#include "functions.hpp"

int add_new_person(std::vector<Person*> *people, std::string name, std::string second_name, std::string date_of_birthday, long telegram_id, bool is_male)
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
            {std::cout <<"max line len: " << MAX_LINE_LEN << std::endl;}
        
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
            {std::cout <<"max line len: " << MAX_LINE_LEN << std::endl; return 1;}
    }
    if(q >= 15)
        {std::cout << "Error while parsing command (command length >)"; return 1;}
    *command = '\0';
    
    return 0;
}
 
int find_param_and_value(str_with_pos &ch, std::string &param, std::string &value, int &i)
{
    char s;
    clear_spaces(ch, i);
    while(!isblank(ch.get_ch_nm()))
    {
        
        param += ch.get_ch();
        
        
        if(i > MAX_LINE_LEN)
            {std::cout <<"max line len: " << MAX_LINE_LEN << std::endl; return 1;}
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
            {std::cout <<"max line len: " << MAX_LINE_LEN << std::endl; return 1;}
        }
    }
    //cout << "OUT" << endl;
    return 0;
}

std::string covert_char_to_string(char *param)
{
    std::string s;
    for(; *param; param++)
        s += *param;
    //cout << s.length() << endl;
    return s;
}

int find_param(str_with_pos &ch, std::string &res, int &i)
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
            {std::cout <<"max line len: " << MAX_LINE_LEN << std::endl; return 1;}
    }
    //cout << "HER: " << res.length() << endl;
    clear_spaces(ch, i);
    //select name
    return 0;
}

int find_params(str_with_pos &ch, std::vector<std::string> &list_of_params, int &i)
{
    
    std::string s;
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
        {std::cout <<"max line len: " << MAX_LINE_LEN << std::endl; return 1;}
    
    }
    clear_spaces(ch, i);
    

    return 0;
}


int find_params_and_values(str_with_pos &ch, std::vector<std::pair<std::string, std::string>> &list_of_params, int &i)
{
    
    while(true)
    {   
        std::string param = "", value = "";
        find_param_and_value(ch, param, value, i);
        
        std::pair<std::string, std::string> A =  std::make_pair(param, value);
        
        
        list_of_params.push_back(A);
        
        
        
        clear_spaces(ch, i);
       
        
        if(ch.get_ch_nm() != ',' || ch.get_ch_nm() == '\0')
            return 0;

        //ch.pos++; // symbol ','
        
        if(ch.get_ch_nm() == ',')
            ch.pos++; 
        
        

        clear_spaces(ch, i);
        if(i++ > MAX_LINE_LEN)
            {std::cout <<"max line len: " << MAX_LINE_LEN << std::endl; return 1;}

    }
    
   
}
std::string find_val(std::vector<std::pair<std::string, std::string>> A, std::string target)
{
    for(auto i = A.begin(); i != A.end(); i++)
        if(i->first == target) 
            return i->second;

    std::string s = "";
    return s;
    
}

std::string ch_to_srt(char *ch)
{
    std::string s = "";
    while(*ch)
        {s.push_back(*ch); ch++;}
    
    return s;

}


bool check_birth(std::string main, std::string src)
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
int strmatch(std::string s1, char * s2)
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

bool matching(Person* prs, const std::vector<std::pair<std::string, std::string>> &params)
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
            if(std::stol(params[i].second, 0, 10) != prs->telegram_id)
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
            std::cout << "Couldn\'t recognize parametr after WHERE: " << params[i].first << std::endl;
            return 1;
        } 

    }
    
    return res;
}

std::string convert_mas_to_str(std::vector<std::vector<std::string>> s)
{
    /*
    name, second_name
    name, second_name
    name, second_name
    
    i - quant of params
    j - quant of people
    */
    std::string res = "";
    int j = (!s.empty())? s.size(): 0, i;
    if(j != 0)
        i = (!s[0].empty())? s[0].size():0;
    else 
        i = 0;
    std::cout << i<< ' ' << j << std::endl;
    for(int p = 0; p < j; p++)
    {
        for(int q = 0; q < i; q++)
        {
            res += s[p][q] + " ";
            std::cout<<"adding: " << s[p][q] << std::endl;
        }
        res += "\n";
    }
    return res;
}

void strcp(char * s1, std::string s2)
{
    memset(s1, '\0', strlen(s1));
    int sz = s2.size();
    
    for(int i = 0; i < sz; i++)
        s1[i] = s2[i];
   
    
}

void show_all_help()
{
    std::cout<< std::endl<<std::endl;
    std::cout<<"To select something: SELECT param1, param2... WHERE statement1 = s-th1, statement2 = s-th2" << std::endl;
    std::cout<<"To delete something: DELETE WHERE cond1, cond2..." << std::endl;
    std::cout<< "To insert something: INSERT param1 = value1, param2 = value2..." << std::endl;
    std::cout<< "To update something: UPDATE param1 = value1, param2 = value2... WHERE condition1, condition2... ";
    std::cout<< "To write changes: WRITE_DOWN (automaticly write when close)" << std::endl;
    std::cout<< "To exit program: '"<<CLOSE_CONDITION <<'\''<< std::endl;
    std::cout<< "Additional information about all functions: <Command> --help" << std::endl<< std::endl;
}


void print_db(std::vector<Person*> people)
{
    for(int i = 0; i < people.size(); i++)
    {
        std::cout << people[i]->name << std::endl;
        std::cout << people[i]->second_name << std::endl;
        std::cout << people[i]->is_male<< std::endl;
        std::cout << people[i]->date_of_birth << std::endl;
        std::cout << people[i]->telegram_id << std::endl;
    }
}