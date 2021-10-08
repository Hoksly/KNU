#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;
const unsigned int MAX_VAR_LEN = 56;
const unsigned int MAX_TYPE_LEN = 56;
const unsigned int MAX_LEN_LINE= 256;
const unsigned int MAX_QUANT_OF_VAR = 40;
const unsigned int MAX_LEN_FILE = 1000;
const unsigned int MAX_STRING_AS_VALUE_LEN = 128;
const unsigned int MAX_FUNCTION_NAME_LEN = 56;

const char STRING_TYPE_NAME[MAX_TYPE_LEN] = "string";
const char INT_TYPE_NAME[MAX_TYPE_LEN] = "int";



map <char[MAX_VAR_LEN], char[MAX_TYPE_LEN]> Variables;
map <char[MAX_VAR_LEN], int> Variables_int_values;
map <char[MAX_VAR_LEN], char[MAX_STRING_AS_VALUE_LEN]> Variables_string_values;
vector<char[MAX_FUNCTION_NAME_LEN]> Functions_name;

//specific container, which would contain pointers to containers with values -> function of clearing values, when it's changing type



void read_file(char *filename, char out_str[][256])
{
    char line[256];
    
    
    char q;
    int i, f = 0;
    FILE *file = fopen(filename, "r");
    do{
        q = fgetc(file);

        if (q == -1)
            break; 

        i = 0;
        while (q != '\n' && q != -1)
        {
            out_str[f][i] = q;
            //std::cout << (int)q << std::endl;
            ++i;
            q = fgetc(file);

        } 
        
        //std::cout << out_str[f] << '\n';
        f++;
    }while(true);

    fclose(file);

}

struct list_var
{
    string type;
    string *variables;
};

struct var
{
    char name[MAX_VAR_LEN];
    char type[MAX_VAR_LEN];
};




char  *clear_spaces(char *ch)
{
    while (*ch == ' ')
        ch++;
    return ch;
}

char *clear_spaces_and_idk_its_name(char *ch)
{
    while (*ch == ' ' || *ch == '\n')
        ch++;

    return ch;
}

int const_identificator(char *ch, char *ret)
{
    while('0' < *ch < '9' || *ch == '.')
    {
        *ret = *ch;
        ret++;
        ch++;
    }
    return 0;
}

int const_string(char *ch, char* ret)
{
    while(*ch != '"')
    {
        if (*ch == '\n')
        {
            cout << "Error while parsing string. Are you missing symbol" << '"' << " ?" << endl;; 
            return 1;
        } 
        *ch = *ret;

    }

    return 0;
}

int var_identificator(char *ch, char *ret)
{
    
    clear_spaces_and_idk_its_name(ch);
    
    if(!(64<*ch<91 || 96<*ch<123))
        return -1;
    
    *ret = *ch;
    ch++;
    ret++;

    
    while (('0' <= *ch && *ch <= '9') || ('a' <= *ch && *ch <= 'z') || ('A' <= *ch && *ch <= 'Z'))
    {
        //cout << (int) *ch << endl;
        *ret = *ch;
        ch++;
        ret++;
        
    }

    return 0;
}

int type_identificator(char *ch, char *ret)
{
    return var_identificator(ch, ret);
}


int oprtr(char *ch, char* ret)
{
    char *t = clear_spaces(ch);
    if(!(*t == '+'|| *t == '/' || *t == '-' || *t == '*' || *t == '='))
    {
        return 1;
    }

    *ret = *t;   

    return 0;
}

bool is_declarated_function(char *var_name) // 
{
    /*
    return statements:
    1 - is in list of function names
    0 - is not in list of function names
    */
    //checking it

    return false;
}

bool is_declarated_variable(char *var)
{


    for(auto it = Variables.begin(); it != Variables.end(); ++it)
    {
        if(*(*it).first == *var) // it - pointer to specific pair from the map. We take first from it (char[]) and
            return true;         // compare it's value (operator *) with a value of var (operator *val) 
    }  
    return false;
}

int clear_or_create_new_int_variable(char *var_name)
{
    auto var_pointer = Variables_int_values.begin();

    bool exist = false;
    for(; var_pointer != Variables_int_values.end(); var_pointer++)
    {
        if(*(*var_pointer).first == *var_name)
        {
            exist = true; break;
        }

    }

    if(!exist)
    {
        char *var_copy = new char[MAX_VAR_LEN];

        Variables_int_values.insert(pair<char, int>(var_copy, 0));
    }

}

int compare_types(char *var1, char *var2, int &line_number, char *res)
{
    auto var_1_pointer = Variables.begin();
    auto var_2_pointer = Variables.begin();
    for(; var_1_pointer != Variables.end(); ++var_1_pointer)
    {
        if(*(*var_1_pointer).first == *var1) 
            break;       
    }  
    for(; var_2_pointer != Variables.end(); ++var_2_pointer)
    {
        if(*(*var_2_pointer).first == *var2) 
            break;         
    }  

    if(*(*var_2_pointer).second == *(*var_2_pointer).second)
        if(*(*var_2_pointer).second == *STRING_TYPE_NAME)
        {
            *res = *STRING_TYPE_NAME;
            return 0;
        }
        else if(*(*var_2_pointer).second == *INT_TYPE_NAME) //Here is a question: how would it works? 
        {
            *res =  *INT_TYPE_NAME;
            return 0;
        }
    else
    {
        cout << "Error in line: " << line_number << " operation '+' is not defined for clases ";
        cout << (*var_2_pointer).second << " and " << (*var_1_pointer).second << endl;
        return 1;
    }

}

int operation_plus(char *var1, char *var2, char *var3, int &line_number)
{
    char type_of_result[MAX_TYPE_LEN];
    if(compare_types(var2, var3, line_number, type_of_result) == 1);
        return 1;

    if(*type_of_result == *STRING_TYPE_NAME)
    {

    }    

    return 0;
}

int operation_minus(char *var1, char *var2, char *var3, int &line_number)
{

    return 0;
}

int operation_multiplication(char *var1, char *var2, char *var3, int &line_number)
{

    return 0;
}

int operation_division_type_1(char *var1, char *var2, char *var3, int &line_number)
{

    return 0;
}





int simple_operation(char *ch, char *var1, int &line_number)
{
    char var2[MAX_VAR_LEN], var3[MAX_VAR_LEN];
    clear_spaces(ch);
    var_identificator(ch, var2);

    if(!is_declarated_variable(var2)){
        cout <<"Error in " << line_number << "line: "<< var2 << " is not declarated is this scope" << endl; 
        return 1;}

    clear_spaces(ch);
    char oper[1];
    oprtr(ch, oper);

    if(oper[0] == '=') 
        cout <<"Error in " << line_number << "line: "<< "Second operator '='";
    
    clear_spaces(ch);

    var_identificator(ch, var3);
    
    if(!is_declarated_variable(var3)){
        cout <<"Error in " << line_number << "line: "<< var2 << " is not declarated is this scope" << endl; 
        return 1;}


    if(oper[0] == '+')
        operation_plus(var1, var2, var3, line_number);

    else if(oper[0] == '-')
        operation_minus(var1, var2, var3, line_number);

    else if(oper[0] == '*')
        operation_multiplication(var1, var2, var3, line_number);

    else if(oper[0] == '/')
        operation_division_type_1(var1, var2, var3, line_number);

    

    
    



    return 0;
}


int work_with_one_line(char *ch, int number_of_line)
{

    char var1 [MAX_VAR_LEN];
    if(var_identificator(ch, var1) == 1);
        cout << "Error in string " << number_of_line << endl; //it should call real error. But how? Additional file with including it?
    
    if(is_declarated_function(var1)){}
        //working with specific function, needs an update later

    char oprt[1];
    if(oprtr(ch, oprt) == 1);
        cout << "error while parsing. Did you miiss operator?" << endl; // also should call real error
    
    if(oprt[0] == '=')
    {
        
        clear_spaces(ch);
        if(*ch == '"')
        {

        }
        else if('0' <= *ch <= '9')
        {

        }
        else
        {

        }
    }
    else
    {
        cout << "Wrong operator in line " << number_of_line  << " Did you mean '=' ?" << endl;
        return 1;
    }
    






}



void process()
{
    /*
    vector <char[MAX_VAR_LEN]> variables;
    
    char file[MAX_LEN_FILE][MAX_LEN_LINE];
    read_file("example.py", file);
    char s[MAX_VAR_LEN];
    char *uk = clear_spaces_and_idk_its_name(file[0]);
    //;
    var_identificator(uk, s);
    cout << s << endl;
    */

   
}

int main()
{
    process();
}


/*
line counter (when ch == '\n' => counter ++)
errors generators!!!
working from file


*/
