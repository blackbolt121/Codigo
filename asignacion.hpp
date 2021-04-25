#include "estructura.hpp"
#include <list>
using namespace std;
class asignacion : estructura{
    public:
        asignacion() : estructura(){
            esArray = false;
        }
        palabra getVar(){return var;}
        list<palabra> getOperadores(){return operadores;}
        void setVar(palabra p){
            this->var = p;
        }
        void setIsArray(bool r) { esArray =  r; }
        void setVarName(string varname) { this->varname = varname; }
        void insertarOperador(palabra p){
            operadores.push_back(p);
        }
        void setSize(int size) { dim = size; }
        int getSize() { return dim; }
        palabra getPalabra(){
            return this->palabra_clave;
        }
        string getVarName() { return varname; }
        static asignacion process(queue<palabra> &q){
            bool asignado = false;
            palabra p;
            asignacion as;
            smatch m;
            const regex r("(^[_$a-zA-Z]+[_$a-zA-Z0-9]*(\\[([_$a-zA-Z]+[_$a-zA-Z0-9]*|[0-9]+)\\])+$)");
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
                            string varN = p.getWord(), aux = "";
                            as.setVar(p);
                            if(regex_search(varN , m, r)){
                                as.setIsArray(true);
                                for(char s : varN){
                                    if(s != '[' && s != ']'){
                                        aux+=s;
                                    }else{
                                        if(s == '['){
                                            as.setVarName(aux);
                                            cout << aux << endl;
                                            aux = "";
                                        }else if(s == ']'){
                                            as.setSize(stoi(aux));
                                        }
                                        
                                    }
                                }
                                
                            }else{
                                as.setVarName(varN);
                                as.setVar(p);
                            }
                            asignado = true;
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
        string varname;
        list<palabra> operadores;
        bool esArray;
        int dim;
};