#include "parser.h"
#include <cstdlib>

int main(){
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