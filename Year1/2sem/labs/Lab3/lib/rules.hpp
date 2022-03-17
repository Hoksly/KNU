#include "classes.hpp"
#include <queue>

bool simple_minus(Lexeme * Node);
bool add_constants(Lexeme * Node);
bool subs_constants(Lexeme * Node);
bool mult_constants(Lexeme * Node);
bool div_constants(Lexeme * Node);
bool complex_plus(Lexeme * Node);
bool remove_zero(Lexeme * Node);