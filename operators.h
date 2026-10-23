#pragma once

#include <string>

//* Просто сборище операторов, ничего особо интересного

class Operator
{
public:
    std::string oper;
    int priority;
    bool is_unary;
    virtual double F1(double a){return 0;};
    virtual double F2(double a, double b){return 0;};
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
    double F2(double a, double b) override
    {
        return a+b;
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
    double F2(double a, double b) override
    {
        return a-b;
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
    double F2(double a, double b) override
    {
        return a*b;
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
    double F2(double a, double b) override
    {
        return a/b;
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
    double F2(double a, double b) override
    {
        return (int)a%(int)b;
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
    double F2(double a, double b) override
    {
        return std::pow(a,b);
    }
};