#include "file.hpp"

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

vector<char *> read_file(char *filename)
{
    FILE *file;
    vector<char *> ret;
    file = fopen(filename, "r");
    if(file == NULL)
    {    printf("Error while opening file \n"); return ret;}
    
    char *line = new char[128];
    size_t len;
    ssize_t read;
    
    while (readline(file, line))
    {
        ret.push_back(line);
        line = new char[128];
    
    }

    return ret;
}

char * ReadFileToOne(char *filename)
{
    FILE *file;
    char *ret = NULL, *cp, c;
    file = fopen(filename, "r");
    if(file == NULL)
    {    printf("Error while opening file \n"); return ret;}

    ret = new char[100000];
    cp = ret;

    while ((c = fgetc(file)) != EOF)
    {
        *cp = c;
        cp++;
    }
    *cp = '\n';

    return ret;


}

void WriteToFile(char* data, char* filename)
{
    FILE *file; 

    file = fopen(filename, "w");
    fputs(data, file);
        
}
