#include "parser.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

int main(int argc,char* argv[]){
    if(argc==1){
        std::string s;
        std::vector<std::string> code;
        while(true){
            std::cout<<">>> ";
            std::getline(std::cin,s);
            if(s=="exit") return 0;
            else if(s=="run"){
                Execute(code);
                std::cout<<"\n";
                code = {};
            }
            else if(s=="clear") std::system("clear");
            else if(s=="scratch") code = {};
            else code.push_back(s);
        }
    }
    else{
        std::ifstream in(argv[1]);
        std::vector<std::string> a;
        std::string temp;
        while(std::getline(in,temp))
            a.push_back(temp);
        Execute(a);
        while(!std::cin){}
    }
}