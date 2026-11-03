#pragma once

#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <algorithm>



class Var{
    public:
        char type;
        std::vector<uint8_t> v;
        std::string name="";
        Var(long long int a){
            v.resize(8);
            std::memcpy(v.data(), &a, 8);
            type = 'i';
        }
        Var(bool a){
            v.resize(1);
            if(a) v[0]=255;
            else v[0]=0;
            type='b';
        }
        Var(double a){
            v.resize(8);
            std::memcpy(v.data(), &a, 8);
            type = 'd';
        }
        Var(std::string a){
            v.resize(a.length());
            for(int i=0;i<a.length();i++){
                v[i]=a[i];
            }
            if(a[0]=='"'&&a[a.length()-1]=='"') type='s';
            else type='p';
        }
        long long int get_i(){
            long long int in;
            std::memcpy(&in, v.data(), 8);
            return in;
        }
        double get_d(){
            double o;
            std::memcpy(&o, v.data(), 8);
            return o;
        }
        bool get_b(){
            return v[0]==255;
        }
        std::string get_s(){
            return std::string(v.begin(),v.end());
        }
        std::string get_p(){
            return std::string(v.begin(),v.end());
        }
};

std::vector<Var*> variables;

char Get_Type(std::string str){
    if(str[0]=='"'&&str[str.length()-1]=='"') return 's';
    bool wasMinus=false,wasPoint=false;
    for(int i=0;i<str.length();i++){
        if(str[i]=='-'){
            if(wasMinus) return 's';
            wasMinus=true;
        }
        else if(str[i]=='.'){
            if(wasPoint) return 's';
            wasPoint=true;
        }
        else if(str[i]<'0'||str[i]>'9') return 'p';
    }
    if(wasPoint) return 'd';
    else return 'i';
}
Var* GetVar(std::string);
Var* AutoVar(std::string);

std::string To_String(Var* x);
std::string To_String(double x){
    std::string a; int sign=1;
    if(x==0) return "0";
    if(x<0){x=x*(-1);sign=-1;}
    int i1=(long long int)x;double i3=10*(x-(long long int)x);
    while(i1>0){a=a+(char)(i1%10+'0');i1=i1/10;}
    if(sign==-1){a=a+'-';}
    std::reverse(a.begin(),a.end());
    if(i3!=0) a=a+'.';
    while(i3>0){a=a+(char)((int)i3+'0');i3=10*(i3-(int)i3);}
    a=a;
    return a;
}
std::string To_String(long long int x){
    std::string a; int sign=1;
    if(x<0){sign=-1;x=x*(-1);}
    if(x==0) return "0";
    while(x>0){
        a=a+(char)(x%10+'0');
        x=x/10;
    }
    if(sign==-1){a=a+'-';}
    std::reverse(a.begin(),a.end());
    a=a;
    return a;
}
std::string To_String(std::string x){
    return x;
}
std::string To_String(Var* x){
    //std::cout<<x->get_p();
    if(x->type=='d') return To_String(x->get_d());
    if(x->type=='s') return To_String(x->get_s());
    if(x->type=='i') return To_String(x->get_i());
    if(x->type=='p') return To_String(x->get_p());
}

double To_Double(double x){
    return x;
}
double To_Double(long long int x){
    return (double)x;
}
double To_Double(std::string x){
    double a=0;int deg=1;
    bool wasPoint=false,wasMinus=false;
    for(int i=0;i<x.size();i++){
        if(x[i]=='.') wasPoint=true;
        else if(x[i]=='-') wasMinus=true;
        else if(x[i]>='0'&&x[i]<='9'){
            if(wasPoint){
                a=a+(int)(x[i]-'0')*std::pow(0.1,deg);
                deg++;
            }
            else{
                a=a*10+(int)(x[i]-'0');
            }

        }
        else return 69828.27982;
    }
    if(wasMinus) a=a*(-1);
    return a;
}
double To_Double(Var* x){
    if(x->type=='d') return To_Double(x->get_d());
    else if(x->type=='i') return To_Double(x->get_i());
    else if(x->type=='s') return To_Double(x->get_s());
    else if(x->type=='p') return To_Double(GetVar(x->get_p()));
}

long long int To_Int(double x){
    return (long long int)x;
}
long long int To_Int(long long int x){
    return x;
}
long long int To_Int(std::string x){
    double a=0;
    bool wasMinus=false;
    for(int i=0;i<x.size();i++){
        if(x[i]=='-') wasMinus=true;
        else if(x[i]>='0'&&x[i]<='9'){
            a=a*10+(int)(x[i]-'0');
        }
        else return 6982827982;
    }
    if(wasMinus) a=a*(-1);
    return a;
}
long long int To_Int(Var* x){

    if(x->type=='d') return To_Int(x->get_d());
    else if(x->type=='i') return To_Int(x->get_i());
    else if(x->type=='s') return To_Int(x->get_s());
    else if(x->type=='p') return To_Int(GetVar(x->get_p()));
}

std::string To_Pointer(std::string str){
    if(str[0]=='"'&&str[str.length()-1]=='"') str = str.substr(1,str.length()-2);
    return str;
}
std::string To_Pointer(Var* v){
    return To_Pointer(To_String(v));
}

Var* GetVar(std::string a){
    std::cout<<variables.size()<<std::endl;
    for(Var* v : variables){
        std::cout<<To_String(a)<<" "<<v->name<<std::endl;
        if(v->name==To_String(a)){
            return v;
        }
    }
    std::cout<<"No such var."<<std::endl;
    throw 'f';
}

Var* SetVar(std::string a,Var* b){
    for(Var* v : variables){
            if(v->name==a){
                v->type=b->type;
                v->v=b->v;
                return b;
            }
    }
    b->name=To_String(a);
    variables.push_back(b);
    return b;
}

Var* AutoVar(std::string str){
    char type = Get_Type(str);
    if(type=='d') return new Var(To_Double(str));
    else if(type=='i') return new Var(To_Int(str));
    else if(type=='s') return new Var(To_String(str));
    else if(type=='p') return new Var(To_Pointer(str));
}
Var* AutoVar(Var* v){
    if(v->type=='s'){
        return AutoVar(v->get_s());
    }
    else return v;
}
