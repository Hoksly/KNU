#include <stdio.h>
#include <string.h>
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
const int UNIVERSAL_LEN = 40;

char CLOSE_CONDITION[] = ":q";
char CLOSE_CONDITION_UPPER[] = ":Q";

string HELP_CONDITION = "--help";

const int MAX_VALUE_LEN = 40;
const int MAX_PARAM_LEN = 20;
const int MAX_BOOL_LEN = 2;
//commands
char INSERT_COMMAND[] = "INSERT";
char DELETE_COMMAND[] = "DELETE";
char UPDATE_COMMAND[] = "UPDATE";
char SELECT_COMMAND[] = "SELECT";
const string WHERE_COMMAND = "WHERE";
char WRITE_DOWN_COMMAND[] = "WRITE_DOWN";

//other variables
string EMPTY_STRING = "";
string NAME_PARAM = "name";
string SECOND_NAME_PARAM = "second_name";
string IS_MALE_PARAM = "is_male";
string TELEGRAM_ID_PARAM = "telegram_id";
string DATE_OF_BIRTH_PARAM = "date_of_birth";

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
        //cout << s[pos] << endl;
        return s[pos];
    }
    void clear()
    {
        pos = 0;
        s = "";
    }

};
/*
struct Person
{   
    char *name = new char[MAX_NAME_LEN];
    char *second_name = new char[MAX_NAME_LEN];
    bool is_male;
    long telegram_id;
    char *date_of_birth = new char[MAX_DATE_OF_BIRTH_LEN];

};
*/
struct Person
{
    char name[MAX_NAME_LEN];
    char second_name[MAX_NAME_LEN];
    bool is_male;
    long telegram_id;
    char date_of_birth[MAX_DATE_OF_BIRTH_LEN];
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
/*
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
*/

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



int add_new_person(vector<Person*> *people, string name, string second_name, string date_of_birthday, long telegram_id, bool is_male)
{
    Person *ptr = new Person;
    for(int i = 0; i < MAX_NAME_LEN; i++)
        ptr->name[i] = name[i];
    for(int i = 0; i < MAX_NAME_LEN; i++)
        ptr->second_name[i] = second_name[i];
    for(int i = 0; i < MAX_DATE_OF_BIRTH_LEN; i++)
        ptr->date_of_birth[i] = date_of_birthday[i];
    
    ptr->is_male = is_male;
    ptr->telegram_id = telegram_id;
    people->push_back(ptr);

    //cout << ptr->name << endl;
    //cout << ptr->second_name << endl;
    //cout << ptr->telegram_id << endl;
    //cout << ptr->date_of_birth << endl;

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


int find_command(str_with_pos &ch, char *command, int &i)
{
    int q = 0, s_len = ch.s.length();
    while(q < s_len && ch.get_ch_nm() != ' ' && ch.get_ch_nm() != 0)
    {
        *command = toupper(ch.get_ch());
        
        command++;
        if(i++ > MAX_LINE_LEN)
            {cout <<"max line len: " << MAX_LINE_LEN << endl; return 1;}
    }
    if(q >= 15)
        {cout << "Error while parsing command (command length >)"; return 1;}
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

int find_param(str_with_pos &ch, string &res, int &i)
{
    clear_spaces(ch, i);
    int q = 0;
    //cout<<"s: " << ch.pos << endl;
    while(!isblank(ch.get_ch_nm()) && ch.get_ch_nm() != ',' && ch.get_ch_nm() != 0)
    {
        
        res.push_back(ch.get_ch());
        //cout << "q: " << (int) ch.get_ch_nm() << endl;
        q++;
        
        if(i > MAX_LINE_LEN)
            {cout <<"max line len: " << MAX_LINE_LEN << endl; return 1;}
    }
    //cout << "HER: " << res.length() << endl;
    clear_spaces(ch, i);
    //select name
    return 0;
}

int find_params(str_with_pos &ch, vector<string> &list_of_params, int &i)
{
    
    string s;
    clear_spaces(ch, i);
    while (true)
    {
    
    s = "";
    find_param(ch, s, i);
    
    list_of_params.push_back(s);
    
    
    if(ch.get_ch_nm() != ',' || ch.get_ch_nm() == '\0')
        return 0;

    ch.pos++; // symbol ','
    clear_spaces(ch, i);
    if(i++ > MAX_LINE_LEN)
        {cout <<"max line len: " << MAX_LINE_LEN << endl; return 1;}
    
    }
    clear_spaces(ch, i);
    

    return 0;
}


int find_params_and_values(str_with_pos &ch, vector<pair<string, string>> &list_of_params, int &i)
{
    
    while(true)
    {   
        string param = "", value = "";
        find_param_and_value(ch, param, value, i);
        
        pair<string, string> A =  make_pair(param, value);
        
        
        list_of_params.push_back(A);
        
        
        
        clear_spaces(ch, i);
       
        
        if(ch.get_ch_nm() != ',' || ch.get_ch_nm() == '\0')
            return 0;

        //ch.pos++; // symbol ','
        
        if(ch.get_ch_nm() == ',')
            ch.pos++; 
        
        

        clear_spaces(ch, i);
        if(i++ > MAX_LINE_LEN)
            {cout <<"max line len: " << MAX_LINE_LEN << endl; return 1;}

    }
    
   
}
string find_val(vector<pair<string, string>> A, string target)
{
    for(auto i = A.begin(); i != A.end(); i++)
        if(i->first == target) 
            return i->second;

    string s = "";
    return s;
    
}

int command_insert(str_with_pos &ch, vector<Person*> *people, int &i)
{
    vector <pair<string, string>> params_list;
    find_params_and_values(ch, params_list, i);
    
    //char *is_male = new char[MAX_BOOL_LEN];
    //char *date_of_birth = new char[MAX_DATE_OF_BIRTH_LEN];
    string  date_of_birth;
    
    if(EMPTY_STRING != find_val(params_list, NAME_PARAM) && EMPTY_STRING != find_val(params_list, SECOND_NAME_PARAM))
    {
        long telegram_id;
        bool is_realy_male = (bool) stoi(find_val(params_list, IS_MALE_PARAM), 0, 10);
        date_of_birth = find_val(params_list, DATE_OF_BIRTH_PARAM);
        //is_male = find_val(params_list, IS_MALE_PARAM);

        if(find_val(params_list, TELEGRAM_ID_PARAM) != EMPTY_STRING)
            telegram_id = stol(find_val(params_list, TELEGRAM_ID_PARAM), 0, 10);
        else
            telegram_id = 0;
        
        if(date_of_birth[0] < 0)
            date_of_birth = EMPTY_STRING;
        
        
        
    
        add_new_person(people,find_val(params_list, NAME_PARAM), 
        find_val(params_list, SECOND_NAME_PARAM), 
        date_of_birth, telegram_id, is_realy_male);


    }
    else
    {
        cout << "Error in insert command: gap 'name' and 'second_name' cannot be empty or been ignored" << endl;
        return 1;
    }
   

    
    

   return 0;
}
string ch_to_srt(char *ch)
{
    string s = "";
    while(*ch)
        {s.push_back(*ch); ch++;}
    
    return s;

}
bool check_birth(string main, string src)
{
    bool res = true;
    for(int i = 0; i < MAX_DATE_OF_BIRTH_LEN; i++)
    {
        if(src[i] == src[i+1]&& src[i] == '0')
            {i++; continue;}
        
        if(src[i] != main[i])
            res = false;
        
    }
    return res;

}
int strmatch(string s1, char * s2)
{
    //cout << s2 << ' ' << strlen(s2) << endl;
    //cout<<"HERE: " << s2 << endl;
    if(s1.size() != strlen(s2))
        return 1;
    
    int sz = s1.size();
    for(int i = 0; i < sz; i++)
        if(s1[i] != s2[i]) 
            return s1[i] - s2[sz];
    return 0;
}

bool matching(Person* prs, const vector<pair<string, string>> &params)
{
    bool res = true;
    for(int i = 0; i < params.size(); i++)
    {
        if(params[i].first == NAME_PARAM)
        {
            if(strmatch(params[i].second, prs->name))
                {res = false;}
        }
        else if(params[i].first == SECOND_NAME_PARAM)
        {
            if(strmatch(params[i].second, prs->second_name))
                {res = false;}
        }
        else if(params[i].first == TELEGRAM_ID_PARAM)
        {
            if(stol(params[i].second, 0, 10) != prs->telegram_id)
                {res = false;}
        }
        else if(params[i].first == IS_MALE_PARAM)
        {
            if((bool) params[i].second[0] == prs->is_male)
                {res = false;}
        }
        else if(params[i].first == DATE_OF_BIRTH_PARAM)
        {
            if(!check_birth(ch_to_srt(prs->date_of_birth), params[i].second))
                res = false;
        }  
        else
        {
            cout << "Couldn\'t recognize parametr after WHERE: " << params[i].first << endl;
            return 1;
        } 

    }
    
    return res;
}

string convert_mas_to_str(vector<vector<string>> s)
{
    /*
    name, second_name
    name, second_name
    name, second_name
    
    i - quant of params
    j - quant of people
    */
    string res = "";
    int j = (!s.empty())? s.size(): 0, i;
    if(j != 0)
        i = (!s[0].empty())? s[0].size():0;
    else 
        i = 0;
    cout << i<< ' ' << j << endl;
    for(int p = 0; p < j; p++)
    {
        for(int q = 0; q < i; q++)
        {
            res += s[p][q] + " ";
            cout<<"adding: " << s[p][q] << endl;
        }
        res += "\n";
    }
    return res;
}

string give_selected_results(vector<Person*> &printed, vector<string> params)
{
    int par_sz = params.size(), pr_sz = printed.size();
    string s = "";
    //vector<vector<string>> s(pr_sz, vector<string>(par_sz));
    int pers_sz = printed.size(), param_sz = params.size();

    for(int i = 0; i < pers_sz; i++)
    {
        for(int j = 0; j < param_sz; j++)
        {
            if(params[j] == NAME_PARAM)
                {s += printed[i]->name;
                s += " "; }
            if(params[j] == SECOND_NAME_PARAM)
                {s += printed[i]->second_name;
                s += " "; }
            if(params[j] == DATE_OF_BIRTH_PARAM)
                {s += printed[i]->date_of_birth;
                s += " "; }
            if(params[j] == IS_MALE_PARAM)
                s += (printed[i]->is_male)? "male ": "female ";
            if(params[j] == TELEGRAM_ID_PARAM)
                s +=to_string(printed[i]->telegram_id) + " ";
                     
        
        }
        s += "\n";
    }
    //cout << endl;
    //cout << s << endl;
    return s;

   
    
    
}

int command_select(str_with_pos &ch,  vector<Person*> &people, int &i)
{
    vector <string> params_list;
    vector<pair<string, string>> where_list;
    vector<Person*> res;


    find_params(ch, params_list, i);
    string where = "";
    find_param(ch, where, i); // searching for WHERE param
   
    if(where == WHERE_COMMAND)
        {find_params_and_values(ch, where_list, i);}
    
    int sz = people.size();
    for(int i = 0; i < sz; i++)
    {
        if(matching(people[i], where_list))
            res.push_back(people[i]);
    }
    

    string s = give_selected_results(res, params_list);
    cout << endl << s;
    return 0;
    // SELECT name WHERE date_of_birth = 00:00:0000
    

}


void strcp(char * s1, string s2)
{
    memset(s1, '\0', strlen(s1));
    int sz = s2.size();
    
    for(int i = 0; i < sz; i++)
        s1[i] = s2[i];
   
    
}

int update_values( vector<Person*> &people,  vector<pair<string, string>> to_update)
{
    int update_sz = to_update.size();
    int people_sz = people.size();

    for(int i = 0; i < update_sz; i++)
    {
        if(to_update[i].first == NAME_PARAM)
            for(int j = 0; j < people_sz; j++)
                strcp(people[j]->name, to_update[i].second);
        if(to_update[i].first == SECOND_NAME_PARAM)
            for(int j = 0; j < people_sz; j++)
                strcp(people[j]->second_name, to_update[i].second);  
        
        if(to_update[i].first == DATE_OF_BIRTH_PARAM)
            for(int j = 0; j < people_sz; j++)
                strcp(people[j]->date_of_birth, to_update[i].second);  

        if(to_update[i].first == TELEGRAM_ID_PARAM)
            for(int j = 0; j < people_sz; j++)
                people[j]->telegram_id = stol(to_update[i].second, 0, 10);  
        if(to_update[i].first == NAME_PARAM)
            for(int j = 0; j < people_sz; j++)
                people[j]->is_male = (bool) to_update[i].second[0];       
            
        
    }
    return 0;
}

int command_update(str_with_pos &ch,  vector<Person*> &people, int &i)
{
    vector<pair<string, string>> to_what_update;
    vector<pair<string, string>> where_update;
    string where;
    vector<Person*> res;

    find_params_and_values(ch, to_what_update, i);
    find_param(ch, where, i); // searching for WHERE param
    if(where == WHERE_COMMAND)
        {find_params_and_values(ch, where_update, i);}
    
    else
        cout << "Usage: UPDATE <param = value> WHERE <param = value>";
    
    int sz = people.size();
    for(int i = 0; i < sz; i++)
    {
        if(matching(people[i], where_update))
            res.push_back(people[i]);
    }
    cout << (res.empty())? "EMPTY": res[0]->name;
    cout << endl;
    update_values(res, to_what_update);
    //UPDATE name = Bily WHERE name = Billy
    return 0;
}

int delete_person(vector<Person*> &people, vector<Person*> &to_delete)
{
    
    for(auto i = people.begin(); i != people.end(); i++)
    {
        for(auto j = to_delete.begin(); j != to_delete.end(); j++)
        {
            if(*i == *j)
                {people.erase(i); i--;}
        }
    }
    return 0;
}

int delete_command(str_with_pos &ch,  vector<Person*> &people, int &i)
{
    string where;
    find_param(ch, where, i); // searching for WHERE param
    vector<pair<string, string>> what_to_delete;

    if(where == WHERE_COMMAND)
        {find_params_and_values(ch, what_to_delete, i);}
    
    else
        cout << "Usage: DELETE WHERE <param = value>";
    
    vector<Person*> res;
    int sz = people.size();
    for(int i = 0; i < sz; i++)
    {
        if(matching(people[i], what_to_delete))
            res.push_back(people[i]);
    }

    delete_person(people, res);

    return 0;

}


int parse_command(str_with_pos &input, vector<Person*> *people)
{

    char main_command[MAX_COMMAND_LEN];
    int i = 0;
    find_command(input, main_command, i);
    clear_spaces(input, i);
    //cout << "String: " << input.s << endl;
    //cout <<"Comand: "<< main_command << endl;

    if(!strcmp(main_command, WRITE_DOWN_COMMAND))
    {
        //cout << "HERE" << endl;
        write_in_file(FILENAME, people);
    }
    
    else if(!strcmp(main_command, INSERT_COMMAND))
    {
        
        command_insert(input, people, i);
    }
    
    else if(!strcmp(main_command, UPDATE_COMMAND))
    {
        command_update(input, *people, i);
    }
    
    else if(!strcmp(main_command, DELETE_COMMAND))
    {
        delete_command(input, *people, i);   
    }
    
    else if(!strcmp(main_command, SELECT_COMMAND))
    {
        
        command_select(input, *people, i);
    }
    
    else
    {cout << "Error while parsing command: couldn't recognize command: "<< main_command << endl; return 1;}

    
    return 0; //SELECT name, second_name WHERE name = Andrew
}

void print_db(vector<Person*> people)
{
    for(int i = 0; i < people.size(); i++)
    {
        cout << people[i]->name << endl;
        cout << people[i]->second_name << endl;
        cout << people[i]->is_male<< endl;
        cout << people[i]->date_of_birth << endl;
        cout << people[i]->telegram_id << endl;
    }
}

void show_all_help()
{
    cout << endl <<endl;
    cout <<"To select something: SELECT param1, param2... WHERE statement1 = s-th1, statement2 = s-th2" << endl;
    cout <<"To delete something: DELETE WHERE cond1, cond2..." << endl;
    cout << "To insert something: INSERT param1 = value1, param2 = value2..." << endl;
    cout << "To update something: UPDATE param1 = value1, param2 = value2... WHERE condition1, condition2... ";
    cout << "To write changes: WRITE_DOWN (automaticly write when close)" << endl;
    cout << "To exit program: '"<<CLOSE_CONDITION <<'\''<< endl;
    cout << "Additional information about all functions: <Command> --help" << endl << endl;
}

//int process(int arg, char *argv[])
int process()
{
    vector<Person*> people;
    vector<Person*> *ptr = &people;

    if(read_file(FILENAME, &people))
        return 1;

   
    //simple_write();
    //Person pp = *(people[0]);
    //Debug
    /*
    cout << people.size() << endl;
    for(int i = 0; i < people.size(); i++)
    {
        Person pp = *(people[i]);
        cout << pp.name << ' ' << pp.second_name << ' ' << pp.date_of_birth << endl;
    }
    */
    
    
    
    
    str_with_pos input;
    while (true)
    {
        input.clear();
        getline(cin, input.s);
        //cout<< "line: " << input.s << endl;
        
        if(input.s == CLOSE_CONDITION || input.s == CLOSE_CONDITION_UPPER)
        {
            print_db(people);
            write_in_file(FILENAME, &people);
            cout << "Exiting..." << endl;
            break;
        }
        else if(input.s == HELP_CONDITION)
            show_all_help();
        
        else
            parse_command(input, ptr);


    }
   

    return 0;
}


int main(int arg, char *argv[])
{
    
    //process(arg, argv);
    process();
    
    //simple_write();
    return 0;   

}

/*
Adding new person with command insert not wotking properly, debug with cin

INSERT name = Van, second_name = Darkholm, is_male = 1, telegram_id = 123, date_of_birth = 12:07:1987

*/