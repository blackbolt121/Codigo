#include "estructura.hpp"
#include "iostream"
#include <map>
class funct : public estructura{
    public:
        funct(){}
        static funct process(queue<palabra> q){
            funct foo;
            int cont = 0;
            palabra auxt;
            while(!q.empty()){
                palabra aux = q.front();
                switch(aux){
                    case 8-13:
                        if(cont == 0){
                            foo.setType(aux);
                        }else{
                            auxt = aux;
                        }
                        break;
                    case 41:
                        foo.setBloque(aux.getBloque());
                        foo.setDelared();
                        break;
                    case 38-39://En cuanto se encuentre un parentesis, debe ignorar las palabras
                        break;
                    case 31:
                        if(cont == 0){
                            foo.setNombre(aux);
                            cont++;
                        }else{
                            if(!foo.isInArgumentes(aux))
                                foo.addArgument(aux,auxt);
                            else{
                                foo.setHasError(true);
                            }
                        }
                        break;
                    case 46:
                        return foo;
                        break;
                }
                q.pop();
            }   
        }
        void setType(palabra type){
            this->type = type;
        }
        void setNombre(palabra nombre){
            this->nombre = nombre;
        }
        void addArgument(palabra type, palabra var){
            this->arguments[var] = type;
        }
        void setReturn(palabra retur){
            this->retur = retur;
        }
        void setBloque(int bloque){
            this->bloque = bloque;
        }
        void setDelared(){
            this->delcared = true;
        }
        bool isInArgumentes(palabra p){
            if(arguments.find(p) != arguments.end()){
                return true;
            }
            return false;
        }
    private:
        palabra type;
        palabra nombre;
        map<palabra, palabra> arguments;
        palabra retur;
        int bloque;
        bool delcared;
};