#ifndef TRIE_H
#define TRIE_H

#define MAX_WORD_LEN 80

class TNode
{
    char m_char; // character for this node

    bool m_isWord; // is this end of a word?

    TNode *m_next; // points to next node

    TNode *m_last; // points to last node added, for optimization when adding new nodes

    TNode *m_child; // points to child node

public:

    TNode( char c ) // constructor
    {
        m_char = c;
        m_isWord = false;
        m_next = NULL;
        m_last = NULL;
        m_child = NULL;
    }

    bool GetIsWord() // query if node is end of a word
    {
        return m_isWord;
    }

    void SetIsWord() // set node to be end of word
    {
        m_isWord = true;
    }

    char GetChar() // get character of node
    {
        return m_char;
    }

    TNode *GetNext() // get next node
    {
        return m_next;
    }

    TNode *GetChild() // get child node
    {
        return m_child;
    }

    TNode *FindChild( char c ) // finds child nodes with a given character
    {
        TNode *child = m_child;

        while ( NULL != child )
        {
            if ( c == child->m_char )
                return child;

            child = child->m_next;
        }

        return NULL;
    }

    void AddChild( TNode *child ) // adds a new child node, m_last is used to optimize appending new node at the end
    {
        if ( NULL == m_last )
        {
            m_child = child;
        }
        else
        {
            m_last->m_next = child;
        }

        m_last = child;
    }
};

class Trie
{
    typedef bool (__cdecl *TRIECALLBACK)( const char *, size_t, void * ); // callback function to enumerate all strings in trie

    TNode *m_head; // first dummy node in trie

    char m_word[MAX_WORD_LEN];

    // recursively enumerate all words in trie and pass them to callback function

    bool GetWordAtLevel( TNode *node, size_t level, TRIECALLBACK callback, void *context )
    {
        bool bResult = true;

        TNode *child = node->GetChild();

        while ( NULL != child )
        {
            m_word[level] = child->GetChar();

            bResult = GetWordAtLevel( child, level+1, callback, context );

            if ( false == bResult ) // stop enumerating if callback returns false
                break;

            child = child->GetNext();
        }
        
        if ( true == node->GetIsWord() )
        {
            m_word[level] = '\0'; // NULL terminate the string

            bResult = callback( m_word, level, context ); // pass string and length to callback function
        }

        return bResult;
    }

    void FreeNodes( TNode *node ) // recursively free all memory allocated for trie
    {
        TNode *next, *child = node->GetChild();

        while ( NULL != child )
        {
            next = child->GetNext();

            FreeNodes( child );

            child = next;
        }

        delete node;
    }

public:

    Trie()
    {
        m_head = new TNode( '\0' ); // created first dummy node holding NULL character
    }

    ~Trie()
    {
        FreeNodes( m_head ); // clean up
    }

    // adds a new word to trie, any duplicates will be automatically discarded

    void AddWord( const char *psz )
    {
        bool findChild = true;

        TNode *child, *node = m_head;

        for ( ;; )
        {
            if ( isspace( *psz ) || '\0' == *psz )
                break;

            if ( true == findChild )
            {
                child = node->FindChild( *psz );

                if ( NULL == child )
                {
                    findChild = false;

                    child = new TNode( *psz );

                    node->AddChild( child );
                }
            }
            else
            {
                child = new TNode( *psz );

                node->AddChild( child );
            }

            node = child;

            psz++;
        }

        node->SetIsWord();
    }

    bool IsWord( const char *psz, size_t len ) // check if a string up to "len" in length can be found in trie
    {
        TNode *node = m_head;

        while ( 0 != len )
        {
            node = node->FindChild( *psz );

            if ( NULL == node )
                return false;
      
            psz++;

            len--;
        }

        return node->GetIsWord();
    }

    // enumerate all words in trie using a callback

    void EnumarateAllWords( TRIECALLBACK callback, void *context )
    {
        GetWordAtLevel( m_head, 0, callback, context );
    }
};

#endif
