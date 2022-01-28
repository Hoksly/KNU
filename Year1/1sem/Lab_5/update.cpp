#include "update.hpp"

int update_values(std::vector<Person*> &people,  std::vector<std::pair<std::string, std::string>> to_update)
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

int command_update(str_with_pos &ch,  std::vector<Person*> &people, int &i)
{
    std::vector<std::pair<std::string, std::string>> to_what_update;
    std::vector<std::pair<std::string, std::string>> where_update;
    std::string where;
    std::vector<Person*> res;

    find_params_and_values(ch, to_what_update, i);
    find_param(ch, where, i); // searching for WHERE param
    if(where == WHERE_COMMAND)
        {find_params_and_values(ch, where_update, i);}
    
    else
        std::cout << "Usage: UPDATE <param = value> WHERE <param = value>";
    
    int sz = people.size();
    for(int i = 0; i < sz; i++)
    {
        if(matching(people[i], where_update))
            res.push_back(people[i]);
    }
    std::cout << (res.empty())? "EMPTY": res[0]->name;
    std::cout << std::endl;
    update_values(res, to_what_update);
    //UPDATE name = Bily WHERE name = Billy
    return 0;
}
 
