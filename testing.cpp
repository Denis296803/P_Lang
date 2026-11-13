#include "parser.h"


int main(){
   //Execute({"a=1.25","b=1.25","Console.Write((a+b)+\"\n\")","if(a+b==2.5){","","Console.Write(\"YES\n\")","}"});
    // std::vector<std::string> v = {
    //     "a=2",
    //     "for(7){",
    //     "a=a+a",
    //     "}",
    //     "Console.Write(a)"
    // };

    
    Execute({"Console.Write(\"Hello world!\n\")"});
    Execute({"for(10){","Console.Write(maybe)","Console.Write(\"\n\")","}"});
}