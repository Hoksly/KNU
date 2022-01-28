#include "select.hpp"


std::string give_selected_results(std::vector<Person*> &printed, std::vector<std::string> params)
{
    int par_sz = params.size(), pr_sz = printed.size();
    std::string s = "";
    //std::vector<std::vector<std::string>> s(pr_sz, std::vector<std::string>(par_sz));
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
                s += std::to_string(printed[i]->telegram_id) + " ";
                     
        
        }
        s += "\n";
    }
    //cout << endl;
    //cout << s << endl;
    return s;

   
    
    
}

int command_select(str_with_pos &ch,  std::vector<Person*> &people, int &i)
{
    std::vector <std::string> params_list;
    std::vector<std::pair<std::string, std::string>> where_list;
    std::vector<Person*> res;


    find_params(ch, params_list, i);
    std::string where = "";
    find_param(ch, where, i); // searching for WHERE param
   
    if(where == WHERE_COMMAND)
        {find_params_and_values(ch, where_list, i);}
    
    int sz = people.size();
    for(int i = 0; i < sz; i++)
    {
        if(matching(people[i], where_list))
            res.push_back(people[i]);
    }
    

    std::string s = give_selected_results(res, params_list);
    std::cout << std::endl << s;
    return 0;
    // SELECT name WHERE date_of_birth = 00:00:0000
    

}
 
