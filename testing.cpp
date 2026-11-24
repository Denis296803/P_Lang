#include "parser.h"


int main(){
    /*Execute({
        "a=[1,2,3,4,5]",
        "for(0,a.length(),1,i){",
        "Console.Write(a[i]+\"\n\")",
        "}"
    });*/
    //Execute({"b = [[[[1,2,3,4,5],2,3,4,5],2,3,4,5],2,3,4,5]","Console.Write(b+\"\\n\")"});

    
    //Execute({"Console.Write(\"Hello world!\n\")"});
    //Execute({"a=Int(Console.Read())","for(10){","a=a+1","Console.Write(a+\"jsafasf\")","}"});
    Execute({"[1,2,3,4,5]","a = [1,2,3,4,5]","Console.Write(\"n\".to_n())","a.push(\"a\",0)","a[-1]=2","Console.Write(a+\"\\n\")","a.pop(0)","Console.Write(a)"});
    //Execute({"c=true","d=false","Console.Write(Str(c||d)+\" \"+Str(c&&d))"});
    std::cout<<"\n\n\n\n"; for(Var* v:variables) std::cout<<"\n"<<v->name<<"("<<v->type<<") = "<<To_String(v);
}