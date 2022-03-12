#include "input.h"
using namespace std;


bool readline(FILE *file, char * ret)
{
    char c;
    bool res = false;
    
    while ((c = fgetc(file)) != EOF && c != '\n')
    {

        *ret = c;
        ret++;
        res = true;
        

    }
    if (c == '\n')
        res = true;
    
    *ret = '\0';

    return  res;
}

pair<vector<vector<String*>>, vector<vector<char>>> read_file(char* filename)
{

    vector<vector<char>> NonEmpty(STR_LEN, vector<char>());
    vector<vector<String*>> ret;
    for(int i = 0; i < STR_LEN; i++) // LEN == 128
        ret.push_back(vector<String*>());
    
    bool Map[STR_LEN][LEN];
    for (int i = 0; i < STR_LEN; ++i)
        memset(Map[i], false, LEN);
    

    FILE *file;
    file = fopen(filename, "r");
    if(file == NULL)
    {    printf("Error while opening file \n"); return make_pair(ret, NonEmpty);}

    String *word = new String();

    char *line = new char[STR_LEN]; //Redefine constant
    size_t len;
    ssize_t read;
    
    while (readline(file, line))
    {
        word->mas = line;
        word->_len = strlen(line);

        ret[word->_len - 1].push_back(word);
        for(int i = 0; i < word->_len; ++i)
        {
            if(!Map[i][tolower((*word)[i])])
            {
                
                Map[i][tolower((*word)[i])] = true;
                
            }
        }
        
        

        line = new char[STR_LEN];
        word = new String();
        

    }

    for(int i = 0; i < STR_LEN; ++i)
        {
            for(int q = 0; q < LEN; q++)
            {
                if(Map[i][q])
                {
                
                    NonEmpty[i].push_back((char) q);
                }
            }
        }

    return make_pair(ret, NonEmpty);
}



void write_out(char *filename, vector<String *> &sorted)
{
    ofstream out;
    out.open(filename);
    if (!out.is_open())
            {printf("Error while opening out file \n"); return;}

    for(auto v = sorted.begin(); v != sorted.end(); v++)
    {
        char * mas = (*v)->mas;
        while(*mas != '\0')
        {out << *mas; mas++;}
        out << '\n';

    }


}
