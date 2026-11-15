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

    
    // Execute({"Console.Write(\"Hello world!\n\")"});
    // Execute({"a=Int(Console.Read())","for(10){","a=a+1","Console.Write(a+\"jsafasf\")","}"});
    Execute({"a = [1,2,3,4,5]","Console.Write(\"n\".to_n())","a.push(\"a\")","Console.Write(a)"});
}