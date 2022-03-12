#pragma once
#include <string>
#include <string.h>
#include <iostream>


struct command
{
    std::string first;
    std::string second;
    bool is_end;
    int n;

    command(std::string, std::string, int , bool); 
    
};

typedef struct MarkovPart
{
    char val;
    MarkovPart *next = nullptr;
} *MarkovPtr;

class MarkovList
{
    int _size = 0;
    MarkovPtr FIRST = nullptr;

    //functions
    MarkovPtr GiveLast();
    MarkovPtr Search(MarkovPtr, std::string);

    bool IsIt(MarkovPtr, std::string, int);

    MarkovPtr MoveTo(MarkovPtr, int);

    //operations 
    void CreateNewParts(int);
    void DeleteParts(MarkovPtr, int);
    void ReplaceValue(MarkovPtr, std::string, int);
    void AddParts(MarkovPtr, int);
    void AddAndSet(MarkovPtr, std::string);
    void Replace(MarkovPtr, std::string, std::string);

    public:
    MarkovList(char *);
    MarkovList(std::string);

    int size();
    int replace(std::string, std::string);
    void show();
    std::string data();
    char * data_char();

};
