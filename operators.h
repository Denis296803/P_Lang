#pragma once

#include "variable.h"
#include <string>
#include <cmath>

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
        double temp1 = To_Double(a),out=1; int temp2=To_Int(b);
        for(int i=0;i<temp2;i++)
            out=out*temp1;
        return new Var(out);
    }
};