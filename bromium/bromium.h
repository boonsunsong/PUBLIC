#ifndef BROMIUM_H
#define BROMIUM_H

const TCHAR szModuleName[] = _T("BROMIUM");

#define MIN_TIMER_INTERVAL        20
#ifdef _DEBUG
#define DEFAULT_THREADS           20
#define DEFAULT_ADD_WORK_INTERVAL 1000
#define DEFAULT_MAX_WORK_DURATION 42
#else
#define DEFAULT_THREADS           5000
#define DEFAULT_ADD_WORK_INTERVAL MIN_TIMER_INTERVAL
#endif
#define MIN_WORK_DURATION         1
#define DEFAULT_MIN_WORK_DURATION MIN_WORK_DURATION

const struct Random
{
    Random()
    {
        srand ( GetTickCount() );
    }

    DWORD generate( int minval, int maxval ) const
    {
        return (rand() % (maxval-minval+1)) + minval;
    }

} RandomGenerator;

inline DWORD random( DWORD low, DWORD high )
{
    return RandomGenerator.generate( low, high );
}

/*template <class T> class CVector
{
    typedef bool (*ENUMCVECTOR)( T *, void * );

    T *m_pArray;

    size_t m_capacity;
    size_t m_grow;
    size_t m_count;

public:

    CVector( size_t capacity = 64 )
    {
        m_capacity = capacity;
        m_grow = capacity;
        m_count = 0;

        m_pArray = new T[capacity];
    }

    ~CVector()
    {
        delete []m_pArray;
    }

    void push_back( T *p )
    {
        if ( m_count == m_capacity )
        {
            m_capacity += m_grow;

            T *tmp = new T[m_capacity];

            memcpy( tmp, m_pArray, m_count * sizeof(T) );

            delete []m_pArray;

            m_pArray = tmp;
        }

        m_pArray[m_count] = p;
    }

    size_t count()
    {
        return m_count;
    }

    T *get( size_t ix )
    {
        return m_pArray[ix];
    }

    T *remove( size_t ix )
    {
        T *p = m_pArray[ix];

        ix++;

        if ( ix != m_count )
        {
            unsigned char *offset_src = ((unsigned char *)this->m_pArray) + (ix * sizeof(T *));

            memmove( offset_src - sizeof(unsigned char *), offset_src, (m_count - ix) * sizeof(T *) );
        }

        m_count--;

        return p;
    }

    bool enumerate( ENUMCVECTOR callback, void *context )
    {
        size_t ii;

        bool bResult = false;

        for ( ii = 0; ii < m_count; ii++ )
        {
            bResult = callback( m_pArray[ix], context );

            if ( !bResult )
                break;
        }

        return bResult;
    }
};*/

template <class T> class CQueue
{
    T *m_pval;
    size_t m_capacity;
    size_t m_grow;
    size_t m_count;

    CRITICAL_SECTION m_cs;

public:

    CQueue( size_t capacity = 32 )
    {
        m_capacity = capacity;
        m_grow = capacity;
        m_count = 0;

        m_pval = new T[capacity];

        InitializeCriticalSection( &m_cs );
    }

    ~CQueue()
    {
        DeleteCriticalSection( &m_cs );

        delete []m_pval;
    }

    size_t push( T val )
    {
        EnterCriticalSection( &m_cs );

        if ( m_count == m_capacity )
        {
            m_capacity += m_grow;

            T *tmp = new T[m_capacity];

            memcpy( tmp, m_pval, m_count * sizeof(T) );

            delete []m_pval;

            m_pval = tmp;
        }

        m_pval[m_count] = val;

        m_count++;

        LeaveCriticalSection( &m_cs );

        return m_count;
    }

    bool pop( T *pval )
    {
        bool bResult = false;

        EnterCriticalSection( &m_cs );

        if ( m_count == 0 )
        {
            *pval = 0;
        }
        else
        {
            *pval = m_pval[0];

            m_count--;

            if ( m_count != 0 )
            {
                memmove( &m_pval[0], &m_pval[1], m_count * sizeof(int) );
            }

            bResult = true;
        }

        LeaveCriticalSection( &m_cs );

        return bResult;
    }

    void clear()
    {
        m_count = 0;
    }
};

interface IGlobalAccess
{
    virtual DWORD WaitEvent( DWORD = INFINITE ) = 0;
    virtual void PulseEvent() = 0;
    virtual bool PopQueue( DWORD * ) = 0;
};

class CThread
{
    DWORD m_dwWork, m_dwStartTime, m_dwDuration;

    IGlobalAccess *m_pga;

    HANDLE m_hthread;

    bool m_quit;

    DWORD ThreadProc()
    {
        DWORD dwEnd;

        for ( ;; )
        {
            m_dwDuration = 0;

            if ( m_pga->WaitEvent() != WAIT_OBJECT_0 )
                break;

            if ( m_quit )
                break;

            for ( ;; )
            {
                if ( !m_pga->PopQueue( &m_dwDuration ) )
                {
                    break;
                }

                m_dwWork++;

                m_dwStartTime = GetTickCount();

                dwEnd = m_dwStartTime + m_dwDuration;

                do
                {
                    Sleep( MIN_TIMER_INTERVAL );

                    if ( m_quit )
                        break;

                } while ( GetTickCount() < dwEnd );

                if ( m_quit )
                    break;
            }

            if ( m_quit )
                break;
        }

        return 0;
    }

    static DWORD CALLBACK ThreadProc( void *pthis )
    {
        return ((CThread *)pthis)->ThreadProc();
    }

public:

    CThread( IGlobalAccess *pga, HANDLE *pthread )
    {
        m_pga = pga;

        m_quit = false;

        m_dwWork = 0;

        m_dwDuration = 0;

        m_hthread = CreateThread( NULL, 0, ThreadProc, this, 0, NULL );

        *pthread = m_hthread;
    }

    ~CThread()
    {
        DWORD retry = 0;

        m_quit = true;

        for ( ;; )
        {
            m_pga->PulseEvent();

            if ( WaitForSingleObject( m_hthread, MIN_TIMER_INTERVAL ) == WAIT_OBJECT_0 )
                break;

            if ( ++retry > 5 )
            {
                TerminateThread( m_hthread, -1 );
                break;
            }
        }

        CloseHandle( m_hthread );
    }

    DWORD GetDuration( DWORD *pdwStartTime, DWORD *pdwWork )
    {
        *pdwStartTime = m_dwStartTime;

        *pdwWork = m_dwWork;

        return m_dwDuration;
    }

    void SignalQuit()
    {
        m_quit = true;
    }
};

struct ThreadInfo
{
    CThread *thd;
    RECT rc;
    bool  bActive;
    DWORD dwPercent;
    DWORD dwTimeLeft;
    DWORD dwWork;
};

class Bromium : public CResource, public CMetric<Bromium>, public CCreateDialog<Bromium>, public CDialogBox<Bromium>, public IGlobalAccess
{
    int m_nCmdShow;

    HINSTANCE m_hinst, m_hinstRes;

    HWND m_hwnd, m_hdlg, m_hwndLB1, m_hwndLB2;

    DWORD m_min_work_duration, m_max_work_duration, m_add_work_interval, m_next_add_work_time;

    CQueue<DWORD> m_queue;

    HANDLE m_hevent;

    UINT_PTR m_uTimer;

    bool m_quit, m_bPauseQueue;

    Bromium( HINSTANCE hinst, HINSTANCE hinstRes, int nCmdShow ) : CResource( hinstRes ), CMetric<Bromium>( this, hinst ), CCreateDialog<Bromium>( this, hinstRes, hinst ), CDialogBox<Bromium>( this, hinstRes )
    {
        DPF( "\x1B[2J" );

        m_quit = false;

        m_bPauseQueue = false;

        m_hevent = CreateEvent( NULL, TRUE, FALSE, NULL );

        m_hinst = hinst;
        m_hinstRes = hinstRes;
        m_nCmdShow = nCmdShow;

        INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES };

        InitCommonControlsEx( &icex );
    }

    ~Bromium()
    {
        CloseHandle( m_hevent );

        UnregisterClass( szModuleName, m_hinst );
    }

    void AddThreads( DWORD count )
    {
        HANDLE hthread;

        ThreadInfo *pti;

        CThread *thd;

        DWORD ii;

        SendMessage( m_hwndLB1, WM_SETREDRAW, FALSE, 0 );

        for ( ii = 0; ii < count; ii++ )
        {
            thd = new CThread( this, &hthread );

            if ( !hthread )
            {
                delete thd;
                break;
            }

            pti = new ThreadInfo;

            pti->bActive = false;
            pti->dwPercent = 0;
            pti->dwTimeLeft = 0;
            pti->dwWork = 0;

            pti->thd = thd;

            ListBox_InsertString( m_hwndLB1, -1, pti );
        }

        SendMessage( m_hwndLB1, WM_SETREDRAW, TRUE, 0 );
    }

    void QuitThreads( DWORD count, DWORD cc )
    {
        ThreadInfo *pti;

        while ( count-- )
        {
            pti = (ThreadInfo *) ListBox_GetItemData( m_hwndLB1, --cc );

            pti->thd->SignalQuit();
        }
    }

    void RemoveThreads( DWORD count )
    {
        DWORD cc = (DWORD) ListBox_GetCount( m_hwndLB1 );

        if ( count > cc )
        {
            count = cc;
        }

        if ( count > 1 )
        {
            QuitThreads( count, cc );
        }

        ThreadInfo *pti;

        SendMessage( m_hwndLB1, WM_SETREDRAW, FALSE, 0 );

        while ( count-- )
        {
            pti = (ThreadInfo *) ListBox_GetItemData( m_hwndLB1, --cc );

            delete pti->thd;

            delete pti;

            ListBox_DeleteString( m_hwndLB1, cc );
        }

        SendMessage( m_hwndLB1, WM_SETREDRAW, TRUE, 0 );
    }

    void AddWork()
    {
        DWORD dwDuration = random( m_min_work_duration, m_max_work_duration ) * 1000;

        m_queue.push( dwDuration );

        TCHAR sz[MAX_PATH];

        _sntprintf( sz, countof(sz), _T("%u %s"), dwDuration/1000, (LPCTSTR) LoadString( IDS_SECS ) );

        ListBox_InsertString( m_hwndLB2, -1, sz );

        ::PulseEvent( m_hevent );
    }

    INT_PTR AboutDlgProc( HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM )
    {
        BOOL fResult = TRUE;

        switch ( uMsg )
        {
            case WM_INITDIALOG:

                m_hdlg = hdlg;

                SendMessage( hdlg, WM_SETICON, ICON_BIG, (LPARAM) LoadIcon( IDR_MODULE ) );
                SendMessage( hdlg, WM_SETICON, ICON_SMALL, (LPARAM) LoadIcon( IDR_MODULE ) );

                FORWARD_WM_NEXTDLGCTL( hdlg, GetDlgItem( hdlg, IDOK ), 1, PostMessage );

            break;

            case WM_COMMAND:

            switch ( GET_WM_COMMAND_ID( wParam, lParam ) )
            {
                case IDOK:
                case IDCANCEL:

                    EndDialog( hdlg, 0 );

                  break;

                default:

                    fResult = FALSE;

                  break;
            }

            break;

            case WM_SYSCOLORCHANGE:

                InvalidateRect( hdlg, NULL, TRUE );

            break;

            default:

                fResult = FALSE;

            break;
        }

        return fResult;
    }

    DWORD WaitEvent( DWORD dwTimeOut )
    {
        return WaitForSingleObject( m_hevent, dwTimeOut );
    }

    void PulseEvent()
    {
        ::PulseEvent( m_hevent );
    }

    bool PopQueue( DWORD *pdwDuration )
    {
        bool bResult = m_queue.pop( pdwDuration );

        if ( bResult )
        {
            ListBox_DeleteString( m_hwndLB2, 0 );
        }

        return bResult;
    }

    int main();

    bool OnCreate( HWND );

    void OnTimer();

    void OnDestroy();

    void OnUpdate();

    void OnCommand( HWND, UINT, UINT );

    void OnDrawItem( DRAWITEMSTRUCT * );

    LRESULT MainDlgProc( HWND, UINT, WPARAM, LPARAM );

    friend int WINAPI _tWinMain( HINSTANCE, HINSTANCE, LPTSTR, int );
};

#endif
