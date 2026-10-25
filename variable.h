#pragma once

#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>

class Var{
    public:
        char type;
        std::vector<uint8_t> v;
        Var(int a){
            v.resize(4);
            std::memcpy(v.data(), &a, 4);
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
            type='s';
        }
       int get_i(){
            int in;
            std::memcpy(&in, v.data(), 4);
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
            std::string s;
            for(int i=0;i<v.size();i++)
                s = s+(char)v[i];
            return s;
        }
};