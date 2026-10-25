#include <vector>
#include <iostream>
#include "parser.h"
#include "operators.h"
#include "variable.h"
#include "functions.h"


int main(){
    std::vector<Operator*> opers = {new Add(),new Sub()};
    std::vector<Function*> funcs = {new Write()};
    Decode(Parse("Console.Write(1.23+2.34)",opers,funcs));
}