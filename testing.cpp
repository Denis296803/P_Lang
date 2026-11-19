#include "parser.h"


int main(){
    //Execute({"c=1.25","b=1.25","Console.Write((c+b)+\"\n\")","if(c+b==2.5){","","Console.Write(\"YES\n\")","}"});
    // std::vector<std::string> v = {
    //     "a=2",
    //     "for(7){",
    //     "a=a+a",
    //     "}",
    //     "Console.Write(a)"
    // };

    
    // Execute({"Console.Write(\"Hello world!\n\")"});
    // Execute({"a=Int(Console.Read())","for(10){","a=a+1","Console.Write(a+\"jsafasf\")","}"});
    Execute({"[1,2,3,4,5]","a = [1,2,3,4,5]","Console.Write(\"n\".to_n())","a.push(\"a\",0)","a[-1]=2","Console.Write(a)"});
    //std::cout<<"\n\n\n\n"; for(Var* v:variables) std::cout<<"\n"<<v->name<<"("<<v->type<<") = "<<To_String(v);
}