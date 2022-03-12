#include "lib/recognize.hpp"
#include "lib/classes.hpp"
#include "lib/file.hpp"
#include "lib/Markov.hpp"

#include <iostream>
using namespace std;

char ALGO_FILENAME[] = "alg.txt";
char INPUT_FILENAME[] = "inp.txt";
char OUTPUT_FILENAME[] = "out.txt";

bool SAVE_RES = false;


int main()
{
    char Alphabet[100], Tuple[100], *filedata, *input_data;

    filedata = ReadFileToOne(ALGO_FILENAME);
    input_data = ReadFileToOne(INPUT_FILENAME);
    char **ch = &filedata;
    
    vector<command> Commands;
    extract(&filedata, Alphabet, Tuple, Commands);    

    MarkovList ML(input_data);
    ML.show();

    RunAlgoritm(ML, Commands, true, false, false);
    if (SAVE_RES);
        //WriteToFile(ML.data_char(), OUTPUT_FILENAME);

   return 0;
}