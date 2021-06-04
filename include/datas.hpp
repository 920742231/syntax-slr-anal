_Pragma("once");

#include<string>

typedef struct value_list {
    int value_kind;
    int value_level;
    int value_address;
    std::string value_type;
    std::string value_name;
    std::string value_process;
    enum Kind {Value,Parameter};
} value_list_t;

typedef struct process_list {
    int process_level;
    int first_value_address;
    int last_value_address;
    std::string process_name;
    std::string process_type;
} process_list_t;

#include<map>

using ValueMap = std::map<std::string,value_list_t>;

using ProcessMap = std::map<std::string,process_list_t>;

#include<vector>

using ValueVector = std::vector<value_list_t>;

using ProcessVector = std::vector<process_list_t>;