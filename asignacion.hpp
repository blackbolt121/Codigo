#include "estructura.hpp"
#include <list>
using namespace std;
class asignacion : estructura{
    public:
        asignacion() : estructura(){

        }
        palabra getVar(){return var;}
        list<palabra> getOperadores(){return operadores;}
        void setVar(palabra p){
            this->var = p;
        }
        void insertarOperador(palabra p){
            operadores.push_back(p);
        }
        palabra getPalabra(){
            return this->palabra_clave;
        }
        static asignacion process(queue<palabra> &q){
            bool asignado = false;
            palabra p;
            asignacion as;
            while(!q.empty()){
                p = q.front();
                switch(p){
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 37:
                    case 38:
                    case 39:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 54:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                        as.insertarOperador(p);
                        break;
                    case 31: //En caso de encontrar una variable
                        if(!asignado){
                            as.setPalabraClave(p);
                            as.setVar(p);
                            cout << p.getCodeBlock().getBlock() << endl;;
                        }else{
                            as.insertarOperador(p);
                        }
                        break;
                    
                    case 45: //Para no mantener esta linea vacia :( (es un caracter de espacio =)
                        asignado = true;
                        break;
                    case 46:
                        return as;
                    default:
                        break;
                }
                q.pop();
                
            }
            return as;
        } 
    private:
        palabra type;
        palabra var;
        list<palabra> operadores;
        bool esArray;
        int dim;
};