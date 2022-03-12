#include <stdio.h>
#include <vector>
#include <string>

bool readline(FILE *file, char * ret);
char * ReadFileToOne(char *filename);
std::vector<char *> read_file(char *filename);
void WriteToFile(std::string, char*);