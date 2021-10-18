//#include <iostream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>

using namespace std;

char FILENAME[] = "data.dat";
const int MAX_NAME_LEN = 40;
const int MAX_DATE_OF_BIRTH_LEN = 11;
const int MAX_LINE_LEN = 150;
const int MAX_COMMAND_LEN  = 15;
char CLOSE_CONDITION[] = ":q";

const int MAX_VALUE_LEN = 40;
const int MAX_PARAM_LEN = 20;

//commands
char INSERT_COMMAND[] = "INSERT";
char DELETE_COMMAND[] = "DELETE";
char UPDATE_COMMAND[] = "UPDATE";
char SELECT_COMMAND[] = "SELECT";
char WRITE_DOWN_COMMAND[] = "WRITE_DOWN";

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
    
    file = fopen(FILENAME, "ab");

    Person An = {"Van", "Darkholm", true, 0, "01:01:1987"};

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
    
    if((file = fopen(filename, "wb")) == NULL)
    {
        cout << "Error while writing in file" << endl; return 1;
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
int add_new_person(vector<Person*> *people, char *name, char *second_name, char *date_of_birthday, long telegram_id, bool is_male)
{
    Person *ptr = new Person;
    for(int i = 0; i < MAX_NAME_LEN; i++, name++)
        ptr->name[i] = *name;
    for(int i = 0; i < MAX_NAME_LEN; i++, second_name++)
        ptr->second_name[i] = *second_name;
    for(int i = 0; i < MAX_DATE_OF_BIRTH_LEN; i++, date_of_birthday++)
        ptr->date_of_birth[i] = *date_of_birthday;
    
    ptr->is_male = is_male;
    ptr->telegram_id = telegram_id;
    people->push_back(ptr);
}

 void clear_spaces(char **ch) 
{
    while (**ch == ' ')
        (*ch)++;

}
int find_word(char **ch, char *word)
{
    while(('a' <= **ch && **ch <= 'z') || ('A' <= **ch && **ch <= 'Z'))
    {
        *word = **ch;
        word++;
        (*ch)++;
    }

    return 0;
}

int find_command(char **ch, char *command)
{
    int i = 0;
    while(i < MAX_COMMAND_LEN && **ch != ' ')
    {
        *command = **ch;
        (*ch)++;
        command++;
    }
    if(**ch == 0 || i >= 15)
        {cout << "Error while parsing command"; return 1;}
    *command = '\0';
    return 0;
}
int find_param_and_value(char **ch, char *param, char *value)
{

    return 0;
}
int find_params(char **ch, map<char*, char*> *list_of_params)
{
    char *param = new char[MAX_PARAM_LEN];
    char *value = new char[MAX_VALUE_LEN];
    while(true)
    {
        find_param_and_value(ch, param, value);
        list_of_params->insert(param, value);
        char *param = new char[MAX_PARAM_LEN];
        char *value = new char[MAX_VALUE_LEN];
        
        clear_spaces(ch);
        if(**ch != ',')
            return 0;

    }
}

int parse_command(char *input, vector<Person*> *people)
{
    char **ch = &input;
    char *main_command = new char[MAX_COMMAND_LEN];
    find_command(ch, main_command);
    clear_spaces(ch);
    map <char*, char*> params_list;


    if(!strcmp(main_command, WRITE_DOWN_COMMAND))
    {
        write_in_file(FILENAME, people);
    }
    
    else if(!strcmp(main_command, INSERT_COMMAND))
    {

    }
    
    else if(!strcmp(main_command, UPDATE_COMMAND))
    {
        
    }
    
    else if(!strcmp(main_command, DELETE_COMMAND))
    {
        
    }
    
    else if(!strcmp(main_command, SELECT_COMMAND))
    {
        
    }
    
    else
    {cout << "Error while parsing command: couldn't recognize command" << endl; return 1;}


    return 0;
}



int process()
{
    vector<Person*> people;
    vector<Person*> *ptr = &people;

    if(read_file(FILENAME, &people))
        return 1;

    /*
    //simple_write();
    //Person pp = *(people[0]);
    cout << people.size() << endl;
    for(int i = 0; i < people.size(); i++)
    {
        Person pp = *(people[i]);
        cout << pp.name << ' ' << pp.second_name << ' ' << pp.date_of_birth << endl;
    }
    */
    cout << endl <<endl;
    cout << "Welcome to the consol version of TelegramDb controller"<< endl;
    cout << "Some tips for it's usage: " << endl;
    cout <<"To select something: SELECT param1, param2... WHERE statement1 = s-th1, statement2 = s-th2" << endl;
    cout <<"To delete something: DELETE WHERE cond1, cond2..." << endl;
    cout << "To insert something: INSERT param1 = value1, param2 = value2..." << endl;
    cout << "To update something UPDATE param1 = value1, param2 = value2... WHERE condition1, condition2... ";
    cout << "To write changes: WRITE_DOWN (automaticly write when close)" << endl;
    cout << "To exit program "<<CLOSE_CONDITION << endl;
    cout << "Additional information about all functions: <Command> --help" << endl << endl;
    char *input = new char[MAX_LINE_LEN];
    while (true)
    {
        
        cin.getline(input, MAX_LINE_LEN);
        if(!strcmp(input, CLOSE_CONDITION))
        {
            write_in_file(FILENAME, &people);
            cout << "Exiting..." << endl;
            break;
        }


    }


    return 0;
}


int main()
{
    process();
    //simple_write();
    return 0;   

}