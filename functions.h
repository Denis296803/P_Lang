#pragma once
#include <string>
#include "variable.h"
#include <vector>
#include <iostream>

void Execute(std::vector<std::string> code);

class Function{
    public:
        std::string name;
        virtual Var* F(std::vector<Var*> args){return new Var(0ll);}
};

class Write:public Function{
    public:
        Write(){name = "Console.Write";}
        Var* F(std::vector<Var*> args) override{
            std::string tmp = To_String(args[0]);
            std::cout<<tmp;
            return new Var(0ll);
        }
};

class ExeFunction{
    public:
        std::string name;
        virtual void F(std::vector<Var*> args,std::vector<std::string> code){return;}
};

class If:public ExeFunction{
    public:
        If(){name="if";}
        void F(std::vector<Var*> args,std::vector<std::string> code) override{
            if(args[0]->get_b()==true){ 
                Execute(code);
            }
        }
};