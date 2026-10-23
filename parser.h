#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "operators.h"

//* Парсер арифметики

// Класс, который является узлом дерева
class Operation
{
public:
    Operation* a; Operation* b;
    Operator* oper;
    double constant;
    bool is_leaf = false;
    Operation(Operation* par1,Operation* par2,Operator* op){a=par1;b=par2;oper=op;is_leaf = false;}
    Operation(double c){constant = c;is_leaf = true;}
    ~Operation(){delete a; delete b;};
};

// Парсер(да, знаю, удивительно)
Operation* Parse(const std::string& string,const std::vector<Operator*>& operators){
    std::string str = string;
    if(str.size()==0){return new Operation(0);}
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
    std::vector<int> indexes,ops,depths;
    for(int indexOper=0;indexOper<operators.size();indexOper++){
        for(int i=0;i<str.size()-operators[indexOper]->oper.size();i++){
            if(str.substr(i,(operators[indexOper]->oper.size()))==operators[indexOper]->oper){
                int c=0;
                for(int j=0;j<i;j++){
                    if(str[i]=='(') c++;
                    else if(str[i]==')') c--;
                }
                indexes.push_back(i);ops.push_back(indexOper); depths.push_back(c);
            }
        }
    }

    if(indexes.size()>0){
        //Если есть операторы, находим с наименьшим приоритетом
        int bestId,bestDepth=2147483647,bestPriority=2147647483,bestPosition=2147483647;
        
        for(int i=0;i<indexes.size();i++){
            if(bestDepth>depths[i]||
                bestDepth==depths[i]&&bestPriority>operators[ops[i]]->priority||
                bestDepth==depths[i]&&bestPriority==operators[ops[i]]->priority&&bestPosition<indexes[i]
            ){
                bestDepth=depths[i];
                bestPriority=operators[ops[i]]->priority;
                bestPosition=indexes[i];
                bestId=ops[i];
            }
        }
        return new Operation(Parse(str.substr(0,bestPosition),operators),Parse(str.substr(bestPosition+operators[bestId]->oper.length()),operators),operators[bestId]);
    }
    else{
        // Преобразователь std::string -> double
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
        return new Operation(output);
    }

}
// Декодер(думаю, тут очевидно)
double Decode(Operation* tree){
    if(tree->is_leaf)
        return tree->constant;
    else if(!(tree->is_leaf)){
        if(tree->oper->is_unary)
            return tree->oper->F1(Decode(tree->a));
        else
            return tree->oper->F2(Decode(tree->a),Decode(tree->b));
    }
    else
        return 0;
}