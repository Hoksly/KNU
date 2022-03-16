#pragma once
#include <string.h>
#include <vector>
#include <string>
#include <iostream>
#include "enums.hpp"
#include "constants.hpp"
#include <cmath>
//std::vector<std::string> ToStrigns(const std::string &s);
void simplify(std::string &str);
OperatorType give_operator(std::string);

bool XOR (void *p1, void *p2);
bool NotNULL(void *p1, void *p2);
bool NotNULL(void *p1);
bool IsNull(void *p1);
bool IsNull(void *p1, void *p2);

bool isin(OperatorType, std::vector<OperatorType>);
bool deq(double *, double *);
bool vareq(Var*, Var*);

void print(std::string);
void print(bool);

