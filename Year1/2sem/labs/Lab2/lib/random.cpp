#include "random.h"
using namespace std;

char * GiveStr(int len)
{
    bool up;
    char * word = new char[len+1];
    memset(word, '\0', len+1);
    for(int i = 0; i < len; i++)
    {
        char letter = rand() %  26;
        up = (bool) (rand() % 2);
        if(up)
            word[i] =  letter + 65;
        else
            word[i] = letter + 97;
        if(!isalpha(word[i]))
            cout << "ERROR" << endl;   
    
    }
    
    word[len] = '\n';
    
    

    return word;
}


pair<vector<vector<String*>>,vector<vector<char>>> give_set(int total_len)
{
    cout << "BEGINING OF SET CREATION" << endl;
    int len;
    vector<vector<char>> NonEmpty(STR_LEN, vector<char>());
    vector<vector<String*>> ret(STR_LEN, vector<String *>());
    
    
    bool Map[STR_LEN][LEN];
    
    for (int i = 0; i < STR_LEN; ++i)
        memset(Map[i], false, LEN);
    

    

    String *word = new String();
    cout << "HERE" << endl;
    len = rand() % 126 + 1;
    char *line = GiveStr(len); 
    cout << "HERE2" << endl;
    for(int i = 0; i < total_len; ++i)
    {
        word->mas = line;
        word->_len = len;

        ret[word->_len - 1].push_back(word);
        for(int i = 0; i < word->_len; ++i)
        {
            if(!Map[i][tolower((*word)[i])])
            {
                
                Map[i][tolower((*word)[i])] = true;
                
            }
        }
        
        

        line = GiveStr(rand() % 126 + 1);
        word = new String();
        

    }

    for(int i = 0; i < STR_LEN; ++i)
        {
            for(int q = 0; q < LEN; q++)
            {
                if(Map[i][q])
                {
                    //cout << "HEREEEEEEE" << endl;
                
                    NonEmpty[i].push_back((char) q);
                    //cout <<((char) q ) << endl;
                }
            }
        }

    cout << "FINISHED CREATING SET" << endl;

    return make_pair(ret, NonEmpty);

}
