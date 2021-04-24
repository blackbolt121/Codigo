#pragma once
#include <iostream>
#include "estructura.hpp"
#include "semantica.hpp"
#include <regex>
class declaracion : public estructura{
    public:
        declaracion() : estructura() {
            esArray = false;
            size = 1;
        }
        void setPalabraClave(palabra p){
            this->palabra_clave = p;
        }
        void setID(palabra p){ (p == 31)? id = p : id = palabra();}
        void setIsArray(bool isArray) { this->esArray = isArray;}
        void setSize(int size) { this->size = size;}
        void setType(palabra type) { this->type = type;}
        void setVarname(string varname) { this-> varname = varname;}
        palabra getID(){return this->id;}
        bool isArray(){ return esArray;}
        int getSize(){ return size;}
        palabra getType(){ return type; }
        string getVarName(){ return varname;}
        static declaracion process(queue<palabra> &q);
        friend class semantica;
    protected:
        palabra id;
        palabra type;
        string varname;
        bool esArray;
        int size;
};
declaracion declaracion::process(queue<palabra> &q){
    declaracion arr;
    const regex r("(^[_$a-zA-Z]+[_$a-zA-Z0-9]*(\\[([_$a-zA-Z]+[_$a-zA-Z0-9]*|[0-9]+)\\])+$)");
    smatch match;
    while(!q.empty()){
        palabra p = q.front();
        string word = p.getWord(), aux="";
        bool esArray;
        switch(p){ 
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                arr.setType(p);
                break;
            case 31:
                arr.setPalabraClave(p);
                arr.setID(p);
                //Con esta funcion lo que hacemos es guardar la nombre de la variable en arreglo
                esArray = regex_search(word, match,r);
                if(esArray){
                    arr.setIsArray(true);
                    for(char s : word){
                        if(s != '[' && s != ']'){
                            aux+=s;
                        }else{
                            if(s == '['){
                                arr.setVarname(aux);
                                aux = "";
                            }else if(s == ']'){
                                arr.setSize(stoi(aux));
                            }
                            
                        }
                    }
                }
                else{
                    arr.setVarname(p.getWord());
                }
                break;
            case 46: // En caso de que encuentre un ; entonces devuelve el objeto
                break;
            default:
                break;
        }
        q.pop();
    }
    return arr;
}
