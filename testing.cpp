#include <vector>
#include <iostream>
#include "parser.h"
#include "operators.h"
#include "variable.h"
#include "functions.h"


int main(){
    Decode(Parse("a=1.25"));
    Decode(Parse("b=1.25"));
    Decode(Parse("Console.Write(a+b)"));
}