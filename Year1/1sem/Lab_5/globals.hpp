#pragma once
#include<string>

const char FILENAME[] = "data.dat";
const int MAX_NAME_LEN = 40;
const int MAX_DATE_OF_BIRTH_LEN = 11;
const int MAX_LINE_LEN = 350;
const int MAX_COMMAND_LEN  = 15;
const int UNIVERSAL_LEN = 40;

const char CLOSE_CONDITION[] = ":q";
const char CLOSE_CONDITION_UPPER[] = ":Q";

const std::string HELP_CONDITION = "--help";

const int MAX_VALUE_LEN = 40;
const int MAX_PARAM_LEN = 20;
const int MAX_BOOL_LEN = 2;
//commands
const char INSERT_COMMAND[] = "INSERT";
const char DELETE_COMMAND[] = "DELETE";
const char UPDATE_COMMAND[] = "UPDATE";
const char SELECT_COMMAND[] = "SELECT";
const std::string WHERE_COMMAND = "WHERE";
const char WRITE_DOWN_COMMAND[] = "WRITE_DOWN";

//other variables
const std::string EMPTY_STRING = "";
const std::string NAME_PARAM = "name";
const std::string SECOND_NAME_PARAM = "second_name";
const std::string IS_MALE_PARAM = "is_male";
const std::string TELEGRAM_ID_PARAM = "telegram_id";
const std::string DATE_OF_BIRTH_PARAM = "date_of_birth";