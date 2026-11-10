#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "operators.h"
#include "variable.h"
#include "functions.h"



std::vector<Operator*> operators = {new Add(),new Sub(),new Asg(),new Equ()};
std::vector<Function*> functions = {new Write()};
std::vector<ExeFunction*> exeFunctions = {new If(),new For()};


//* Парсер

// Класс, который является узлом дерева
class _Operation
{
public:
    _Operation* a; _Operation* b;
    Operator* oper;
    Var* constant;
    std::vector<_Operation*> arguments;
    std::vector<_Operation*> code;
    Function* function;
    ExeFunction* exeFunc;
    bool is_leaf = false,is_func = false,func_exe=false;
    _Operation(_Operation* par1,_Operation* par2,Operator* op){a=par1;b=par2;oper=op;is_leaf = false,is_func=false,func_exe=false;}
    _Operation(Var* c){constant = c;is_leaf = true,is_func=false,func_exe=false;}
    _Operation(Function* func,std::vector<_Operation*> args){function = func; arguments = args;is_leaf = false,is_func=true,func_exe=false;}
    _Operation(ExeFunction* func,std::vector<_Operation*> args,std::vector<_Operation*> text){exeFunc = func; arguments = args;code=text;is_leaf = false,is_func=true,func_exe=true;}
    ~_Operation(){
        delete a; 
        delete b; 
        for (auto arg : arguments) delete arg;
        delete constant;
    };
};

// Парсер(да, знаю, удивительно)
_Operation* _Parse(const std::string& string){
    //std::cout<<"Parse: "<<string<<";";
    std::string str = string;
    if(str.size()==0){return new _Operation(0);}
    //Обрезка скобок
    while(str[0]==' ') str=str.substr(1,str.length()-1);
    while(str[str.size()-1]==' ') str=str.substr(0,str.length()-1);
    if(string.length()>1){
        while(true){
            if(str[0]=='('&&str[str.size()-1]==')'){
                std::string temp = str.substr(1,str.size()-2);
                int c=0;
                for(int i=0;i<temp.size();i++){
                    if(temp[i]=='(') c++;
                    else if(temp[i]==')'){
                        c--;
                        if(c<0) break;
                    }
                }
                if(c >= 0)
                    str=temp;
                else
                    break;
            }
            else
                break;
        }
    }
    //std::cout<<string<<std::endl;
    if(string[0]=='"'&&string[string.length()-1]=='"'){
        Var* v = new Var(string.substr(1,string.length()-2));
        v->type='s';    
        return new _Operation(v);
    }
    //Нахождение всех операторов
    std::vector<int> indexesOper,opers,depthsOper,funcs,indexesFunc,depthsFunc;
    for(int indexOper=0;indexOper<operators.size();indexOper++){
        for(int i=0;i+operators[indexOper]->oper.size()<=str.size();i++){
            if(str.substr(i,(operators[indexOper]->oper.size()))==operators[indexOper]->oper){
                int c1=0,c2=0;
                for(int j=0;j<i;j++){
                    if(str[j]=='(') c1++;
                    else if(str[j]==')') c1--;
                    else if(str[j]=='"') c2++;
                }
                if(c2%2==0){indexesOper.push_back(i);opers.push_back(indexOper); depthsOper.push_back(c1);}
            }
        }
    }
    std::vector<int> indexesOperFinal,opersFinal,depthsOperFinal,funcsFinal,indexesFuncFinal,depthsFuncFinal;

    for(int indexOper1=0;indexOper1<opers.size();indexOper1++){
        bool was_found=false;
        for(int indexOper2=0;indexOper2<opers.size();indexOper2++){
            if(indexOper1!=indexOper2&&(indexesOper[indexOper1]+operators[opers[indexOper1]]->oper.length()>indexesOper[indexOper2]&&indexesOper[indexOper1]<indexesOper[indexOper2]||indexesOper[indexOper2]+operators[opers[indexOper2]]->oper.length()>indexesOper[indexOper1]&&indexesOper[indexOper2]<indexesOper[indexOper1])&&operators[opers[indexOper1]]->oper.length()<operators[opers[indexOper2]]->oper.length()){
                was_found=true;
                break;
            }
        }
        if(!was_found){
            indexesOperFinal.push_back(indexesOper[indexOper1]);
            depthsOperFinal.push_back(depthsOper[indexOper1]);
            opersFinal.push_back(opers[indexOper1]);
        }
    }


    for(int indexFunc=0;indexFunc<functions.size();indexFunc++){
        for(int i=0;i+functions[indexFunc]->name.size()<str.size();i++){
            if(str.substr(i,(functions[indexFunc]->name.size()))==functions[indexFunc]->name){
                int c1=0,c2=0;
                for(int j=0;j<i;j++){
                    if(str[j]=='(') c1++;
                    else if(str[j]==')') c1--;
                    else if(str[j]=='"') c2++;
                }
                if(c2%2==0){indexesFunc.push_back(i);funcs.push_back(indexFunc); depthsFunc.push_back(c1);}
            }
        }
    }

    for(int indexFunc1=0;indexFunc1<funcs.size();indexFunc1++){
        bool was_found=false;
        for(int indexFunc2=0;indexFunc2<funcs.size();indexFunc2++){
            if(indexFunc1!=indexFunc2&&(indexesFunc[indexFunc1]+functions[funcs[indexFunc1]]->name.length()>indexesFunc[indexFunc2]&&indexesFunc[indexFunc1]<indexesFunc[indexFunc2]||indexesFunc[indexFunc2]+functions[funcs[indexFunc2]]->name.length()>indexesFunc[indexFunc1]&&indexesFunc[indexFunc2]<indexesFunc[indexFunc1])&&functions[funcs[indexFunc1]]->name.length()<functions[funcs[indexFunc2]]->name.length()){
                was_found=true;
                break;
            }
        }
        if(!was_found){
            indexesFuncFinal.push_back(indexesFunc[indexFunc1]);
            depthsFuncFinal.push_back(depthsFunc[indexFunc1]);
            funcsFinal.push_back(funcs[indexFunc1]);
        }
    }

    if(indexesOperFinal.size()>0||indexesFuncFinal.size()>0){
        int bestIdOper=-1,bestDepthOper=2147483647,bestPriorityOper=2147483647,bestPositionOper=2147483647;
        int bestIdFunc=-1,bestDepthFunc=2147483647,bestPositionFunc=2147483647;
        std::vector<_Operation*> vec2;
        if(indexesOper.size()>0){
            //Если есть операторы, находим с наименьшим приоритетом
            
            for(int i=0;i<indexesOperFinal.size();i++){
                if(bestDepthOper>depthsOperFinal[i]||
                    bestDepthOper==depthsOperFinal[i]&&bestPriorityOper>operators[opersFinal[i]]->priority||
                    bestDepthOper==depthsOperFinal[i]&&bestPriorityOper==operators[opersFinal[i]]->priority&&bestPositionOper>indexesOperFinal[i]
                ){
                    bestDepthOper=depthsOperFinal[i];
                    bestPriorityOper=operators[opersFinal[i]]->priority;
                    bestPositionOper=indexesOperFinal[i];
                    bestIdOper=opersFinal[i];
                }
            }

            
        }
        
        if(indexesFunc.size()>0){
            //Если есть функции, находим с наименьшим приоритетом
            
            for(int i=0;i<indexesFuncFinal.size();i++){
                if(bestDepthFunc>depthsFuncFinal[i]||
                    bestDepthFunc==depthsFuncFinal[i]&&bestPositionFunc>indexesFuncFinal[i]
                ){
                    bestDepthFunc=depthsFuncFinal[i];
                    bestPositionFunc=indexesFuncFinal[i];
                    bestIdFunc=funcsFinal[i];
                }
            }
            std::vector<std::string> vec1;
            int last=bestPositionFunc+functions[bestIdFunc]->name.size(),c1=0,c2=0;
            for(int i=bestPositionFunc+functions[bestIdFunc]->name.size();i<str.length()-1;i++){
                if(str[i]=='(') c1++;
                else if(str[i]==')') c1--;
                else if(str[i]=='"') c2++;
                else if(str[i]==','&&c2%2==0&&c1==0){vec1.push_back(str.substr(last,i-last));last=i;}
            }
            if(last<str.length()){
                vec1.push_back(str.substr(last,str.length()-last));
            }
            for(int i=0;i<vec1.size();i++){
                vec2.push_back(_Parse(vec1[i]));
            }

        }
        if(bestDepthFunc>=bestDepthOper)
            return new _Operation(_Parse(str.substr(0,bestPositionOper)),_Parse(str.substr(bestPositionOper+operators[bestIdOper]->oper.size())),operators[bestIdOper]);
        _Operation* operation = new _Operation(functions[bestIdFunc],vec2);
        return operation;
    }
    else{
        return new _Operation(AutoVar(str));
    }

}
// Декодер(думаю, тут очевидно)
Var* _Decode(_Operation* tree){
    if(tree->is_leaf){
        return tree->constant;
    }
    else if(!(tree->is_leaf)){
        if(!(tree->is_func)){
            //std::cout<<"Decode: "<<tree->oper->oper<<std::endl;
            if(tree->oper->is_unary){
                Var* a = tree->oper->F1(_Decode(tree->a));
                return a;
                delete a;
            }
            else{
                Var* a=_Decode(tree->a); Var* b=_Decode(tree->b);
                return tree->oper->F2(a,b);
                delete a,b;
            }
        }
        else{
            if(!(tree->func_exe)){
                //std::cout<<"Decode: "<<tree->function->name<<std::endl;
                std::vector<Var*> v1;
                for(_Operation* v:tree->arguments){
                    v1.push_back(_Decode(v));
                }
                Var* temp = tree->function->F(v1);
                return temp;
                delete temp;
            }
            else{
                tree->exeFunc->F(tree->arguments,tree->code);
                return nullptr;
            }
        }
    }
    return nullptr;
}

std::vector<_Operation*> ParseMega(std::vector<std::string> st);

void Execute(std::vector<std::string> strings){
    std::vector<_Operation*> v = ParseMega(strings);
    //std::cout<<"Decode";
    for(_Operation* o:v){
        //std::cout<<To_String(_Decode(o))<<std::endl;
        _Decode(o);
    }
}

std::vector<_Operation*> _GetArgs(const std::string& string){
    std::string str = string;
    while(str[0]==' ') str=str.substr(1,str.length()-1);
    while(str[str.size()-1]==' ') str=str.substr(0,str.length()-1);
    while(true){
        if(str[0]=='('&&str[str.size()-1]==')'){
            std::string temp = str.substr(1,str.size()-2);
            int c=0;
            for(int i=0;i<temp.size();i++){
                if(temp[i]=='(') c++;
                else if(temp[i]==')'){
                    c--;
                    if(c<0) break;
                }
            }
            if(c >= 0)
                str=temp;
            else
                break;
        }
        else
            break;
    }
    std::vector<std::string> vec1;
    std::vector<_Operation*> vec2;
    int last=0,c1=0,c2=0;
    for(int i=0;i<str.length()-1;i++){
        if(str[i]=='(') c1++;
        else if(str[i]==')') c1--;
        else if(str[i]=='"') c2++;
        else if(str[i]==','&&c2%2==0&&c1==0){vec1.push_back(str.substr(last,i-last));last=i;}
    }
    if(last<str.length()){
        vec1.push_back(str.substr(last,str.length()-last));
    }
    for(int i=0;i<vec1.size();i++){
        vec2.push_back(_Parse(vec1[i]));
    }
    return vec2;
}

std::vector<_Operation*> ParseMega(std::vector<std::string> strings){
    bool was_found=false; int startIndex=-1,startIndexString=-1,endIndex=-1,endIndexString=-1,counterBrack=0,counterFancy=0,indexFunc=-1; ExeFunction* func=nullptr;
    std::vector<_Operation*> out,args;
    for(int i=0;i<strings.size();i++){
        std::string string = strings[i];
        //std::cout<<string<<std::endl;
        if(string!=""){
            if(!was_found){
                for(ExeFunction* f:exeFunctions){
                    for(int index=0;index+(int)f->name.length()<=string.size();index++){
                        int counters[3] = {0,0,0};
                        if(string.substr(index,f->name.length())==f->name&&counters[0]%2==0&&counters[1]==0&&counters[2]==0){
                            was_found=true;
                            indexFunc=i;
                            int tempCounters[3] = {0,0,0};
                            for(int a=i;a<strings.size();a++){
                                for(int b=0;b<strings[a].size();b++){
                                    std::string str = strings[a];
                                    char ch = strings[a][b];
                                    if(ch=='"') tempCounters[0]++;
                                    else if(ch=='{'&&tempCounters[0]%2==0&&tempCounters[1]==0&&tempCounters[2]==0){
                                        startIndex=a;startIndexString=b;
                                        counterBrack=(a==i)?(1):(0);
                                        break;
                                    }
                                    else if(ch=='('&&tempCounters[0]%2==0) tempCounters[1]++;
                                    else if(ch==')'&&tempCounters[0]%2==0) tempCounters[1]--;
                                    else if(ch=='['&&tempCounters[0]%2==0) tempCounters[2]++;
                                    else if(ch==']'&&tempCounters[0]%2==0) tempCounters[2]--;
                                }
                                if(startIndex!=-1&&startIndexString!=-1) break;
                            }
                            func=f;
                            break;
                        }
                        else if(strings[i][index]=='('&&counters[0]%2==0) counters[1]++;
                        else if(strings[i][index]==')'&&counters[0]%2==0) counters[1]--;
                        else if(strings[i][index]=='['&&counters[0]%2==0) counters[2]++;
                        else if(strings[i][index]==']'&&counters[0]%2==0) counters[2]--;
                        else if(strings[i][index]=='"') counters[0]++;
                    }
                    if(func!=nullptr) break;
                }
                if(!was_found) out.push_back(_Parse(string));
            }
            else{
                for(int a=0;a<string.size();a++){
                    if(string[a]=='"') counterFancy++;
                    else if(string[a]=='{'&&counterFancy%2==0) counterBrack++;
                    else if(string[a]=='}'&&counterFancy%2==0) counterBrack--;
                    if(counterBrack==0){
                        endIndex=i;
                        endIndexString=a;

                        std::vector<std::string> v1;
                        int startArgs=-1,endArgs=-1;
                        for(int j=0;j<strings[indexFunc].size();j++){
                            if(strings[indexFunc][j]=='('&&startArgs==-1) startArgs=j;
                            else if(strings[indexFunc][j]==')') endArgs=j;
                        }
                        args=_GetArgs(strings[indexFunc].substr(startArgs,endArgs-startArgs+1));
                        v1.push_back(strings[startIndex].substr(startIndexString+1));
                        for(int j=startIndex+1;j<endIndex;j++)
                            v1.push_back(strings[j]);
                        v1.push_back(strings[endIndex].substr(0,endIndexString-1));
                        std::vector<_Operation*> v2 = ParseMega(v1);
                        was_found=false;
                        counterBrack=0;
                        out.push_back(new _Operation(func,args,v2));
                        break;
                    }
                }
            }
        }
    }
    return out;
}