#pragma once
#include <iostream>
#include "declaracion.hpp"
using namespace std;
class arreglo : public declaracion{

    public:
        arreglo() : declaracion(){
            this->size = 0;
            this->varname = "";
        }
        void setSize(int size){
            this->size = size;
        }
        void setVarname(string varname){
            this->varname = varname;
        }
        void setType(palabra type){
            this->type = type;
        }
        void setVar(palabra var){
            this->var = var;
        }
        int getSize(){
            return this->size;
        }
        string getVarname(){
            return this->varname;
        }
        palabra getVar(){
            return this->var;
        }
        palabra getType(){
            return this->type;
        }
        static arreglo process(queue<palabra> q){
            arreglo arr;
            while(!q.empty()){
                palabra p = q.front();
                string word = p.getWord(), aux="";
                switch(p){ 
                    case 8-12:
                        arr.setType(p);
                        break;
                    case 31:
                        arr.setPalabraClave(p);
                        arr.setVar(p);
                        //Con esta funcion lo que hacemos es guardar la nombre de la variable en arreglo
                        for(char s : word){
                            if(s != '[' || s != ']'){
                                aux+=s;
                            }else{
                                if(s == '['){
                                    arr.setVarname(aux);
                                    aux = "";
                                }else{
                                    arr.setSize(stoi(aux));
                                }
                                
                            }
                        }
                        break;
                    case 46:
                        return arr;
                        break;
                    default:
                        
                        break;
                }
            }
            return arr;
        }
    private:
        string varname;
        palabra type, var;
        int size;
};