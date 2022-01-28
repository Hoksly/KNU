#include "insert.hpp"


int command_insert(str_with_pos &ch, std::vector<Person*> *people, int &i)
{
    std::vector <std::pair<std::string, std::string>> params_list;
    find_params_and_values(ch, params_list, i);

    //char *is_male = new char[MAX_BOOL_LEN];
    //char *date_of_birth = new char[MAX_DATE_OF_BIRTH_LEN];
    std::string  date_of_birth;
    
    if(EMPTY_STRING != find_val(params_list, NAME_PARAM) && EMPTY_STRING != find_val(params_list, SECOND_NAME_PARAM))
    {
        long telegram_id;
        bool is_realy_male = (bool) std::stoi(find_val(params_list, IS_MALE_PARAM), 0, 10);
        date_of_birth = find_val(params_list, DATE_OF_BIRTH_PARAM);
        //is_male = find_val(params_list, IS_MALE_PARAM);

        if(find_val(params_list, TELEGRAM_ID_PARAM) != EMPTY_STRING)
            telegram_id = std::stol(find_val(params_list, TELEGRAM_ID_PARAM), 0, 10);
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
        std::cout << "Error in insert command: gap 'name' and 'second_name' cannot be empty or been ignored" << std::endl;
        return 1;
    }
   

    
    

   return 0;
} 
