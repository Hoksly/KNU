#include <stdio.h>
#include <iostream>
using namespace std;

char File1[] = "file1.txt";
char File2[] = "file2.txt";
char File3[] = "out.txt";


int main()
{
    FILE *file1, *file2, *fileout;

     if((file1 = fopen(File1, "r")) == NULL || file2 = fopen(File1, "r")) == NULL|| fileout = fopen(File1, "r")) == NULL)
    {
        std::cout << "Error while opening database file";
        return 1;
    
    }
    
    

}