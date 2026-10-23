#include <vector>
#include <iostream>
#include "parser.h"
#include "operators.h"


int main(){
    std::vector<Operator*> operators {new Add(),new Sub(),new Mul(),new Div(),new Mod(),new Pow()};
    std::cout<<Decode(Parse("1.123^2.234",operators));
}