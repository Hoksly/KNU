#include "lib/recognize.hpp"
#include "lib/classes.hpp"
#include "lib/file.hpp"
#include <iostream>
using namespace std;

char ALGO_FILENAME[] = "alg.txt";

char INPUT_FILENAME[] = "inp.txt";

int main()
{
    char Alphabet[100], Tuple[100], *filedata, *input_data;

    filedata = ReadFileToOne(ALGO_FILENAME);
    input_data = ReadFileToOne(INPUT_FILENAME);
    char **ch = &filedata;
    
    vector<command> Commands;
    extract(&filedata, Alphabet, Tuple, Commands);    
    for(auto i:Commands)
    {cout << i.first<< ' ' << i.second << endl; }
    //for (int i = 0; i < Commands.size(); ++i);

    return 0;
}