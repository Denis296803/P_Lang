#pragma once
#include "variable.h"
#include <iostream>
#include <random>
std::mt19937 rng(std::random_device{}());
class Var;
class _Constant{
	public:
		std::string name;
		virtual Var* F(){return new Var(0ll);}
};
class Maybe:public _Constant{
public: 
	Maybe(){name="maybe";}
	Var* F() override{
		return new Var(is(rng)==2);
	}
private:
	std::uniform_int_distribution<short int> is{1,3};
};
class Pie: public _Constant{
public:
	Pie(){name="Math.pi";}
	Var* F() override{
		return new Var(3.14159265359);
	}
};
class E: public _Constant{
public:
	E(){name="Math.e";}
	Var* F() override{
		return new Var(2.71828182846);
	}
};
std::vector<_Constant*> constants = {new Maybe(),new E(),new Pie()};
Var* GetConstant(std::string a){
	for(_Constant* c:constants){
		if(a==c->name) return c->F();}
	return nullptr;
}

