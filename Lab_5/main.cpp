//#include <iostream>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

char FILENAME[] = "data.dat";
const int MAX_NAME_LEN = 40;
const int MAX_DATE_OF_BIRTH_LEN = 11;

/*
struct Person
{   
    const char *name;
    const char *second_name;
    bool is_male;
    long telegram_id;
    const char *date_of_birth;

};
*/
struct Person
{   
    char name[40];
    char second_name[40];
    bool is_male;
    long telegram_id;
    char date_of_birth[11];

};

int read_file(char *filename, vector<Person*> *people)
{
    /*
    Database file:
    n - quantity of structures
    strucutres data
    */

    FILE *file;  
    char *c;
    
    int  n = 0, i;
    


    if((file = fopen(filename, "rb")) == NULL)
    {
        cout << "Error while opening database file";
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
            people->push_back((Person*) c2);
            ctr = 0;
            Person *ptr = (Person *) malloc(sizeof(Person));
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

int simple_write()
{
    FILE *file;
    char *c;
    int size = sizeof(Person);
    
    file = fopen("data.dat", "ab");

    Person An = {"Billy", "Herington", true, 0, "01:01:1992"};

    c = (char *) (&An); 
    for(int i = 0; i < size; i++)
    {
        putc(*c++, file);
    
    }
    fclose(file);
    

    return 0;
}

int write_in_file(char *filename, vector<Person*> *people)
{
    FILE *file;
    char *c;
    int size = sizeof(Person);
    
    if((file = fopen(filename, "wb")) == NULL);
    {
        cout << "Error while writing in file" << endl; return 1;
    }
    
    int n = people->size();

    for(int i = 0; i < n; i++)
    {
        c = (char *) (*people)[i];
        
        for(int j = 0; j < size; j++)
            putc(*c++, file);

    }
    return 0;
}


int process()
{
    vector<Person*> people;
    vector<Person*> *ptr = &people;

    read_file(FILENAME, ptr);
    //simple_write();
    //Person pp = *(people[0]);
    cout << people.size() << endl;
    for(int i = 0; i < people.size(); i++)
    {
        Person pp = *(people[i]);
        cout << pp.name << ' ' << pp.second_name << ' ' << pp.date_of_birth << endl;
    }
    
    return 0;
}


int main()
{
    process();
    return 0;   

}