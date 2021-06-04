#include"syntaxanal.hpp"
#include<fstream>
#include<utility>
#include<iostream>
#include<cstdlib>
#include<regex>
using namespace std;
int main() {

    char s_name[18],s_number[3];
    regex pattern("([^.]+)[.]dyd");
    string val {"$1.val"} , pro {"$1.pro"},dyd_name;
    fstream dyd_fs,value_fs,process_fs;
    SyntaxAnal syntaxanal;
    
    cout << "dyd file name : ";
    cin >> dyd_name;
    
    if(regex_match(dyd_name,pattern)) {
        dyd_fs.open(dyd_name,ios::in);
        value_fs.open(regex_replace(dyd_name,pattern,val),ios::out);
        process_fs.open(regex_replace(dyd_name,pattern,pro),ios::out);
    }
    else {
        return 0;
    }

    while(!syntaxanal.Wrong()) {

        dyd_fs.read((char *)&s_name,17);
        if(dyd_fs.gcount() != 17) break;
        dyd_fs.read((char *)&s_number,3);
        s_name[16] = 0;
        s_number[2] = 0;
        syntaxanal.Analysis(make_pair(s_name,atoi(s_number)));
    }

    syntaxanal.ExportValueList(value_fs);
    syntaxanal.ExportProcessList(process_fs);

    return 0;
}