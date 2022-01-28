#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>

#include "globals.hpp"
#include "classes.hpp"
#include "file.hpp"
#include "functions.hpp"

#include "insert.hpp"
#include "select.hpp"
#include "update.hpp"
#include "delete.hpp"

using namespace std;





// INSERT name = Van, second_name = Darkholm, is_male = 1, telegram_id = 123456, date_of_birth = 24:10:1972




int parse_command(str_with_pos &input, vector<Person*> *people)
{

    char main_command[MAX_COMMAND_LEN];
    int i = 0;
    find_command(input, main_command, i);
    clear_spaces(input, i);
    

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

    
    return 0; //SELECT name, second_name WHERE name = Billy
}





int process()
{
    vector<Person*> people;
    vector<Person*> *ptr = &people;

    if(read_file(FILENAME, &people))
        return 1;


    
    
    str_with_pos input;
    while (true)
    {
        input.clear();
        getline(cin, input.s);
        //cout<< "line: " << input.s << endl;
        
        if(input.s == CLOSE_CONDITION || input.s == CLOSE_CONDITION_UPPER)
        {
            //print_db(people);
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