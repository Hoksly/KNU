#include "delete.hpp"


int delete_person(std::vector<Person*> &people, std::vector<Person*> &to_delete)
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

int delete_command(str_with_pos &ch,  std::vector<Person*> &people, int &i)
{
    std::string where;
    find_param(ch, where, i); // searching for WHERE param
    std::vector<std::pair<std::string, std::string>> what_to_delete;

    if(where == WHERE_COMMAND)
        {find_params_and_values(ch, what_to_delete, i);}
    
    else
        std::cout << "Usage: DELETE WHERE <param = value>";
    
    std::vector<Person*> res;
    int sz = people.size();
    for(int i = 0; i < sz; i++)
    {
        if(matching(people[i], what_to_delete))
            res.push_back(people[i]);
    }

    delete_person(people, res);

    return 0;

}

