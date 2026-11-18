#pragma once
#include <string>
#include "variable.h"
#include <vector>
#include <iostream>

void Execute(std::vector<std::string> code);
class _Operation;
Var* _Decode(_Operation* tree);

class Function{
    public:
        std::string name;
        virtual Var* F(std::vector<Var*> args){return new Var(0ll);}
};

class Write:public Function{
    public:
        Write(){name = "Console.Write";}
        Var* F(std::vector<Var*> args) override{
            std::cout<<To_String(GetVar(args[0]));
            return new Var(0ll);
        }
};
class Read:public Function{
	public:
		Read(){name="Console.Read";}
		Var* F(std::vector<Var*> args) override{
			std::string s;
			std::getline(std::cin,s);
			return new Var(s);
		}
};
class Str:public Function{
	public:
		Str(){name="Str";}
		Var* F(std::vector<Var*> args) override{
			return new Var(To_String(args[0]));
		}
};

class Int:public Function{
	public:
		Int(){name="Int";}
		Var* F(std::vector<Var*> args) override{
			return new Var(To_Int(args[0]));
		}
};

class Double:public Function{
	public:
		Double(){name="Double";}
		Var* F(std::vector<Var*> args) override{
			return new Var(To_Double(args[0]));
		}
};


class ExeFunction{
    public:
        std::string name;
        virtual void F(std::vector<_Operation*> args,std::vector<_Operation*> code){return;}
};

class If:public ExeFunction{
    public:
        If(){name="if";}
        void F(std::vector<_Operation*> args,std::vector<_Operation*> code) override{
            if(To_Bool(_Decode(args[0]))==true){
                for(_Operation* o:code)
                    _Decode(o);
            }
        }
};
class For:public ExeFunction{
    public:
        For(){name="for";}
        void F(std::vector<_Operation*> args,std::vector<_Operation*> code) override{
            std::string var_name = ""; double a=0,b,c=1;
            if(args.size()>=4)
                var_name = To_Pointer(_Decode(args[3]));
            if(args.size()>=3)
                c=To_Double(_Decode(args[2]));
            if(args.size()>=2){
                a = To_Double(_Decode(args[0]));
                b = To_Double(_Decode(args[1]));}
            if(args.size()>=1)
                b = To_Double(_Decode(args[0]));
            for(double i=a;i<b;i=i+c){
                if(var_name!="")
                    SetVar(var_name,new Var(i));
                for(_Operation* o:code)
                    _Decode(o);
            }
        }
};

class TypeFunction{
    public:
        std::string name;
        virtual Var* F(std::vector<Var*> args){return nullptr;}
};
class To_N:public TypeFunction{
    public:
        To_N(){name="to_n";}
        Var* F(std::vector<Var*> args) override{
            return new Var(To_String(args[0])+"\n");
        }
};
class Push : public TypeFunction{
    public:
        Push(){name="push";}
        Var* F(std::vector<Var*> args) override{
            if(args.size()==2){
	            args[0]->a.push_back(args[1]);
	            SetVar(args[0]->name,args[0]);
	            return args[0];
            }
            else if(args.size()==3){
            	args[0]->a.insert(args[0]->a.begin()+To_Int(args[2]),args[1]);
            	SetVar(args[0]->name,args[0]);
            	return args[0];
            }
            else
                return args[0];
        }
};

std::vector<Function*> functions = {new Write(),new Read(),new Str(),new Int(),new Double()};
std::vector<ExeFunction*> exeFunctions = {new If(),new For()};
std::vector<TypeFunction*> typeFunctions = {new To_N(),new Push()};