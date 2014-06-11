#include "precomp.h"

static DWORD GetTimes( DWORD dwNow, DWORD dwStartTime, DWORD dwDuration, DWORD *pdwTimeLeft )
{
    DWORD dwElapsed = dwNow - dwStartTime;

    DWORD dwTimeLeft = dwDuration - dwElapsed;

    if ( dwTimeLeft % 1000 )
    {
        dwTimeLeft += 1000;
    }

    *pdwTimeLeft = dwTimeLeft;

    return (dwElapsed * 100) / dwDuration;
}

void Bromium::OnTimer()
{
    ThreadInfo *pti;

    int ix, cc = ListBox_GetCount( m_hwndLB1 );

    DWORD dwDuration, dwStartTime, dwPercent, dwTimeLeft, dwIdle = 0, dwNow = GetTickCount();

    for ( ix = 0; ix < cc; ix++ )
    {
        pti = (ThreadInfo *) ListBox_GetItemData( m_hwndLB1, ix ) ;

        dwDuration = pti->thd->GetDuration( &dwStartTime, &pti->dwWork );

        if ( dwDuration )
        {
            if ( !pti->bActive )
            {
                pti->bActive = true;
                pti->dwPercent = 100;
                pti->dwTimeLeft = (DWORD) - 1;
            }

            dwPercent = GetTimes( dwNow, dwStartTime, dwDuration, &dwTimeLeft );

            if ( pti->dwPercent != dwPercent || pti->dwTimeLeft != dwTimeLeft )
            {
                pti->dwPercent = dwPercent;
                pti->dwTimeLeft = dwTimeLeft;

                InvalidateRect( m_hwndLB1, &pti->rc, FALSE );
            }
        }
        else
        {
            dwIdle++;

            if ( pti->bActive )
            {
                pti->bActive = false;

                InvalidateRect( m_hwndLB1, &pti->rc, FALSE );
            }
        }
    }

    BOOL f;

    if ( GetDlgItemInt( m_hwnd, IDC_STATIC1, &f, FALSE ) != (UINT) dwIdle )
    {
        SetDlgItemInt( m_hwnd, IDC_STATIC1, dwIdle, FALSE );
    }

    cc = ListBox_GetCount( m_hwndLB2 );

    if ( GetDlgItemInt( m_hwnd, IDC_STATIC2, &f, FALSE ) != (UINT) cc )
    {
        SetDlgItemInt( m_hwnd, IDC_STATIC2, cc, FALSE );
    }

    if ( dwNow > m_next_add_work_time )
    {
        m_next_add_work_time = dwNow + m_add_work_interval;

        if ( !m_bPauseQueue )
        {
            AddWork();
        }
    }
}

bool Bromium::OnCreate( HWND hwnd )
{
    m_hwnd = hwnd;

    m_hwndLB1 = GetDlgItem( m_hwnd, IDC_LIST1 );
    m_hwndLB2 = GetDlgItem( m_hwnd, IDC_LIST2 );

    SendMessage( m_hwnd, WM_SETICON, ICON_BIG, (LPARAM) LoadIcon( IDR_MODULE ) );
    SendMessage( m_hwnd, WM_SETICON, ICON_SMALL, (LPARAM) LoadIcon( IDR_MODULE ) );

    AddThreads( DEFAULT_THREADS );

    m_min_work_duration = DEFAULT_MIN_WORK_DURATION;

#ifdef _DEBUG    
    m_max_work_duration = DEFAULT_MAX_WORK_DURATION;
#else
    m_max_work_duration = ListBox_GetCount( m_hwndLB1 ) / 17;
#endif

    m_add_work_interval = DEFAULT_ADD_WORK_INTERVAL;

    m_next_add_work_time = GetTickCount() + m_add_work_interval;

    SetDlgItemInt( m_hwnd, IDC_EDIT1, ListBox_GetCount( m_hwndLB1 ), FALSE );
    SetDlgItemInt( m_hwnd, IDC_EDIT2, DEFAULT_ADD_WORK_INTERVAL, FALSE );
    SetDlgItemInt( m_hwnd, IDC_EDIT3, DEFAULT_MIN_WORK_DURATION, FALSE );
    SetDlgItemInt( m_hwnd, IDC_EDIT4, m_max_work_duration, FALSE );

    m_uTimer = SetTimer( m_hwnd, IDR_MODULE, MIN_TIMER_INTERVAL, NULL );

    if ( m_nCmdShow != SW_HIDE )
    {
        ShowWindow( m_hwnd, SW_SHOWNORMAL );
    }

    return true;
}

void Bromium::OnDestroy()
{
    KillTimer( m_hwnd, m_uTimer );

    m_quit = true;

    RemoveThreads( (DWORD) ListBox_GetCount( m_hwndLB1 ) );

    PostQuitMessage( 0 );
}

void Bromium::OnUpdate()
{
    BOOL f;

    DWORD max_threads = max( 1, GetDlgItemInt( m_hwnd, IDC_EDIT1, &f, FALSE ) );

    m_add_work_interval = max( MIN_TIMER_INTERVAL, GetDlgItemInt( m_hwnd, IDC_EDIT2, &f, FALSE ) );
    m_min_work_duration = max( MIN_WORK_DURATION, GetDlgItemInt( m_hwnd, IDC_EDIT3, &f, FALSE ) );
    m_max_work_duration = max( MIN_WORK_DURATION, GetDlgItemInt( m_hwnd, IDC_EDIT4, &f, FALSE ) );

    SetDlgItemInt( m_hwnd, IDC_EDIT1, max_threads, FALSE );
    SetDlgItemInt( m_hwnd, IDC_EDIT2, m_add_work_interval, FALSE );
    SetDlgItemInt( m_hwnd, IDC_EDIT3, m_min_work_duration, FALSE );
    SetDlgItemInt( m_hwnd, IDC_EDIT4, m_max_work_duration, FALSE );

    DWORD cc = (DWORD) ListBox_GetCount( m_hwndLB1 );

    if ( max_threads != cc )
    {
        if ( max_threads > cc )
        {
            AddThreads( max_threads - cc );

            SetDlgItemInt( m_hwnd, IDC_EDIT1, ListBox_GetCount( m_hwndLB1 ), FALSE );
        }
        else
        {
            RemoveThreads( cc - max_threads );
        }

        ::PulseEvent( m_hevent );
    }

    m_next_add_work_time = GetTickCount() + m_add_work_interval;
}

void Bromium::OnCommand( HWND hwndCtl, UINT uId, UINT /*uCmd*/ )
{
    switch ( uId )
    {
        case IDC_BUTTON1:

            OnUpdate();

        break;

        case IDC_BUTTON2:

            UINT strId;

            m_bPauseQueue = !m_bPauseQueue;

            if ( m_bPauseQueue )
            {
                strId = IDS_RESUME_ADD;
            }
            else
            {
                strId = IDS_PAUSE_ADD;
            }

            SetDlgItemText( m_hwnd, uId, LoadString( strId ) );

        break;

        case ID_FILE_EXIT:

            PostMessage( m_hwnd, WM_CLOSE, 0, 0L );

        break;

        case ID_HELP_ABOUT:

            DialogBoxParam( IDD_ABOUT, &Bromium::AboutDlgProc, m_hwnd  );

        break;
    }
}

void Bromium::OnDrawItem( DRAWITEMSTRUCT *pdis )
{
    if ( pdis->CtlID == IDC_LIST1 )
    {
        TCHAR sz[MAX_PATH];

        ThreadInfo *pti = (ThreadInfo *) pdis->itemData;

        pti->rc = pdis->rcItem;

        InflateRect( &pti->rc, 0, -1 );

        int width = pti->rc.right - pti->rc.left;

        int height = pti->rc.bottom - pti->rc.top;

        PatBlt( pdis->hDC, pti->rc.left, pti->rc.top, width, height, WHITENESS );

        if ( pti->bActive && pti->dwPercent )
        {
            HBRUSH hbr = SelectBrush( pdis->hDC, GetStockObject( LTGRAY_BRUSH ) );

            int bar = (int) (((float)width * (float)pti->dwPercent)/100.f);

            PatBlt( pdis->hDC, pti->rc.left, pti->rc.top, bar, height, PATCOPY );

            SelectBrush( pdis->hDC, hbr );
        }

        int mode = SetBkMode( pdis->hDC, TRANSPARENT );

        _sntprintf( sz, countof(sz), _T("%u [%u %s]"), pdis->itemID + 1, pti->dwWork, (LPCTSTR) LoadString( IDS_WORK ) );

        DrawText( pdis->hDC, sz, -1, &pti->rc, DT_SINGLELINE );

        if ( pti->bActive )
        {
            _sntprintf( sz, countof(sz), _T("[%u %s] %u%%"), pti->dwTimeLeft/1000, (LPCTSTR) LoadString( IDS_SECS ), pti->dwPercent );

            DrawText( pdis->hDC, sz, -1, &pti->rc, DT_SINGLELINE | DT_CENTER );
        }
        else
        {
            _sntprintf( sz, countof(sz), _T("[%s]"), (LPCTSTR) LoadString( IDS_IDLE ) );

            DrawText( pdis->hDC, sz, -1, &pti->rc, DT_SINGLELINE | DT_CENTER  );
        }

        SetBkMode( pdis->hDC, mode );
    }
}

LRESULT Bromium::MainDlgProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    INT_PTR lResult = 0;

    // DPF( "%08X %-20s %08X %08X", m_hwnd, WM_MSG(uMsg), wParam, lParam );

    switch ( uMsg )
    {
        case WM_INITDIALOG:
            if ( !OnCreate( hwnd ) )
            {
                DestroyWindow( hwnd );
            }
        break;

        case WM_COMMAND:
            OnCommand( GET_WM_COMMAND_HWND(wParam,lParam), GET_WM_COMMAND_ID(wParam,lParam), GET_WM_COMMAND_CMD(wParam,lParam) );
        break;

        case WM_DRAWITEM:
            OnDrawItem( (DRAWITEMSTRUCT *) lParam );
        break;

        case WM_THEMECHANGED:
        case WM_SYSCOLORCHANGE:
            InvalidateRect( hwnd, NULL, TRUE );
        break;

        case WM_TIMER:
            OnTimer();
        break;

        case WM_CLOSE:
            DestroyWindow( hwnd );
        break;

        case WM_DESTROY:
            OnDestroy();
        break;

        default:
            lResult = DefDlgProc( hwnd, uMsg, wParam, lParam );
        break;
    }

    return lResult;
}

int Bromium::main()
{
    MSG msg = { 0 };

    m_hwnd = FindWindow( szModuleName, NULL );

    if ( m_hwnd )
    {
        OpenIcon( m_hwnd );
        BringWindowToTop( m_hwnd );
        SetForegroundWindow( m_hwnd );
        ShowWindow( m_hwnd, SW_SHOWNORMAL );
    }
    else
    {
        WNDCLASSEX wcx = { 0 };

        wcx.style         = CS_DBLCLKS | CS_SAVEBITS | CS_BYTEALIGNWINDOW;
        wcx.hInstance     = m_hinst;
        wcx.hIcon         = 
        wcx.hIconSm       = LoadIcon( IDR_MODULE );
        wcx.hCursor       = ::LoadCursor( NULL, IDC_ARROW );
        wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wcx.lpszClassName = szModuleName;

        if ( CreateDialogParam( &wcx, IDR_MODULE, &Bromium::MainDlgProc ) )
        {
            while ( GetMessage( &msg, NULL, 0, 0 ) )
            {
                if ( !IsDialogMessage( m_hwnd, &msg ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
            }
        }
    }

    return (int) msg.wParam;
}

int WINAPI _tWinMain( HINSTANCE hinst, HINSTANCE, LPTSTR, int nCmdShow )
{
    Bromium app( hinst, hinst, nCmdShow );

    return app.main();
}
