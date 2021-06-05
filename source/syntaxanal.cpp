#include"syntaxanal.hpp"
#include<iostream>

using namespace std;

void SyntaxAnal::Advance(const pair<string,int> & dyd) {

    state_stack.push(current_st);
    //输入终结符查询action表转换状态
    current_st = slr_anal.Action(current_st,dyd.second);

    //移进、规约、或异常
    switch(StateType()) {
    //移进
    case 0:
        Shift(dyd);
        break;
    //接收
    case 1:
        Accept(dyd);
        break;
    //规约
    case 2:
        Recurse(dyd);
        break;
    //异常
    case 3: 
        Error(current_st);
    default:
        break;
    }
}

int SyntaxAnal::StateType() const {
    //移进项目
    if(current_st < 100) return 0;
    //接收项目
    if(current_st == 100) return 1;
    //规约项目
    if(current_st > 100 && current_st < 150) return 2;
    //异常项目
    else return 3;
}

void SyntaxAnal::Shift(const pair<string,int> & dyd) {
    
    switch(current_st) {
    case 2:
    case 68:
        ++level;
        break;
    case 10:
        switch(state_stack.top()) {
        case 7:     //value defined
            AddValue(dyd.first);
            break;
        case 37:    //函数形参
            undefined_parameters.push_back(dyd.first);
            break;
        case 8:     //变量赋值
        case 25:    //变量赋值
        case 26:    //read(D)
        case 27:    //write(D)
        case 42:    //变量赋值
        case 63:    //变量赋值
        case 70:    //变量赋值
        default:
            if(value_map.find(dyd.first) == value_map.end()) {
                //变量未定义
                if(dyd.first != current_proc) Error(undeclared);
            }
            break;

        }
        break;
        
    case 23:        //function defined "function a"
        AddProcess(dyd.first);
        break;
    case 24:        //end
    case 72:        //end
        --level;
        //回写过程最后一个变量的地址
        if(process_map.find(current_proc) != process_map.end()) 
            process_map[current_proc].last_value_address = value_map.size() - 1;
        current_proc = string {"main"};
        if(!undefined_parameters.empty()) {
            //函数形参未定义
            Error(undeclared);
        }
        break;
    case 36:        //D -> a,T -> a(F)
        if(next_dyd.second == SLRTable::LPAR) {
            //T -> a(F)
            if(process_map.find(dyd.first) == process_map.end()) {
                //函数未定义
                Error(undeclared);
            }
        }
        else if(value_map.find(dyd.first) == value_map.end()) {
            //变量未定义
            Error(undeclared);
        }
        break;
    default:
        break;
    }
}
void SyntaxAnal::Recurse(const pair<string,int> & dyd) {
    int i,symbol;
    switch(current_st) {
    case 101:   //S' -> begin A;H end
        for(i = 0;i < 5;state_stack.pop(),++i);
        symbol = SLRTable::S_;
        break;
    case 102:   //A -> B
        state_stack.pop();
        symbol = SLRTable::A;
        break;
    case 103:   //A -> A;B
        for(i = 0;i < 3;state_stack.pop(),++i);
        symbol = SLRTable::A;
        break;
    case 104:   //B -> C
        state_stack.pop();
        symbol = SLRTable::B;
        break;
    case 105:   //B -> E
        state_stack.pop();
        symbol = SLRTable::B;
        break;
    case 106:   //C -> integer D
        for(i = 0;i < 2;state_stack.pop(),++i);
        symbol = SLRTable::C;
        break;
    case 107:   //D -> a
        state_stack.pop();
        symbol = SLRTable::D;
        break;
    case 108:   //E -> integer function a (F);G
        for(i = 0;i < 8;state_stack.pop(),++i);
        symbol = SLRTable::E;
        break;
    case 109:   //F -> D
        state_stack.pop();
        symbol = SLRTable::F;
        break;
    case 110:   //G -> begin A;H end
        for(i = 0;i < 5;state_stack.pop(),++i);
        symbol = SLRTable::G;
        break;
    case 111:   //H -> I
        state_stack.pop();
        symbol = SLRTable::H;
        break;
    case 112:   //H -> H;I
        for(i = 0;i < 3;state_stack.pop(),++i);
        symbol = SLRTable::H;
        break;
    case 113:   //I -> J
    case 114:   //I -> K
    case 115:   //I -> L
    case 116:   //I -> M
        state_stack.pop();
        symbol = SLRTable::I;
        break;
    case 117:   //J -> read(D)
        for(i = 0;i < 4;state_stack.pop(),++i);
        symbol = SLRTable::J;
        break;
    case 118:   //K -> write(D)
        for(i = 0;i < 4;state_stack.pop(),++i);
        symbol = SLRTable::K;
        break;
    case 119:   //L -> D := N
        for(i = 0;i < 3;state_stack.pop(),++i);
        symbol = SLRTable::L;
        break;
    case 120:   //N -> N - O
        for(i = 0;i < 3;state_stack.pop(),++i);
        symbol = SLRTable::N;
        break;
    case 121:   //N -> O
        state_stack.pop();
        symbol = SLRTable::N;
        break;
    case 122:   //O -> O * P
        for(i = 0;i < 3;state_stack.pop(),++i);
        symbol = SLRTable::O;
        break;
    case 123:   //O -> P
        state_stack.pop();
        symbol = SLRTable::O;
        break;
    case 124:   //P -> D
    case 125:   //P -> b
    case 126:   //P -> T
        state_stack.pop();
        symbol = SLRTable::P;
        break;
    case 127:   //M -> if Q then I else I
        for(i = 0;i < 6;state_stack.pop(),++i);
        symbol = SLRTable::M;
        break;
    case 128:   //Q -> N R N 
        for(i = 0;i < 3;state_stack.pop(),++i);
        symbol = SLRTable::Q;
        break;
    case 129:   //R -> <
    case 130:   //R -> <=
    case 131:   //R -> >
    case 132:   //R -> >=
    case 133:   //R -> =
    case 134:   //R -> <>
        state_stack.pop();
        symbol = SLRTable::R;
        break;
    case 135:   //T -> a(F)
        for(i = 0;i < 3;state_stack.pop(),++i);
        symbol = SLRTable::T;
        break;
    default:
        break;
    }

    //状态转换
    current_st = slr_anal.Go(state_stack.top(),symbol);
    //移进、规约、或异常
    switch(StateType()) {
    //移进
    case 0:
        Advance(dyd);
        break;
    //接收
    case 1:
        Accept(dyd);
        break;
    //规约
    case 2:
        Recurse(dyd);
        break;
    //异常
    case 3: 
        Error(current_st);
    default:
        break;
    }
}

void SyntaxAnal::AddProcess(const string & name) {
    process_list_t process_entry;
    current_proc = name;
    if(process_map.find(name) != process_map.end()) {
        //函数重复定义,后续分析均无意义也难以进行，可视为重大错误
        Error(redeclaration);
        wrong = true;
    }
    process_entry.first_value_address = value_map.size();
    process_entry.last_value_address = 0;
    process_entry.process_level = level;
    process_entry.process_name = name;
    process_entry.process_type = "integer";

    process_map[name] = process_entry;
}

void SyntaxAnal::Analysis(const pair<string,int> & dyd) {
    this_dyd = next_dyd;
    next_dyd = dyd;
    if(this_dyd.second == SLRTable::EOLN) ++lines;
    else if(this_dyd.second) Advance(this_dyd);
    else {
        if(next_dyd.second != SLRTable::BEGIN) {
            //第一行无begin
            Error(lack_of_begin);
            this_dyd.second = SLRTable::BEGIN;
            Advance(this_dyd);
        }
    }
}

#include<algorithm>
void SyntaxAnal::AddValue(const string & name) {

    value_list_t value_entry;
    decltype(undefined_parameters.end()) it;

    if(value_map.find(name) != value_map.end()) {
        //重复定义
        Error(redeclaration);
        return;
    }

    value_entry.value_kind = value_list_t::Value;
    value_entry.value_level = level;
    value_entry.value_address = value_map.size();
    value_entry.value_type = "integer";
    value_entry.value_name = name;
    value_entry.value_process = current_proc;


    //未定义形参表中若有同名变量，说明是在定义形参
    for(it = undefined_parameters.begin();it != undefined_parameters.end();++it) {
        if(*it == name) {
            undefined_parameters.erase(it);
            value_entry.value_kind = value_list_t::Parameter;
            break;
        }
    }

    value_map[value_entry.value_name] = value_entry;
}

void SyntaxAnal::Error(int description) {
    switch(description) {

    case lack_of_begin:
        cout << "***1 : lack of \'BEGIN\'.\n";
        break;
    case redeclaration:
        cout << "***" << lines << " : redeclaration \'" << this_dyd.first << "\'.\n";
        break;
    case undeclared:
        cout << "***" << lines << " : undeclared symbol \'" << this_dyd.first << "\'.\n";
        break;
    case 151:
        cout << "***" << lines << " : read " << this_dyd.first << " lack of \'(\'\n";
        current_st = state_stack.top();
        state_stack.pop();
        Advance(make_pair(string{"("},SLRTable::LPAR));
        Advance(this_dyd);
        break;
    case 152:
        cout << "***" << lines << " : write " << this_dyd.first << " lack of \'(\'\n";
        current_st = state_stack.top();
        state_stack.pop();
        Advance(make_pair(string{"("},SLRTable::LPAR));
        Advance(this_dyd);
        break;
    case 153:
        cout << "***" << lines << " fatal error.\n";
        wrong = true;
        break;
    case 154:
        cout << "***" << lines << " illegal declaration.\n";
        current_st = state_stack.top();
        state_stack.pop();
        break;
    default:
        break;
    }
}

#include<iomanip>

void SyntaxAnal::ExportValueList(fstream & fs) const {
    for_each(value_map.begin(),value_map.end(),[&] (auto & it) { 
        fs << "   value_kind : " << setw(16) << it.second.value_kind << '\n' \
           << "  value_level : " << setw(16) << it.second.value_level << '\n' \
           << "value_address : " << setw(16) << it.second.value_address << '\n' \
           << "   value_type : " << setw(16) << it.second.value_type << '\n' \
           << "   value_name : " << setw(16) << it.second.value_name << '\n' \
           << "value_process : " << setw(16) << it.second.value_process << "\n\n";
    });
}

void SyntaxAnal::ExportProcessList(fstream & fs) const {
    for_each(process_map.begin(),process_map.end(),[&] (auto & it) {
        fs << "      process_level : " << setw(16) << it.second.process_level << '\n' \
           << "first_value_address : " << setw(16) << it.second.first_value_address << '\n' \
           << " last_value_address : " << setw(16) << it.second.last_value_address << '\n' \
           << "       process_name : " << setw(16) << it.second.process_name << '\n' \
           << "       process_type : " << setw(16) << it.second.process_type << "\n\n";
    });
}