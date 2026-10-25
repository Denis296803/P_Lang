#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "operators.h"
#include "variable.h"
#include "functions.h"

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
    bool is_func=true;
    _Operation(_Operation* par1,_Operation* par2,Operator* op){a=par1;b=par2;oper=op;is_leaf = false;is_func=false;}
    _Operation(Var* c){constant = c;is_leaf = true;}
    _Operation(Function* func,std::vector<_Operation*> args){function = func; arguments = args;is_leaf = false;is_func=true;}
    ~_Operation(){delete a; 
        delete b; 
        for (auto arg : arguments) delete arg;
        delete constant;
    };
};

// Парсер(да, знаю, удивительно)
_Operation* Parse(const std::string& string,const std::vector<Operator*>& operators, const std::vector<Function*>& functions){
    std::string str = string;
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
    if(indexesOper.size()>0||indexesFunc.size()>0){
        int bestIdOper=-1,bestDepthOper=2147483647,bestPriorityOper=2147483647,bestPositionOper=2147483647;
        int bestIdFunc=-1,bestDepthFunc=2147483647,bestPositionFunc=2147483647;
        std::vector<_Operation*> vec2;
        if(indexesOper.size()>0){
            //Если есть операторы, находим с наименьшим приоритетом
            
            for(int i=0;i<indexesOper.size();i++){
                if(bestDepthOper>depthsOper[i]||
                    bestDepthOper==depthsOper[i]&&bestPriorityOper>operators[opers[i]]->priority||
                    bestDepthOper==depthsOper[i]&&bestPriorityOper==operators[opers[i]]->priority&&bestPositionOper>indexesOper[i]
                ){
                    bestDepthOper=depthsOper[i];
                    bestPriorityOper=operators[opers[i]]->priority;
                    bestPositionOper=indexesOper[i];
                    bestIdOper=opers[i];
                }
            }
            //TODO: конвертация, все такое...

            
        }
        
        if(indexesFunc.size()>0){
            //Если есть функции, находим с наименьшим приоритетом
            
            for(int i=0;i<indexesFunc.size();i++){
                if(bestDepthFunc>depthsFunc[i]||
                    bestDepthFunc==depthsFunc[i]&&bestPositionFunc>indexesFunc[i]
                ){
                    bestDepthFunc=depthsFunc[i];
                    bestPositionFunc=indexesFunc[i];
                    bestIdFunc=funcs[i];
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
                vec2.push_back(Parse(vec1[i],operators,functions));
            }

            //TODO: тут тоже конвертация не помешала бы

        }
        if(bestDepthFunc>=bestDepthOper)
            return new _Operation(Parse(str.substr(0,bestPositionOper),operators,functions),Parse(str.substr(bestPositionOper+operators[bestIdOper]->oper.size()),operators,functions),operators[bestIdOper]);
        _Operation* operation = new _Operation(functions[bestIdFunc],vec2);
        return operation;
    }
    else{

        //TODO: добавить определитель типа и функции для конвертации(ниже функция string -> double)
        short int sign = 0,numIntParts=0,numDoubleParts=-1; unsigned long long int intPart=0,doublePart=0;
        for(int i=0;i<str.length();i++){
            if(str[i]=='-')
                sign=-1;
            else if(str[i]==','||str[i]=='.')
                numDoubleParts=0;
            else if(str[i]>='0'&&str[i]<='9'){
                if(sign==0) sign=1;
                if(numDoubleParts==-1){
                    numIntParts++;
                    intPart=intPart*10+str[i]-'0';
                }
                else{
                    numDoubleParts++;
                    doublePart=doublePart*10+str[i]-'0';
                }
            }
        }
        double output=sign*(intPart+doublePart/std::pow(10,numDoubleParts));
        return new _Operation(new Var(output));
    }

}
// Декодер(думаю, тут очевидно)
Var* Decode(_Operation* tree){
    if(tree->is_leaf)
        return tree->constant;
    else if(!(tree->is_leaf)){
        if(!tree->is_func){
            if(tree->oper->is_unary)
                return tree->oper->F1(Decode(tree->a));
            else
                return tree->oper->F2(Decode(tree->a),Decode(tree->b));
        }
        else{
            std::vector<Var*> v1;
            for(_Operation* v:tree->arguments){
                v1.push_back(Decode(v));
            }
            return tree->function->F(v1);
        }
    }
    else
        return 0;
}

