#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>

using namespace std;

char FILENAME[] = "data.dat";
const int MAX_NAME_LEN = 40;
const int MAX_DATE_OF_BIRTH_LEN = 11;
const int MAX_LINE_LEN = 350;
const int MAX_COMMAND_LEN  = 15;

char CLOSE_CONDITION[] = ":q";
char CLOSE_CONDITION_UPPER[] = ":Q";

const int MAX_VALUE_LEN = 40;
const int MAX_PARAM_LEN = 20;
const int MAX_BOOL_LEN = 2;
//commands
char INSERT_COMMAND[] = "INSERT";
char DELETE_COMMAND[] = "DELETE";
char UPDATE_COMMAND[] = "UPDATE";
char SELECT_COMMAND[] = "SELECT";
char WRITE_DOWN_COMMAND[] = "WRITE_DOWN";

//other variables
char EMPTY_STRING[] = "";
char NAME_PARAM[] = "name";
char SECOND_NAME_PARAM[] = "second_name";
char IS_MALE_PARAM[] = "is_male";
char TELEGRAM_ID_PARAM[] = "telegram_id";
char DATE_OF_BIRTH_PARAM[] = "date_of_birth";

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

struct str_with_pos
{
    string s = "";
    int pos = 0;

    char get_ch()
    {
        
        return s[pos++];
    }
    char get_ch_nm()
    {
        return s[pos];
    }

};
struct Person
{   
    char name[40];
    char second_name[40];
    bool is_male;
    long telegram_id;
    char date_of_birth[11];

};


void print_map(map<char*, char*> A)
{
    cout << "Printing map" << endl;
    auto i = A.begin();
    for(;i != A.end(); i++)
    {
        cout << i->first << ' ' << i->second << endl;
    }
}

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

    cout << ptr->name << endl;
    cout << ptr->second_name << endl;
    cout << ptr->telegram_id << endl;
    cout << ptr->date_of_birth << endl;

    return 0;
}

 void clear_spaces(str_with_pos &ch, int &i) 
{
    while (ch.get_ch_nm() == ' ' && ch.get_ch_nm() != '\0')
        {ch.pos++;
        
        if(i++ > MAX_LINE_LEN)
            {cout <<"max line len: " << MAX_LINE_LEN << endl;}
        
        }

}
/*
int find_word(char **ch, char *word, int &i)
{
    while(('a' <= **ch && **ch <= 'z') || ('A' <= **ch && **ch <= 'Z'))
    {
        *word = **ch;
        word++;
        (*ch)++;
        if(i++ > MAX_LINE_LEN)
            {cout <<"max line len: " << MAX_LINE_LEN << endl; return 1;}
    }
    

    return 0;
}
*/


int find_command(str_with_pos &ch, char *command, int &i)
{
    int q = 0;
    while(q < MAX_COMMAND_LEN && ch.get_ch_nm() != ' ')
    {
        *command = toupper(ch.get_ch());
        
        command++;
        if(i++ > MAX_LINE_LEN)
            {cout <<"max line len: " << MAX_LINE_LEN << endl; return 1;}
    }
    if(ch.get_ch_nm() == 0 || q >= 15)
        {cout << "Error while parsing command"; return 1;}
    *command = '\0';
    return 0;
}

int find_param_and_value(str_with_pos &ch, string &param, string &value, int &i)
{
    char s;
    clear_spaces(ch, i);
    while(!isblank(ch.get_ch_nm()))
    {
        
        param += ch.get_ch();
        
        
        if(i > MAX_LINE_LEN)
            {cout <<"max line len: " << MAX_LINE_LEN << endl; return 1;}
    }
    clear_spaces(ch, i);
    if(ch.get_ch_nm() == '=')
    {   
        //cout << "HERE2" << endl;
        ch.pos++;
        clear_spaces(ch, i);
        s = ch.get_ch_nm();
        while(!isblank(ch.get_ch_nm()) && ch.get_ch_nm() != ',' && ch.get_ch_nm() != '\0')
        {
            value += ch.get_ch();
            
            
            
            if(i++ > MAX_LINE_LEN)
            {cout <<"max line len: " << MAX_LINE_LEN << endl; return 1;}
        }
    }
    //cout << "OUT" << endl;
    return 0;
}
void print_10(char **ch)
{
    for(int i = 0; i < 30; i++)
        cout << (*ch)[i];
    cout << endl;
}
// INSERT name = Andrew, second_name = Nelitskiy, is_male = 1, telegram_id = 123, date_of_birth = 30:09:2004
string covert_char_to_string(char *param)
{
    string s;
    for(; *param; param++)
        s += *param;
    //cout << s.length() << endl;
    return s;
}

int find_params_and_values(str_with_pos &ch, vector<pair<string, string>> &list_of_params, int &i)
{
    
    while(true)
    {   //cout <<"HERE" << endl;
        string param = "", value = "";
        find_param_and_value(ch, param, value, i);
        pair<string, string> A =  make_pair(param, value);
        cout << A.first << ' ' << A.second << endl;
        
        list_of_params.push_back(A);
        //cout << list_of_params->find(covert_char_to_string(param))->first << ' ' << list_of_params->find(covert_char_to_string(param))->second << endl;  
        
        
        clear_spaces(ch, i);
       
        
        if(ch.get_ch_nm() != ',' || ch.get_ch_nm() == '\0')
            return 0;

        ch.pos++; // symbol ','
        clear_spaces(ch, i);
        if(i++ > MAX_LINE_LEN)
            {cout <<"max line len: " << MAX_LINE_LEN << endl; return 1;}

    }
    
   
}

int command_insert(str_with_pos &ch, vector<Person*> *people, int &i)
{
    vector <pair<string, string>> params_list;
    find_params_and_values(ch, params_list, i);
    
    char *is_male = new char[MAX_BOOL_LEN];
    char *date_of_birth = new char[MAX_DATE_OF_BIRTH_LEN];
    //print_map(params_list);
    /*
    if(!strcmp(EMPTY_STRING, params_list.find(NAME_PARAM)->second) && !strcmp(EMPTY_STRING, params_list.find(SECOND_NAME_PARAM)->second))
    {
        long telegram_id;
        bool is_realy_male;
        date_of_birth = params_list.find(DATE_OF_BIRTH_PARAM)->second;
        is_male = params_list.find(IS_MALE_PARAM)->second;
        
        if((int) params_list.find(TELEGRAM_ID_PARAM)->second[0] > 0)
            telegram_id = strtol(params_list.find(TELEGRAM_ID_PARAM)->second, 0, 10);
        else
            telegram_id = 0;
        
        if(date_of_birth[0] < 0)
            date_of_birth = EMPTY_STRING;
        
        if(is_male[0] < 0)
            is_realy_male = true;
        else
            is_realy_male = (bool) strtol(is_male, 0, 10);
        cout << "HERE" << endl;
        cout << params_list.find(NAME_PARAM)->second << endl;
    
        add_new_person(people,params_list.find(NAME_PARAM)->second, 
        params_list.find(SECOND_NAME_PARAM)->second, 
        date_of_birth, telegram_id, is_realy_male);


    }
    else
    {
        cout << "Error in insert command: gap 'name' and 'second_name' cannot be empty or been ignored" << endl;
        return 1;
    }
    */
    /*
    
    strcpy(name, params_list.find(NAME_PARAM)->second);
    strcpy(second_name, params_list.find(SECOND_NAME_PARAM)->second);
    strcpy(telegram_id, params_list.find(TELEGRAM_ID_PARAM)->second);
    strcpy(is_male, params_list.find(IS_MALE_PARAM)->second);
    strcpy(date_of_birth, params_list.find(DATE_OF_BIRTH_PARAM)->second);
    */

    
    

   return 0;
}



int parse_command(str_with_pos &input, vector<Person*> *people)
{

    char *main_command = new char[MAX_COMMAND_LEN];
    int i = 0;
    find_command(input, main_command, i);
    clear_spaces(input, i);
    
    cout <<"Comand: "<< main_command << endl;

    if(!strcmp(main_command, WRITE_DOWN_COMMAND))
    {
        write_in_file(FILENAME, people);
    }
    
    else if(!strcmp(main_command, INSERT_COMMAND))
    {
        
        command_insert(input, people, i);
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

   
    //simple_write();
    //Person pp = *(people[0]);
    //Debug
   
    cout << people.size() << endl;
    for(int i = 0; i < people.size(); i++)
    {
        Person pp = *(people[i]);
        cout << pp.name << ' ' << pp.second_name << ' ' << pp.date_of_birth << endl;
    }
    
    cout << endl <<endl;
    cout << "Welcome to the consol version of TelegramDb controller"<< endl;
    cout << "Some tips for it's usage: " << endl;
    cout <<"To select something: SELECT param1, param2... WHERE statement1 = s-th1, statement2 = s-th2" << endl;
    cout <<"To delete something: DELETE WHERE cond1, cond2..." << endl;
    cout << "To insert something: INSERT param1 = value1, param2 = value2..." << endl;
    cout << "To update something: UPDATE param1 = value1, param2 = value2... WHERE condition1, condition2... ";
    cout << "To write changes: WRITE_DOWN (automaticly write when close)" << endl;
    cout << "To exit program: '"<<CLOSE_CONDITION <<'\''<< endl;
    cout << "Additional information about all functions: <Command> --help" << endl << endl;
    
    str_with_pos input;
    while (true)
    {
        
        getline(cin, input.s);
        
        if(input.s == CLOSE_CONDITION || input.s == CLOSE_CONDITION_UPPER)
        {
            //write_in_file(FILENAME, &people);
            cout << "Exiting..." << endl;
            break;
        }
        parse_command(input, ptr);


    }
   

    return 0;
}


int main()
{
    process();
    //simple_write();
    return 0;   

}

/*
Adding new person with command insert not wotking properly, debug with cin

INSERT name = Andrew, second_name = Nelitskiy, is_male = 1, telegram_id = 123, date_of_birth = 30:09:2004

*/