#include "classes.hpp"



Lexeme::Lexeme(Type what, Lexeme* Parent, Lexeme* LeftChild, Lexeme *RightChild, void *val = nullptr, OperatorType op = NullOPerator)
{
    _type = what;
    left_child = LeftChild;
    right_child = RightChild;
    parent = Parent;
        

    switch (what)
    {
    case Variable:
        variable = (char *) val;
        break;
    
    case Constant:
        value = (double *) val;
        break;
        
    case Operator:
        oper = op;
        break;
    
    default:
        // Should error be here?
        break;
    }
    
}

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

std::string Parser::parse_token() {
    // Пропускаем пробелы перед токеном.        
    while (std::isspace(*input)) ++input;

    // Если input начинается с цифры, то парсим число.
    if (std::isdigit(*input)) {
        std::string number;
        while (std::isdigit(*input) || *input == '.') 
            number.push_back(*input++);
        return number;
    }

    

    // Список всех известных токенов - операции и скобки.
    static const std::string tokens[] =
        { "+", "-", "**", "*", "/", "mod", "abs", "sin", "cos", "(", ")" };
    
    for (auto& t : tokens) {
        if (std::strncmp(input, t.c_str(), t.size()) == 0) {
            input += t.size();
            return t;
        }
    }

    if(isvariable(*input)) // variable can be only one-letter sized
    {
        std::string var;
        var += *input;
        input++;
        variables.push_back(var);
        
        return var;
    }

    

    return ""; // Какой-то неизвестный токен, или символ '\0' - конец строки.
}

Expression Parser::parse_simple_expression() {
    // Парсим первый токен.
    auto token = parse_token();
    

    if (token.empty()) // Неожиданный конец строки, или неизвестный токен
        throw std::runtime_error("Invalid input");

    if (std::isdigit(token[0])) // Если это цифра, возвращаем выражение без аргументов
        return Expression(token);
    if(isvariable(token))
        return Expression(token);

    if (token == "(") {
        auto result = parse();
        if (parse_token() != ")") throw std::runtime_error("Expected ')'");
        return result; // Если это скобки, парсим и возвращаем выражение в скобках
    }

    // Иначе, это унарная операция ("-", "sin", и т.п.)
    auto arg = parse_simple_expression(); // Парсим ее аргумент.
    return Expression(token, arg);
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

Expression Parser::parse_binary_expression(int min_priority) {
    auto left_expr = parse_simple_expression(); // Парсим простое выражение.

    for (;;) {
        token op = parse_token(); // Пробуем парсить бинарную операцию.
        int priority = get_priority(op);
        // Выходим из цикла если ее приоритет слишком низок (или это не бинарная операция).
        if (priority <= min_priority) {
            input -= op.size(); // Отдаем токен обратно,
            return left_expr; // возвращаем выражение слева.
        }

        // Парсим выражение справа. Текущая операция задает минимальный приоритет.
        Expression right_expr = parse_binary_expression(priority);
        left_expr = Expression(op, left_expr, right_expr); // Обновляем выражение слева.
    } // Повторяем цикл: парсинг операции, и проверка ее приоритета.
}

Expression Parser::parse() {
    return parse_binary_expression(0);
}

std::vector<std::string> Parser::give_vars()
{
    return variables;
}