#pragma once
#include <iostream>
#include "palabra.hpp"
#include <regex>
using namespace std;
class variable{
    public:
        variable(){
            varname = "";
            dim = 1;
            esArray = false;

        }
        variable(palabra &p){
            this->p = p;
            smatch m;
            string varN = p.getWord(), aux = "";
            if(regex_search(varN , m, r)){
                esArray = true;
                for(char s : varN){
                    if(s != '[' && s != ']'){
                        aux+=s;
                    }else{
                        if(s == '['){
                            varname = aux;
                            cout << aux << endl;
                            aux = "";
                        }else if(s == ']'){
                            dim *= stoi(aux);
                        }
                    }
                } 
            }else{
                varname = p.getWord();
                dim = 1;
                esArray = false;
            }
        }
        void setType(palabra Type){
            type = Type;
        }
        static regex r;
        palabra getVariable(){
            return p;
        }
        palabra getType(){
            return type;
        }
        int getDim(){
            this->dim;
        }
        bool isArray(){
            return esArray;
        }
        string getVarname(){
            return varname;
        }
    private:
        palabra p, type;
        string varname;
        int dim;
        bool esArray;
         //regex("(^[_$a-zA-Z]+[_$a-zA-Z0-9]*(\\[([_$a-zA-Z]+[_$a-zA-Z0-9]*|[0-9]+)\\])+$)");
};
regex variable::r = regex("(^[_$a-zA-Z]+[_$a-zA-Z0-9]*(\\[([_$a-zA-Z]+[_$a-zA-Z0-9]*|[0-9]+)\\])+$)");