#include "parser.h"


int main(){
   //Execute({"a=1.25","b=1.25","Console.Write((a+b)+\"\n\")","if(a+b==2.5){","","Console.Write(\"YES\n\")","}"});
    std::vector<std::string> v = {
        "a=0",
        "b=0",
        "c=1",
        "for(10){",
        "a=b",
        "b=c",
        "c=a+b",
        "}",
        "Console.Write(c)"
    };

    

    Execute(v);
    // std::cout<<"\n\n";
    // for(Var* v:variables)
    //     std::cout<<v->name<<"("<<v->type<<") = "<<To_String(v)<<"\n";
}