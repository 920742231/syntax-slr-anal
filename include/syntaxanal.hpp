_Pragma("once");

#include"slrtable.hpp"
#include"datas.hpp"
#include<utility>
#include<string>
#include<stack>
#include<vector>
#include<fstream>

class SyntaxAnal {

    public:
        void Advance(const std::pair<std::string,int> &);
        void Analysis(const std::pair<std::string,int> &);
        
        void Error(int);
        void Accept(const std::pair<std::string,int> &) {}
        void Shift(const std::pair<std::string,int> &);
        void Recurse(const std::pair<std::string,int> &);
        
        void AddValue(const std::string &);
        void AddProcess(const std::string &);
        int StateType() const;

        bool Wrong() const {
            return wrong;
        }

        void ExportValueList(std::fstream &) const;
        void ExportProcessList(std::fstream &) const;

    private:

        enum {
            redeclaration,
            undeclared,
            lack_of_begin
        };

        bool wrong {false};

        //
        int lines {1};
        //嵌套层次
        int level;
        //当前状态
        int current_st;
        //状态栈
        std::stack<int> state_stack;
        //当前过程名
        std::string current_proc {"main"};
        //函数形参
        std::vector<std::string> undefined_parameters;
        //下一个符号的二元式
        std::pair<std::string,int> next_dyd,this_dyd;
        //action表和go表
        SLRTable slr_anal;
        //变量表
        ValueMap value_map;
        //过程表
        ProcessMap process_map; 
};