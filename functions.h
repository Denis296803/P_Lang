#pragma once
#include <string>
#include "variable.h"
#include <vector>
#include <iostream>

class Function{
    public:
        std::string name;
        virtual Var* F(std::vector<Var*> args){return new Var(0);}
};
class Write:public Function{
    public:
        Write(){name = "Console.Write";}
        Var* F(std::vector<Var*> args) override{
            if(args[0]->type=='s')
                std::cout<<args[0]->get_s();
            else if(args[0]->type=='i')
                std::cout<<args[0]->get_i();
            else if(args[0]->type=='d')
                std::cout<<args[0]->get_d();
            return new Var(0);
        }
};