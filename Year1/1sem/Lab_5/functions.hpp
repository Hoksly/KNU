#pragma once
#include "classes.hpp"
#include <vector>
#include <iostream>
#include <cstring>

int add_new_person(std::vector<Person*> *people, std::string name, std::string second_name, std::string date_of_birthday, long telegram_id, bool is_male);

void clear_spaces(str_with_pos &ch, int &i);

int find_command(str_with_pos &ch, char *command, int &i);

int find_param_and_value(str_with_pos &ch, std::string &param, std::string &value, int &i);


std::string covert_char_to_string(char *param);

int find_param(str_with_pos &ch, std::string &res, int &i);

int find_params(str_with_pos &ch, std::vector<std::string> &list_of_params, int &i);

int find_params_and_values(str_with_pos &ch, std::vector<std::pair<std::string, std::string>> &list_of_params, int &i);

std::string find_val(std::vector<std::pair<std::string, std::string>> A, std::string target);

std::string ch_to_srt(char *ch);

bool check_birth(std::string main, std::string src);

int strmatch(std::string s1, char * s2);

bool matching(Person* prs, const std::vector<std::pair<std::string, std::string>> &params);

std::string convert_mas_to_str(std::vector<std::vector<std::string>> s);

void strcp(char * s1, std::string s2);

void show_all_help();

void print_db(std::vector<Person*> people);