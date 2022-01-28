#pragma once
#include <string>
#include "globals.hpp"
struct str_with_pos
{
    std::string s = "";
    int pos = 0;

    char get_ch();
    char get_ch_nm();
    void clear();

};
 
 struct Person
{
    char name[MAX_NAME_LEN];
    char second_name[MAX_NAME_LEN];
    bool is_male;
    long telegram_id;
    char date_of_birth[MAX_DATE_OF_BIRTH_LEN];
};

