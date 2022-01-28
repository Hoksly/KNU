#include "file.hpp"


int read_file(const char *filename, std::vector<Person*> *people)
{
    /*
    Database file: filename
    n - quantity of structures
    strucutres data
    */

    FILE *file;  
    char *c;
    
    int  n = 0, i;
    
    

    if((file = fopen(filename, "rb")) == NULL)
    {
        std::cout << "Error while opening database file";
        return 1;
    
    }
    
    Person *ptr = (Person *) malloc(sizeof(Person));
  
    c = (char *) ptr;
    char *c2 = c;
    int ctr = 0, person_sz = sizeof(Person);

    
    while((i = getc(file)) != EOF)
    {
        if(ctr < person_sz)
        {
            *c = i;
            c++;
            ctr++;
        }
        else
        {
            //cout << (long) ptr << endl;
            
            people->push_back((Person*) c2);
            ctr = 0;
            Person *ptr = (Person *) malloc(sizeof(Person));
            //cout << (long) ptr << endl;
            c = (char *) ptr;
            c2 = c;

            *c = i;
            c++;
            ctr++;

        }
       
    }

    people->push_back((Person*)c2);
    
    

   
    fclose(file);
    return 0;
} 

int write_in_file(const char *filename, std::vector<Person*> *people)
{
    FILE *file;
    char *c;
    int size = sizeof(Person);
    
    if((file = fopen(filename, "wb")) == NULL)
    {
        std::cout << "Error while writing in file" << std::endl; return 1;
    }
    if(people->size() == 0)
        return 0;
    
    int n = people->size();

    for(int i = 0; i < n; i++)
    {
        c = (char *) (*people)[i];
        
        for(int j = 0; j < size; j++)
            putc(*c++, file);

    }
    return 0;
}