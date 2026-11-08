#include "parser.h"


int main(){
    Execute({"a=1.25","b=1.25","Console.Write((a+b)+\"\n\")","if(a+b==2.5)","{","Console.Write(\"YES\")","}"});
    // _Decode(_Parse("a=1.25"));
    // _Decode(_Parse("b=1.25"));
    // _Decode(_Parse("Console.Write((a+b))"));
}