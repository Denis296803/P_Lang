#pragma once
#include <string>
#include "variable.h"
#include <vector>
#include <iostream>

class Function{
    public:
        std::string name;
        Var F(std::vector<Var> args);
};
class Write:Function{
    public:
        Write(){name = "Console.Write";}
        Var* F(std::vector<Var*> args){
            if(args[0]->type=='s')
                std::cout<<args[0]->get_s();
            else if(args[0]->type=='i')
                std::cout<<args[0]->get_i();
            else if(args[0]->type=='d')
                std::cout<<args[0]->get_d();
        }
};