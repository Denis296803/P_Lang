#include <vector>
#include <iostream>
#include "parser.h"
#include "operators.h"
#include "variable.h"
#include "functions.h"


int main(){
    std::vector<Operator*> opers = {new Add(),new Sub()};
    std::vector<Function*> funcs = {new Write()};
    Decode(Parse("Console.Write(\"1.25\"+\"3.75\")",opers,funcs));
    // std::string n="78.387";
    // std::cout<<To_Double(n)<<std::endl<<n;
}