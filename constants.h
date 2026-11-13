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
std::vector<_Constant*> constants = {new Maybe()};
Var* GetConstant(std::string a){
	for(_Constant* c:constants){
		if(a==c->name) return c->F();}
	return nullptr;
}

