#include <stdio.h>
#include <sys\timeb.h> // for millisecond structure
#include <algorithm>   // for sorting
#include <vector>
#include <string>
#include "trie.h"
#include "aspera.h"

// check if substring of certain length can be found in trie

bool Aspera::IsStringMadeUpOfSubString( const char *psz, size_t subLen, size_t fullLen )
{
    bool bResult = m_trie.IsWord( psz, subLen ); // fast lookup from trie

    if ( true == bResult ) // if substring is found in trie
    {
        fullLen -= subLen;

        if ( 0 != fullLen )
        {
            bResult = IsStringMadeUpOfSubStrings( &psz[subLen], fullLen, true ); // repeat comparing against all strings in trie, including self
        }
    }

    return bResult;
}

// recursively check if a string is made up of substrings

bool Aspera::IsStringMadeUpOfSubStrings( const char *psz, size_t fullLen, bool bCheckSelf )
{
    size_t subLen = 1; // start with first character of string

    bool bResult;

    for ( ;; )
    {
        bResult = IsStringMadeUpOfSubString( psz, subLen, fullLen );

        if ( true == bResult )
            break;

        if ( true == bCheckSelf )
        {
            if ( subLen++ == fullLen ) // post-increment length after checking
                break;
        }
        else
        {
            if ( ++subLen == fullLen ) // pre-increment length before checking
                break;
        }
    }

    return bResult;
}

bool Aspera::ProcessAllWords( const char *word, size_t len )
{
    m_total_words++;

    if ( len > 1 )
    {
        if ( true == IsStringMadeUpOfSubStrings( word, len, false ) )
        {
            m_words.push_back( word ); // add word that are made up of smaller words into vector
        }
    }

    return true;
}

// sort words by length in desending order, ie : longest words first

bool Aspera::compare_descending( const string &left, const string &right )
{
    size_t left_len = left.length();

    size_t right_len = right.length();

    if ( left_len == right_len )
    {
        return left < right; // if lengths are the same compare alphabetically in ascending order
    }

    return left_len > right_len;
}

int Aspera::main()
{
    int result = 1;

    FILE *f = fopen( INPUT_FILE, "r" );

    if ( NULL == f )
    {
        printf( "\nError opening \"%s\"\n", INPUT_FILE );
    }
    else
    {
        char sz[MAX_WORD_LEN];

        for ( ;; )
        {
            sz[0] = '\0';

            fgets( sz, MAX_WORD_LEN, f ); // read next word

            if ( '\0' == sz[0] ) // bail if nothing was read
                break;

            m_trie.AddWord( sz ); // add word to trie
        }

        fclose( f ); // done with file, close it

        struct timeb t1, t2;

        ftime( &t1 ); // begin time snapshot

        m_trie.EnumarateAllWords( &Aspera::ProcessAllWords, this ); // process all words in trie

        ftime( &t2 ); // end time snapshot

        size_t elapsed = (size_t) (((t2.time * 1000) + t2.millitm) - ((t1.time * 1000) + t1.millitm));

        size_t results = m_words.size();

        size_t showing = (m_max_results_to_show > results) ? results : m_max_results_to_show;

        printf( "\nFound %u result(s) from %u word(s) in %ums\n\nShowing first %u result(s):\n\n", results, m_total_words, elapsed, showing );

        sort( m_words.begin(), m_words.end(), compare_descending ); // all results are sorted by length in desending order

        size_t count = 0;

        for ( vector<string>::const_iterator it = m_words.begin(); it != m_words.end(); it++ )
        {
            if ( count == showing ) // limit number of results being shown
                break;

            count++;

            puts( it->c_str() );
        }

        putchar( '\n' );

        result = 0;
    }

    return result;
}

int main( int argc, char **argv )
{
    size_t max_results_to_show = 0;

    if ( 2 == argc )
    {
        max_results_to_show = (size_t) atol( argv[1] );
    }

    if ( 0 == max_results_to_show )
    {
        max_results_to_show = MAX_RESULTS_TO_SHOW;
    }

    Aspera app( max_results_to_show );

    return app.main();
}
