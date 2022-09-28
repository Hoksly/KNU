#ifndef CONSTANTS
#define CONSTANTS
const char SLAVE_FILE[] = "data/SP.fl";
const char DETAILS_DATA_FILE[] = "data/D.fl";
const char DETAILS_INDEX_FILE[] = "data/D.ind";
const char PROVIDERS_DATA_FILE[] = "data/S.fl";
const char PROVIDERS_INDEX_FILE[] = "data/S.ind";

const std::string HELP_MESSAGE = "i - insert\n"
                                 "d - delete\n"
                                 "u - update\n"
                                 "g - get and display\n"
                                 "h - show this message again\n"
                                 "e - exit";

const std::string INVALID_OPTION = "Invalid option, try again";

const std::string MASTER_OR_SLAVE = "master (m) or slave (s) ?";

const std::string NO_SUCH_MASTER = "No such master";
const std::string NO_SUCH_SLAVE = "No such slave";

const std::string INSTERTION_FAILED = "Insertion failed";
const std::string DELITION_FAILED = "Delition failed";

const std::string SUCCESSFUL_MESAGE = "Successful";

const std::string SLAVE_EXIST = "Such slave already exist";

const std::string FILE_ERROR = "File error occured";
const std::string QUANT_OR_PRICE = "Which field? quantity (q) price (p)";
const std::string SUR_OR_CITY = "Which field? surname (s) city (c)";
const std::string INVALID_OPTION_EXIT = "Invalid option, exiting";

#endif