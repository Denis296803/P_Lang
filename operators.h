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
        if(a->type=='s'||b->type=='s'){
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
        if(a->type=='p') a=GetVar(To_Pointer(a));
        if(b->type=='p') b=GetVar(To_Pointer(b));
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
        if(a->type=='p') a=GetVar(To_Pointer(a));
        if(b->type=='p') b=GetVar(To_Pointer(b));
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
        if(a->type=='p') a=GetVar(To_Pointer(a));
        if(b->type=='p') b=GetVar(To_Pointer(b));
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
        if(a->type=='p') a=GetVar(To_Pointer(a));
        if(b->type=='p') b=GetVar(To_Pointer(b));
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
        if(a->type=='p') a=GetVar(To_Pointer(a));
        if(b->type=='p') b=GetVar(To_Pointer(b));
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
        if(b->type=='p') b = GetVar(To_Pointer(b));
        SetVar(To_Pointer(a),AutoVar(b));
        return b;
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
        //std::cout<<To_String(a)<<" "<<To_String(b);
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

std::vector<Operator*> operators = {new Add(),new Sub(),new Asg(),new Equ()};