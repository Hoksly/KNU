#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include<string.h>

using namespace std;

const unsigned int MAX_VAR_LEN = 56;
const unsigned int MAX_TYPE_LEN = 56;
const unsigned int MAX_LEN_LINE= 256;
const unsigned int MAX_QUANT_OF_VAR = 40;
const unsigned int MAX_LEN_FILE = 1000;
const unsigned int MAX_STRING_AS_VALUE_LEN = 128;
const unsigned int MAX_FUNCTION_NAME_LEN = 56;
const unsigned int MAX_NUMBER_LEN = 127;


const char STRING_TYPE_NAME[MAX_TYPE_LEN] = "string";
const char INT_TYPE_NAME[MAX_TYPE_LEN] = "int";
char PRINT_FUNCTION[MAX_FUNCTION_NAME_LEN] = "print";


map <char*, char*> Variables;
map <char*, long*> Variables_int_values;
map <char*, char*> Variables_string_values;
vector <char*> Functions_name(1, PRINT_FUNCTION);



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






 void clear_spaces(char **ch) //using pointer to the pointer
{
    while (**ch == ' ')
        (*ch)++;

}

void clear_spaces_and_idk_its_name(char **ch)
{
    while (**ch == ' ' || **ch == '\n')
        (*ch)++;

 
}
int digit_or_dot(char **ch, char *digit_str, bool *is_double, const int &line_number)
{
    //cout << **ch << endl;
    if(true)
    {
        
        if(**ch == '.')
            *is_double = true;
        *digit_str = **ch;    
        digit_str++;
        (*ch)++;
        return -1;
    }

    else if(**ch == '\n')
    {
        (*ch)++;
        *digit_str = '\0';
        return 0;
    } //End of fucntion 
    
    else
        {
        //cout << "Error while parsing digit in line " << line_number<< " Is it right-writed?" << endl; 
        return 1;}

    
}

int const_identificator(char **ch, long *ret_int,const  int &line_number)
{
    char *ret = new char[MAX_NUMBER_LEN];
    char **pntr = new char*;
    *pntr = ret;
    bool *is_double = new bool;
    *is_double = false;

    while (('0' <= **ch && **ch <= '9') || **ch == '.')
    {
        *ret = **ch;
        ++ret;
        ++(*ch);
        
    }
    *ret = '\0';
    if(!(*is_double))
        {*ret_int = strtol(*pntr, NULL, 10); 
            return 0;}
        
    if(is_double); // It should work with my library for big numbers!

    

    
    return 0;
    
}
bool is_string(char **ch)
{
    return (**ch == '"');
}

bool is_number(char **ch)
{
    return('0' <= **ch && **ch <= '9');
}
int const_string_identificator(char **ch, char* ret, const int &line_number)
{   int counter = 0;
    if(**ch != '"')
        {cout << "Wrong usage of function, which finding string constants! Rewrite core code!" << endl; return 1;}
    (*ch)++;
    
    while(**ch != '"')
    {
        if (**ch == 0)
        {
            cout << "Error while parsing string in line "<<line_number<< ". Have you missed symbol '" << '"' << "'?"<< endl;; 
            return 1;
        } 
        if(counter > MAX_STRING_AS_VALUE_LEN)
            {cout << "Error in line " << line_number << " string is too large (max size - 127 symbols)." << endl; return 1;}
        *ret = **ch;
        ret++;
        (*ch)++;
        ++counter;
    }
    cout << endl;
    
    *ret = '\0';
    return 0;
}

int var_identificator(char **ch, char *ret, const int &line_number)
{
    
    clear_spaces_and_idk_its_name(ch);

    if(!(64<**ch<91 || 96<**ch<123))
        {cout << "Error while parsing line "<< line_number << "identificator names can start only with a letters (a-z), (A-Z)" << endl;
        return 1;}
    
    *ret = **ch;
    (*ch)++;
    ret++;
    
    
    while (('0' <= **ch && **ch <= '9') || ('a' <= **ch && **ch <= 'z') || ('A' <= **ch && **ch <= 'Z'))
    {
        //cout << (int) *ch << endl;
        *ret = **ch;
        (*ch)++;
        ret++;
        
    }
    
    *ret = '\0';
    
    
    
    return 0;
}

int type_identificator(char **ch, char *ret,const int &line_number)
{
    return var_identificator(ch, ret, line_number);
}


int oprtr(char **ch, char* ret, const int &line_number, bool show_message = true)
{
    clear_spaces(ch); //Is it necessary here? YES
    
    if(!(**ch == '+'|| **ch == '/' || **ch == '-' || **ch == '*' || **ch == '='))
    {   
        if(show_message)
            cout << "Error in line " << line_number << " Have you miss operator?" << endl;
        return 1;
         
    }
    
    *ret = **ch;   
    (*ch)++;
    
    *(++ret) = '\0'; //need to be tested, not clearly sure, that it is working properly
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
        if(!strcmp((it->first), var)) // 0 - when they strings are equal, other integer - when not
            return true;         
    }  
    return false;
}

int delete_variable(char *var_name)
{
    auto var_1_pointer = Variables.begin();
    auto var_int_pointer = Variables_int_values.begin();
    auto var_string_pointer = Variables_string_values.begin();

    for(; var_1_pointer != Variables.end(); ++var_1_pointer)
    {
        if(!strcmp(var_1_pointer->first, var_name)) 
            break;       
    }
    if(!strcmp(var_1_pointer->first, var_name))
        Variables.erase(var_1_pointer);
    else{
        cout << "Variable " << var_name << " Has not been declarated yet" << endl; return 1;}
    

    for(; var_int_pointer != Variables_int_values.end(); ++var_int_pointer)
    {
        if(!strcmp(var_int_pointer->first, var_name)) 
            break;       
    }
    if(!strcmp(var_int_pointer->first, var_name))
        Variables_int_values.erase(var_int_pointer);  

    for(; var_string_pointer != Variables_string_values.end(); ++var_string_pointer)
    {
        if(!strcmp(var_string_pointer->first, var_name)) 
            break;       
    }

    if(!strcmp(var_string_pointer->first, var_name))
        Variables_string_values.erase(var_string_pointer); 

    return 0; 
}

int clear_or_create_new_int_variable(char *var_name)
{
    auto var_pointer = Variables_int_values.begin();
    auto var_type_pointer = Variables.begin();

    bool exist_in_int_values = false;
    bool exist_in_vars = false;
    for(; var_pointer != Variables_int_values.end(); var_pointer++)
    {
        if(!strcmp(var_pointer->first, var_name))
        {
            exist_in_int_values = true; break;
        }

    }

    for(; var_type_pointer != Variables.end(); var_type_pointer++)
    {
        if(!strcmp(var_type_pointer->first, var_name)) 
        {
            exist_in_vars = true; break;
        }

    }
    if(!exist_in_vars)
    {
        char *new_var_copy = new char[MAX_VAR_LEN];
        char *new_type_copy = new char[MAX_VAR_LEN];
        strcpy(new_var_copy, var_name);
        strcpy(new_type_copy, INT_TYPE_NAME);
        Variables.insert(pair<char*, char*> (new_var_copy, new_type_copy));
    }
    else
    {
        strcpy(var_type_pointer->second, INT_TYPE_NAME); 
    }

    if(!exist_in_int_values)
    {
        char *var_copy = new char[MAX_VAR_LEN];
        strcpy(var_copy, var_name);
        long* variable = new long;
        
    

        Variables_int_values.insert(pair<char*, long*>(var_copy, variable));
        // not working properly. But why?
        //ret = var_pointer;
    }

    else
    {
        //ret = var_pointer; // var_pointer-> -is just a pointer, so we need to use a * here 
    }

    return 0;

}


int clear_or_create_new_string_variable(char *var_name)
{
    auto var_pointer = Variables_string_values.begin();
    auto var_type_pointer = Variables.begin();

    bool exist = false;
    bool exist_in_vars = false;
    for(; var_pointer != Variables_string_values.end(); ++var_pointer)
    {
        if(!strcmp(var_pointer->first, var_name))
        {
            exist = true; break;
        }

    }

    for(; var_type_pointer != Variables.end(); ++var_type_pointer)
    {
        if(!strcmp(var_type_pointer->first, var_name))
        {
            exist_in_vars = true; break;
        }

    }
    if(!exist_in_vars)
    {
        char *new_var_copy = new char[MAX_VAR_LEN];
        char *new_type_copy = new char[MAX_VAR_LEN];
        //*new_var_copy = *var_name;
        //*new_type_copy = *STRING_TYPE_NAME;
        strcpy(new_type_copy, STRING_TYPE_NAME);
        strcpy(new_var_copy, var_name);
        Variables.insert(pair<char*, char*> (new_var_copy, new_type_copy));
        //cout << "Evrything is alright1"<< endl;
        
        
    }
    else
    {
        strcpy(var_type_pointer->second, STRING_TYPE_NAME); 
        //cout << "Evrything is alright2"<< endl;
    }


    if(!exist)
    {
        char *var_copy = new char[MAX_VAR_LEN];
        strcpy(var_copy, var_name);
        char* variable = new char[MAX_STRING_AS_VALUE_LEN];
        *variable = '\0';
        
    

        Variables_string_values.insert(pair<char*, char*>(var_copy, variable));
        //cout << "Evrything is alright3"<< endl;
        //ret = var_pointer;
    }

    
    

    return 0;

}

int operation_assigment_string_value(char *var_name, char *new_value , const int &line_number)
{
    
    if(clear_or_create_new_string_variable(var_name))
        return 1;
    
    auto var_pointer = Variables_string_values.begin();
    for(; var_pointer != Variables_string_values.end(); ++var_pointer)
    {
        if(!strcmp(var_pointer->first, var_name))
            break;
    }
    
    if(!strcmp(var_pointer->second, var_name))
        {cout << "Error in line " << line_number << "Is declarated in wrong way? (couldn't find it in list of string variables)" << endl; return 1;}    
    strcpy(var_pointer->second, new_value);
    


    return 0;
}

int operation_assigment_int_value(char *var_name, long *new_value , const int &line_number)
{
    if(clear_or_create_new_int_variable(var_name))
        return 1;

    auto var_pointer = Variables_int_values.begin();
    for(; var_pointer != Variables_int_values.end(); ++var_pointer)
    {
        if(!strcmp(var_pointer->first, var_name))
            break;
    }

    *(var_pointer->second) = *new_value;
    
    return 0;

}

int compare_types(char *var1, char *var2, const int &line_number, char *res, const char operation)
{
    auto var_1_pointer = Variables.begin();
    auto var_2_pointer = Variables.begin();
    
    for(; var_1_pointer != Variables.end(); ++var_1_pointer)
    {
        if(!strcmp(var_1_pointer->first, var1)) 
            break;       
    }  
    for(; var_2_pointer != Variables.end(); ++var_2_pointer)
    {
        if(!strcmp(var_2_pointer->first, var2))
            break;         
    }  

    if(!strcmp(var_1_pointer->second, var_2_pointer->second))
    {   
        if(!strcmp(var_2_pointer->second, STRING_TYPE_NAME))
        {
            strcpy(res, STRING_TYPE_NAME);
            return 0;
        }
        else if(!strcmp(var_2_pointer->second, INT_TYPE_NAME)) //Here is a question: how would it works? 
        {
            strcpy(res, INT_TYPE_NAME);
            return 0;
        }
    }
    else
    {   
        cout << "Error in line: " << line_number << " operation '"<< operation<< "' is not defined for clases ";
        cout << var_2_pointer->second << " and " << var_1_pointer->second << endl;
        return 1;
    }
    return 0;
}

int operation_plus(char *var1, char *var2, char *var3, const int &line_number)
{
    char *type_of_result = new char[MAX_TYPE_LEN];
    if(compare_types(var2, var3, line_number, type_of_result, '+') == 1)
        return 1;
    
    if(!strcmp(type_of_result, STRING_TYPE_NAME)) 
    {
        clear_or_create_new_string_variable(var1);

        auto var_pointer1 = Variables_string_values.begin();
        auto var_pointer2 = Variables_string_values.begin();
        auto var_pointer3 = Variables_string_values.begin();
        auto var_pointer1_iterator = Variables_string_values.begin();

  
        for(; var_pointer1_iterator != Variables_string_values.end(); var_pointer1_iterator++)
        {
            if(!strcmp(var_pointer1_iterator->first, var1))
                var_pointer1 = var_pointer1_iterator;
            
            else if(!strcmp(var_pointer1_iterator->first, var2))
                var_pointer2 = var_pointer1_iterator;
            
            else if(!strcmp(var_pointer1_iterator->first, var3))
                var_pointer3 = var_pointer1_iterator;
     
        }
        int sz2 = 0, sz3 = 0;
        char *pn_mas2 = var_pointer2->second, *pn_mas3 = var_pointer3->second;
        
        while(*pn_mas2) //finding an index of '\0' element in mas2. '\0' is recognized as 'false'
            {pn_mas2++; sz2++; }

        while(*pn_mas3) // same for mas3
            {pn_mas3++; sz3++; }
        
        
        if((sz2+sz3 > MAX_STRING_AS_VALUE_LEN - 1)){
            cout << "Error in line " << line_number << " strings " << var2 << " and " << var3 << " are too large to be added" << endl;
            return 1;} 
        strcpy(var_pointer1->second, var_pointer2->second);
        strcat(var_pointer1->second, var_pointer3->second);
        return 0; 

    }

    else if(!strcmp(type_of_result, INT_TYPE_NAME))
    {
        
        clear_or_create_new_int_variable(var1);

        auto var_pointer1 = Variables_int_values.begin();
        auto var_pointer2 = Variables_int_values.begin();
        auto var_pointer3 = Variables_int_values.begin();
        auto var_pointer1_iterator = Variables_int_values.begin();

  
        for(; var_pointer1_iterator != Variables_int_values.end(); var_pointer1_iterator++)
        {
            if(!strcmp(var_pointer1_iterator->first, var1))
                var_pointer1 = var_pointer1_iterator;
            
            else if(!strcmp(var_pointer1_iterator->first, var2))
                var_pointer2 = var_pointer1_iterator;
            
            else if(!strcmp(var_pointer1_iterator->first, var3))
                var_pointer3 = var_pointer1_iterator;
     
        }

        *(var_pointer1->second) = *(var_pointer2->second) + *(var_pointer3->second);
        return 0; 
    }

        

           

    return 0;
}



int operation_minus(char *var1, char *var2, char *var3, const int &line_number)
{
    return 0;
}

int operation_multiplication(char *var1, char *var2, char *var3, const int &line_number)
{

    return 0;
}

int operation_division_type_1(char *var1, char *var2, char *var3, const int &line_number)
{

    return 0;
}


int work_with_function(char **ch, char *function_name, const int &line_number)
{
    return 0;
}




int simple_operation(char **ch, char *var1, const int &line_number)
{
    
    //char var2[MAX_VAR_LEN], var3[MAX_VAR_LEN];
    char *var2 = new char[MAX_VAR_LEN];
    char *var3 = new char[MAX_VAR_LEN];
    
    clear_spaces(ch);
    
    if(is_string(ch))
        {
            
            char *string_value = new char[MAX_STRING_AS_VALUE_LEN];
            
            
            if(const_string_identificator(ch, string_value, line_number) == 1)
                {delete [] string_value; return 1;}
            
            if(operation_assigment_string_value(var2, string_value, line_number) == 1)
                {delete [] string_value; return 1;}

        }

    else if(is_number(ch))
    {
       
        long *long_value = new long;
            
            
        if(const_identificator(ch, long_value, line_number) == 1)
            {delete long_value; return 1;}
        if(operation_assigment_int_value(var2, long_value, line_number) == 1)
            {delete long_value; return 1;}
        
    }
    else
    {  
        if(var_identificator(ch, var2, line_number) == 1)
            {cout << "errr" << endl; return 1;}

        if(!is_declarated_variable(var2)){
            cout <<"Error in " << line_number << "line: "<< var2 << " is not declarated is this scope" << endl; 
            return 1;}
    }
    

    clear_spaces(ch);

    char oper[1];
    
    if(oprtr(ch, oper, line_number, true) == 1)
        return 1;
    
    if(oper[0] == '=') 
        cout <<"Error in " << line_number << "line: "<< "Second operator '='" << endl;
    
    clear_spaces(ch);
    
    if(**ch == 0)
        {var1 = var2; return 0;}
    
    if(is_string(ch))
        {
            
            char *string_value = new char[MAX_STRING_AS_VALUE_LEN];
            
            
            if(const_string_identificator(ch, string_value, line_number) == 1)
                {delete [] string_value; return 1;}
            
            if(operation_assigment_string_value(var3, string_value, line_number) == 1)
                {delete [] string_value; return 1;}

        }

    else if(is_number(ch))
    {   
        
        long *long_value = new long;
            
            
        if(const_identificator(ch, long_value, line_number) == 1)
            {delete long_value; return 1;}
        if(operation_assigment_int_value(var3, long_value, line_number) == 1)
            {delete long_value; return 1;}
        
    }
    else
    {
        
        if(var_identificator(ch, var3, line_number) == 1)
            return 1;

        if(!is_declarated_variable(var3)){
            cout <<"Error in " << line_number << "line: "<< var2 << " is not declarated is this scope" << endl; 
            return 1;}
    }


    if(oper[0] == '+')
        {operation_plus(var1, var2, var3, line_number);}

    else if(oper[0] == '-')
        operation_minus(var1, var2, var3, line_number);

    else if(oper[0] == '*')
        operation_multiplication(var1, var2, var3, line_number);

    else if(oper[0] == '/')
        operation_division_type_1(var1, var2, var3, line_number);


    delete [] var1;
    delete [] var2;
    return 0;
}


int not_simple_operation(char **ch, char *var1, const int &line_number)
{
    
    return 0;
}


int work_with_one_line(char *ch_pointer, const int &line_number)
{

    char **ch = new char*; //pointer to the value of poiner...
    *ch = ch_pointer; 

    char *var1 = new char[MAX_VAR_LEN];
    
    if(var_identificator(ch, var1, line_number))
        {cout << "Error in line " << line_number << endl; return 1;} //it should call real error. But how? Additional file with including it?
    
    if(is_declarated_function(var1)){}
        //working with specific function, needs an update later

    char oprt[1];
    
    if(oprtr(ch, oprt, line_number, false))
        cout << "Error while parsing expression in line "<< line_number <<". Did you miiss operator?" << endl << ch_pointer << endl; // also should call real error
    
    clear_spaces(ch);
    
    
    if(oprt[0] == '=')
    {
        
        
        if(**ch == '"')
        {
               
            char *string_value = new char[MAX_STRING_AS_VALUE_LEN];
            
            
            if(const_string_identificator(ch, string_value, line_number) == 1)
                {delete [] string_value; return 1;}
            
            if(operation_assigment_string_value(var1, string_value, line_number) == 1)
                {delete [] string_value; return 1;}
            
            return 0;
            
        }
        else if('0' <= **ch && **ch <= '9')
        {
            long *long_value = new long;
            
            
            if(const_identificator(ch, long_value, line_number) == 1)
                {delete long_value; return 1;}
            if(operation_assigment_int_value(var1, long_value, line_number) == 1)
                {delete long_value; return 1;}
        }
        else
        {
            
            simple_operation(ch, var1, line_number);
        }
    }
    else
    {
        cout << "Wrong operator in line " << line_number  << " Did you mean '=' ?" << endl;
        return 1;
    }
    
    delete ch;
    

    return 0;
}



int process()
{
    
    
    char file[MAX_LEN_FILE][MAX_LEN_LINE];
    read_file("example.txt", file);
    int line = 0;
    while (file[line][0] != 0)
    {   
        if(file[line][0] == '\n')
            {++line; continue;}

        char *uk = file[line];
        char **pntr = new char*;
        //cout << line << endl;
        if(work_with_one_line(uk, line+1) == 1)
            return 1;
        
        ++line;
    
    }
    
    // Debug
    for(auto it = Variables.begin(); it != Variables.end(); ++it)
        cout << it->first << ' ' << it->second << endl;
    
    for(auto it = Variables_int_values.begin(); it != Variables_int_values.end(); ++it)
        cout << it->first << ' ' << *(it->second) << endl;

    for(auto it = Variables_string_values.begin(); it != Variables_string_values.end(); ++it)
        cout << it->first << ' ' << (it->second) << endl;
    
    
    /*
    *pntr = uk;
    clear_spaces_and_idk_its_name(pntr);
    int number = 0;
    var_identificator(pntr, s, number);
    */
    
    
    
   return 0;
   
}

int main()
{
    process();
}


/*
Problems with clearing ' ' and '\n'. We need pointer to change into a function. Solved with pointer to pointer
Problem with creating a new dynamic mas -> problem with inserting new walue into a map. Solved with storing only pointers

rewrite a map container <mas_name, mas_type>, <mas_name, int>, <mas_name, mas_value> to
pointer = pn
<pn_name, pn_type>, <pn_name, int> ... Values must be stored only once! Done.

Still not writed:
operations +, -, / and * for int
operating with constants, like : a = "Hello World"
printing results with fuction print()


*/
