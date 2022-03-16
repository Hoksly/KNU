#include "classes.hpp"


void Lexeme::change_left(Lexeme * NewLexeme)
{
    left_child = NewLexeme;
}


void Lexeme::change_right(Lexeme * NewLexeme)
{
    right_child = NewLexeme;
}

void Lexeme::change_parent(Lexeme * NewLexeme)
{ 
    parent = NewLexeme;
}

inline bool isvariable(char c)
{
    return islower(c) || isupper(c);
}

 bool isvariable(std::string s)
{
    if (s.size() != 1)
        return false;

    return (islower(s[0]) || isupper(s[0]));
}

int get_priority(const std::string& token) {
    if (token == "+") return 1;
    if (token == "-") return 1;
    if (token == "*") return 2;
    if (token == "/") return 2;
    if (token == "mod") return 2; // остаток от деления
    if (token == "^") return 3; // степень
    return 0; // Возвращаем 0 если токен - это не бинарная операция (например ")")
}


//Constructor for constants
Lexeme::Lexeme(double val)
{
    value = new double(val);
    _type = Constant;
}

//Constructir for variables
Lexeme::Lexeme(Var *n_variable) 
{
    //std::cout<<"Variable " << n_variable << '\n';
    //std::cout<<"Variable name " << n_variable->name << '\n';
    variable = n_variable;
    _type = Variable;    
}

Lexeme::Lexeme(OperatorType op)
{
    oper = op;
    _type = Operator;
}
Lexeme::Lexeme(OperatorType op, Lexeme* child) // Constructor for unar operations
{
    _type = Operator;
    oper = op;
    // for unar opearions we use left child as argument

    left_child = child;
    child->change_parent(this);
}

Lexeme::Lexeme(const std::string &token, Lexeme * left, Lexeme* right)
{
    /*Suggestion: it is always operators (only they can have a childrens)
    After debug it will be simplyfied*/
    //std::cout << "LEXEME CONSTRUCTOR: " << token <<'\n';
    
    OperatorType op = give_operator(token);
    
    if(op != NullOPerator)
    {
        oper = op;
        _type = Operator;
    }
    else
    {
        std::string msg = "Error in lexeme constructor with '" + token + "' token";
        throw std::runtime_error(msg);
    }
    
    change_left(left);
    change_right(right);
    left->change_parent(this);
    right->change_parent(this);
}



std::string LexParser::parse_token() {
    // Пропускаем пробелы перед токеном.        
    while (std::isspace(*input)) ++input;

    // Если input начинается с цифры, то парсим число.
    if (std::isdigit(*input)) {
        std::string number;
        while (std::isdigit(*input) || *input == '.') 
            number.push_back(*input++);
        //std::cout<<"1 " << number << '\n';
        return number; //!!!!!!!!!!!!!!!
    }

    

    // Список всех известных токенов - операции и скобки.
    //std::cout << "TOKENS" << '\n';
    for (auto& t : TOKENS) {
        //std::cout << t << '\n';
        if (std::strncmp(input, t.c_str(), t.size()) == 0) {
            
            input += t.size();
            
            return t;
        }
    }
    //std::cout << "/TOKENS" << '\n';

    if(isvariable(*input)) // variable can be only one-letter sized
    {
        //std::cout << "Holly shit" << std::endl;
        std::string var;
        var += (*input);
        input++;
        //std::cout<<"3 " << var << '\n';
        return var;
        
    }

    

    return ""; // Какой-то неизвестный токен, или символ '\0' - конец строки.
}

Lexeme* LexParser::parse_simple_expression() {
    // Парсим первый токен.
    std::string token = parse_token();
    //std::cout << token << std::endl;

    if (token.empty()) // Неожиданный конец строки, или неизвестный токен
        throw std::runtime_error("Invalid input");

    if (std::isdigit(token[0])) // Если это цифра, возвращаем выражение без аргументов
        return new Lexeme(std::stod(token));
    
    if(isvariable(token))
        return new Lexeme(Vars.give(token));

    if (token == "(") {
        Lexeme *result = parse();
        if (parse_token() != ")") throw std::runtime_error("Expected ')'");
        return result; // Если это скобки, парсим и возвращаем выражение в скобках
    }

    // Иначе, это унарная операция ("-", "sin", и т.п.)
    Lexeme *arg = parse_simple_expression(); // Парсим ее аргумент.
    return new Lexeme(give_operator(token), arg);
}


Lexeme* LexParser::parse_binary_expression(int min_priority) {
    Lexeme* left_expr = parse_simple_expression(); // Парсим простое выражение.
    
    for (;;) {
        
        
        std::string op = parse_token(); // Пробуем парсить бинарную операцию.
        //std::cout << op << '\n';
        int priority = get_priority(op);
        // Выходим из цикла если ее приоритет слишком низок (или это не бинарная операция).
        if (priority <= min_priority) {
            input -= op.size(); // Отдаем токен обратно,
            
            
            
            return left_expr; // возвращаем выражение слева.
        }

        // Парсим выражение справа. Текущая операция задает минимальный приоритет.
        
        Lexeme* right_expr = parse_binary_expression(priority);
        
        
        
        left_expr = new Lexeme(op, left_expr, right_expr); // Undefined value is not good enough...
    } // Повторяем цикл: парсинг операции, и проверка ее приоритета.
}


Variables::Variables()
{

}

Var * Variables::give(std::string name)
{
    //std::cout << "GIVE: " << name << '\n';
    for(auto v = data.begin(); v != data.end(); v++)
    {
        
        if((*v)->name == name)
            {//std::cout << "FOUND " << (*v) << '\n'; 
                return (*v);}
    }
    Var * v = add(name);

    return add(name);


}

Var * Variables::add(std::string name)
{
    Var* nvar = new Var(name);
    data.push_back(nvar);
    return nvar;
}

void Variables::set(std::string name, double value)
{
    for(auto v = data.begin(); v != data.end(); v++)
    {
        if((*v)->name == name)
            {(*v)->value = value; return;}
    }
    std::string msg = "No variable with name '" + name + "'";
    
    throw std::runtime_error(msg);

}

Lexeme *LexParser::parse()
{
    return parse_binary_expression(0);
}

std::string Lexeme::str_value()
{
   
    //cout << "HERE" << endl;
    switch (_type)
    {
    case Variable:
        //cout << "Variable" << endl;
        return (variable->name);
    
    case Operator:
        //cout << "Operator" << endl;
        
        switch (oper)
        {
        case Plus:
            return "+";
        case Minus:
            return "-";
        case Mult:
            return "*";
        case Div:
            return "/";
        case Pow:
            return "^";
        case NullOPerator:
            return "OperNull";
        }
    case Constant:
        //cout << "Constant" << endl;
        return std::to_string(*(value));
    
    default:
        return "BIG FUCK";
    }  
    
}
std::string prtLex(const Lexeme &lex)
{
    //cout << "HERE" << endl;
    switch (lex._type)
    {
    case Variable:
        //cout << "Variable" << endl;
        return (lex.variable->name);
    
    case Operator:
        //cout << "Operator" << endl;
        
        switch (lex.oper)
        {
        case Plus:
            return "+";
        case Minus:
            return "-";
        case Mult:
            return "*";
        case Div:
            return "/";
        case Pow:
            return "^";
        case NullOPerator:
            return "OperNull";
        }
    case Constant:
        //cout << "Constant" << endl;
        return std::to_string(*(lex.value));
    
    default:
        return "BIG FUCK";
    }  
    
}

bool Lexeme::operator==(const Lexeme &L)
{

    if(L._type != this->_type)
        return false;

    //std::cout << this->str_value() << ' ' <<prtLex(L) << '\n';
    //print(vareq(L.variable, this->variable));
    if(vareq(L.variable, this->variable) && deq(this->value, L.value) && L.oper == this->oper)
    {
        //print("HERE");
        // if Lexeme is operator we will use recursive == 
        if(isin(this->oper, NotEqualOperators) && 
        NotNULL(this->right_child, this->left_child) && 
        NotNULL(L.left_child, L.right_child)) // because only if left == left and right == right they will be equal
        {
            if(NotNULL(this->left_child, this->right_child) && NotNULL(L.left_child, L.right_child))
            {
                return *(this->left_child) == *(L.left_child) && *(this->right_child) == *(L.right_child);
            }
            else
                throw std::runtime_error("Binary operators must have both of arguments, not Null");     
        }

        if(isin(this->oper, EqualOperators)) // operators such as + and *
        {
            if(NotNULL(this->right_child, this->left_child)&&NotNULL(L.left_child, L.right_child))
            {
                bool res_line = (*(this->left_child) == *(L.left_child) && *(this->right_child) == *(L.right_child));
                bool res_reverse = (*(this->left_child) == *(L.right_child) && *(this->right_child) == *(L.left_child));
                return  res_line || res_reverse;
            }
            else
                throw std::runtime_error("Binary operators must have both of arguments, not Null");     
        }
        

        if(isin(this->oper, UnarOperators) && IsNull(this->right_child, L.right_child)) // Unar operators (sin, - ...)  check for right_child is for -
        {
            if(NotNULL(this->left_child, L.left_child))
            {
                return *(this->left_child) == *(L.left_child); 
            }
            else
                throw std::runtime_error("Unar operator must have argument, not Null");
        }

        //situation where we have unar and binar minus 
        if(this->oper == Minus)
            return false;

        return true; 
    }

    return false;
}