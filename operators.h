#pragma once

#include "variable.h"
#include <string>
#include <cmath>
#include <iostream>

//* Просто сборище операторов, ничего особо интересного

class Operator
{
public:
    std::string oper;
    int priority;
    bool is_unary;
    virtual Var* F1(Var* a){return nullptr;};
    virtual Var* F2(Var* a, Var* b){return nullptr;};
};

class Add : public Operator
{
public:
    Add()
    {
        oper     = "+";
        priority = 0;
        is_unary = false;
    }
    Var* F2(Var* a, Var* b) override
    {
		a = GetVar(a); b = GetVar(b);
		if(b->type=='a'&&a->type=='a'){
			std::vector<Var*> v = a->a;
			for(Var* temp:b->a) v.push_back(temp);
			return new Var(v);
		}
        if(a->type=='s'||b->type=='s'||a->type=='a'||b->type=='a'){
            return new Var(To_String(a)+To_String(b));
        }
        return new Var(To_Double(a)+To_Double(b));
    }
};
class Sub : public Operator
{
public:
    Sub()
    {
        oper     = "-";
        priority = 1;
        is_unary = false;
    }
    Var* F2(Var* a, Var* b) override
    {
        a = GetVar(a); b=GetVar(b);
        return new Var(To_Double(a)-To_Double(b));
    }
};
class Mul : public Operator
{
public:
    Mul()
    {
        oper     = "*";
        priority = 2;
        is_unary = false;
    }
    Var* F2(Var* a, Var* b) override
    {
        a = GetVar(a); b=GetVar(b);
		if((b->type=='d'||b->type=='i')&&(a->type=='s'||a->type=='a')||(b->type=='s'||b->type=='a')&&(a->type=='d'||a->type=='i')){
			if(b->type=='d'||b->type=='i'){
				std::string s="",tmp=To_String(a);
				for(int i=0;i<To_Int(b);i++) s=s+tmp;
				return new Var(s);
			}
			std::string s="",tmp=To_String(b);
				for(int i=0;i<To_Int(a);i++) s=s+tmp;
				return new Var(s);
		}
        return new Var(To_Double(a)*To_Double(b));
    }
};
class Div : public Operator
{
public:
    Div()
    {
        oper     = "/";
        priority = 3;
        is_unary = false;
    }
    Var* F2(Var* a, Var* b) override
    {
        a = GetVar(a); b=GetVar(b);
        return new Var(To_Double(a)/To_Double(b));
    }
};
class Mod : public Operator
{
public:
    Mod()
    {
        oper     = "%";
        priority = 2;
        is_unary = false;
    }
    Var* F2(Var* a, Var* b) override
    {
        a = GetVar(a); b=GetVar(b);
        return new Var(To_Int(a)%To_Int(b));
    }
};
class Pow : public Operator
{
public:
    Pow()
    {
        oper     = "^";
        priority = 4;
        is_unary = false;
    }
    Var* F2(Var* a, Var* b) override
    {
        a = GetVar(a); b=GetVar(b);
        double temp1 = To_Double(a),out=1; int temp2=To_Int(b);
        for(int i=0;i<temp2;i++)
            out=out*temp1;
        return new Var(out);
    }
};
class Asg : public Operator
{
public:
    Asg()
    {
        oper     = "=";
        priority = -2;
        is_unary = false;
    }
    Var* F2(Var* a, Var* b) override
    {
        b = GetVar(b);
        //std::cerr<<"ASG: "<<To_String(a)<<" "<<To_String(b)<<"\n";
        SetVar(To_Pointer(a),b,a->key);
        return nullptr;
    }
};
class Equ : public Operator
{
public:
    Equ()
    {
        oper     = "==";
        priority = -1;
        is_unary = false;
    }
    Var* F2(Var* a, Var* b) override
    {
        a = GetVar(a); b = GetVar(b);
        if(To_String(a)==To_String(b))
            return new Var(true);
        return new Var(false);
    }
};
class More : public Operator
{
public:
	More()
	{
		oper = ">";
		priority = -1;
		is_unary = false;
	}
	Var* F2(Var* a, Var* b) override
	{
		a = GetVar(a); b = GetVar(b);
		if(To_Double(a) > To_Double(b))
			return new Var(true);
		return new Var(false);
	}
};
class MoreE : public Operator
{
public:
	MoreE()
	{
		oper = ">=";
		priority = -1;
		is_unary = false;
	}
	Var* F2(Var* a, Var* b) override
	{
		a = GetVar(a); b = GetVar(b);
		if(To_Double(a) >= To_Double(b))
			return new Var(true);
		return new Var(false);
	}
};
class Less : public Operator
{
public:
	Less()
	{
		oper = "<";
		priority = -1;
		is_unary = false;
	}
	Var* F2(Var* a, Var* b) override
	{
		a = GetVar(a); b = GetVar(b);
		if(To_Double(a) < To_Double(b))
			return new Var(true);
		return new Var(false);
	}
};
class LessE : public Operator
{
public:
	LessE()
	{
		oper = "<=";
		priority = -1;
		is_unary = false;
	}
	Var* F2(Var* a, Var* b) override
	{
		a = GetVar(a); b = GetVar(b);
		if(To_Double(a) <= To_Double(b))
			return new Var(true);
		return new Var(false);
	}
};
class AddTo : public Operator
{
public:
	AddTo()
	{
		oper = "+=";
		priority = -2;
		is_unary = false;
	}
	Var* F2(Var* a, Var* b) override
	{
		Var* copy_a = GetVar(a); b = GetVar(b);
		SetVar(To_Pointer(a),new Var(To_Double(b)+To_Double(copy_a)));
		b = new Var(To_Double(b)+To_Double(copy_a));
		delete copy_a;
		return b;
	}
};
class SubTo : public Operator
{
public:
	SubTo()
	{
		oper = "-=";
		priority = -2;
		is_unary = false;
	}
	Var* F2(Var* a, Var* b) override
	{
		Var* copy_a = GetVar(a); b = GetVar(b);
		SetVar(To_Pointer(a),new Var(To_Double(b)-To_Double(copy_a)));
		b = new Var(To_Double(b)-To_Double(copy_a));
		delete copy_a;
		return b;
	}
};
class MulTo : public Operator
{
public:
	MulTo()
	{
		oper = "*=";
		priority = -2;
		is_unary = false;
	}
	Var* F2(Var* a, Var* b) override
	{
		Var* copy_a = GetVar(a); b = GetVar(b);
		SetVar(To_Pointer(a),new Var(To_Double(b)*To_Double(copy_a)));
		b = new Var(To_Double(b)*To_Double(copy_a));
		delete copy_a;
		return b;
	}
};
class DivTo : public Operator
{
public:
	DivTo()
	{
		oper = "/=";
		priority = -2;
		is_unary = false;
	}
	Var* F2(Var* a, Var* b) override
	{
		Var* copy_a = GetVar(a); b = GetVar(b);
		SetVar(To_Pointer(a),new Var(To_Double(b)/To_Double(copy_a)));
		b = new Var(To_Double(b)/To_Double(copy_a));
		delete copy_a;
		return b;
	}
};
class Or:public Operator{
public:
	Or(){
		oper="||";
		is_unary=false;
		priority=-1;
	}
	Var* F2(Var* a,Var* b) override{
		a = GetVar(a); b = GetVar(b);
		if(a->type=='b'&&b->type=='b') return new Var(To_Bool(a)||To_Bool(b));
		return new Var(To_Int(a)|To_Int(b));
	}
};
class And:public Operator{
public:
	And(){
		oper="&&";
		is_unary=false;
		priority=0;
	}
	Var* F2(Var* a,Var* b) override{
		a = GetVar(a); b = GetVar(b);
		if(a->type=='b'&&b->type=='b') return new Var(To_Bool(a)&&To_Bool(b));
		return new Var(To_Int(a)&To_Int(b));
	}
};

std::vector<Operator*> operators = {new Add(),new Sub(),new Asg(),new Equ(),new Mul(),new Div(),new Mod(),new Pow(),new More(),new MoreE(),new Less(),new LessE(),new AddTo(),new SubTo(),new DivTo(),new MulTo(),new And(),new Or()};