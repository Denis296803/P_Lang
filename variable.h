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
            for(int i=0;i<31;i++){
                v[i/8] |= ((1<<i)&a)>>(i-i%4);
            }
            type='i';
        }
        Var(double a){
            uint64_t b;
            v.resize(8);
            std::memcpy(&a,&b,8);
            for(int i=0;i<7;i++){
                v[7-i] |= b&(255<<(i*8));
            }
            type='d';
        }
        Var(std::string a){
            v.resize(a.length());
            for(int i=0;i<a.length();i++){
                v[i]=a[i];
            }
            type='s';
        }
        int get_i(){
            int in=0;
            for(int i=0;i<v.size();i++)
                in |= v[i]<<(i*8);
            return in;
        }
        double get_d(){
            double o=0;
            uint64_t in=0;
            for(int i=0;i<v.size();i++)
                in |= v[i]<<(i*8);
            std::memcpy(&in,&o,64);
            return o;
        }
        std::string get_s(){
            std::string s;
            for(int i=0;i<v.size();i++)
                s = s+(char)v[i];
            return s;
        }
};