#include "parser.h"


int main(){
    Decode(Parse("a=1.25"));
    Decode(Parse("b=1.25"));
    std::cout<<variables.size();
    Decode(Parse("Console.Write((a+b)+\"c\")"));
}