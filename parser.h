#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "operators.h"
#include "variable.h"
#include "functions.h"



std::vector<Operator*> operators = {new Add(),new Sub(),new Asg()};
std::vector<Function*> functions = {new Write()};


//* Парсер

// Класс, который является узлом дерева
class _Operation
{
public:
    _Operation* a; _Operation* b;
    Operator* oper;
    Var* constant;
    std::vector<_Operation*> arguments;
    Function* function;
    bool is_leaf = false;
    bool is_func = false;
    _Operation(_Operation* par1,_Operation* par2,Operator* op){a=par1;b=par2;oper=op;is_leaf = false;is_func=false;}
    _Operation(Var* c){constant = c;is_leaf = true;is_func=false;}
    _Operation(Function* func,std::vector<_Operation*> args){function = func; arguments = args;is_leaf = false;is_func=true;}
    ~_Operation(){delete a; 
        delete b; 
        for (auto arg : arguments) delete arg;
        delete constant;
    };
};

// Парсер(да, знаю, удивительно)
_Operation* Parse(const std::string& string){
    //std::cerr<<"Parse: "<<string<<std::endl;
    std::string str = string;
    if(string[0]=='"'&&string[string.length()-1]=='"'){
        Var* v = new Var(string.substr(1,string.length()-2));
        v->type='s';    
        return new _Operation(v);
    }
    if(str.size()==0){return new _Operation(0);}
    //Обрезка скобок
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
            if(indexOper1!=indexOper2&&indexesOper[indexOper1]==indexesOper[indexOper2]&&operators[opers[indexOper1]]->oper.length()<operators[opers[indexOper2]]->oper.length()){
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
            for(int i=0;i+functions[indexFunc]->name.size()<=str.size();i++){
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
            if(indexFunc1!=indexFunc2&&indexesFunc[indexFunc1]==indexesFunc[indexFunc2]&&functions[funcs[indexFunc1]]->name.length()<functions[funcs[indexFunc2]]->name.length()){
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

    if(indexesOper.size()>0||indexesFunc.size()>0){
        int bestIdOper=-1,bestDepthOper=2147483647,bestPriorityOper=2147483647,bestPositionOper=2147483647;
        int bestIdFunc=-1,bestDepthFunc=2147483647,bestPositionFunc=2147483647;
        std::vector<_Operation*> vec2;
        if(indexesOper.size()>0){
            //Если есть операторы, находим с наименьшим приоритетом
            
            for(int i=0;i<indexesOper.size();i++){
                if(bestDepthOper>depthsOperFinal[i]||
                    bestDepthOper==depthsOperFinal[i]&&bestPriorityOper>operators[opers[i]]->priority||
                    bestDepthOper==depthsOperFinal[i]&&bestPriorityOper==operators[opers[i]]->priority&&bestPositionOper>indexesOperFinal[i]
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
                vec2.push_back(Parse(vec1[i]));
            }

        }
        if(bestDepthFunc>=bestDepthOper)
            return new _Operation(Parse(str.substr(0,bestPositionOper)),Parse(str.substr(bestPositionOper+operators[bestIdOper]->oper.size())),operators[bestIdOper]);
        _Operation* operation = new _Operation(functions[bestIdFunc],vec2);
        return operation;
    }
    else{
        //std::cout<<"Parse: "<<string<<";"<<std::endl;
        return new _Operation(AutoVar(str));
    }

}
// Декодер(думаю, тут очевидно)
Var* Decode(_Operation* tree){
    if(tree->is_leaf){
        return tree->constant;
    }
    else if(!(tree->is_leaf)){
        if(!(tree->is_func)){
            if(tree->oper->is_unary){
                Var* a = tree->oper->F1(Decode(tree->a));
                return a;
                delete a;
            }
            else{
                Var* a=Decode(tree->a); Var* b=Decode(tree->b);
                return tree->oper->F2(a,b);
                delete a,b;
            }
        }
        else{
            std::vector<Var*> v1;
            for(_Operation* v:tree->arguments){
                //std::cerr<<"Call_";
                v1.push_back(Decode(v));
            }
            Var* temp = tree->function->F(v1);
            return temp;
            delete temp;
        }
    }
    else
        return 0;
}

