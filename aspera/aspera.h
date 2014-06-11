#ifndef ASPERA_H
#define ASPERA_H

#define MAX_RESULTS_TO_SHOW 3

const char INPUT_FILE[] = "words for problem.txt";

using namespace std;

class Aspera
{
    friend int main( int, char ** );

    Aspera( size_t max_results_to_show )
    {
        m_total_words = 0;

        m_max_results_to_show = max_results_to_show;
    }

    size_t m_total_words;

    size_t m_max_results_to_show;

    vector<string> m_words;

    Trie m_trie;

    int main();

    bool IsStringMadeUpOfSubString( const char *, size_t, size_t );

    bool IsStringMadeUpOfSubStrings( const char *, size_t, bool );

    bool ProcessAllWords( const char *, size_t );

    static bool ProcessAllWords( const char *word, size_t len, void *pthis )
    {
        return ((Aspera *)pthis)->ProcessAllWords( word, len );
    }

    static bool compare_descending( const string &, const string & ); // sort callback function, must be static
};

#endif                                       
