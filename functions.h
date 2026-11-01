#pragma once
#include <string>
#include "variable.h"
#include <vector>
#include <iostream>

class Function{
    public:
        std::string name;
        virtual Var* F(std::vector<Var*> args){return new Var(0ll);}
};

class Write:public Function{
    public:
        Write(){name = "Console.Write";}
        Var* F(std::vector<Var*> args) override{
            std::cout<<To_String(args[0]);
            return new Var(0ll);
        }
};