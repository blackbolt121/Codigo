#include "estructura.hpp"
#include "variable.hpp"
#include <list>
#include "rpn.hpp"
using namespace std;
class asignacion : estructura{
    public:
        asignacion() : estructura(){ esArray = false; }
        void setVar(palabra p){ this->var = p; }
        void setIsArray(bool r) { esArray =  r; }
        void setVarName(string varname) { this->varname = varname; }
        void insertarOperador(palabra p){ operadores.push_back(p); }
        void setSize(int size) { dim = size; }
        void insertVarAsign(variable &var){ this->vars.push_back(var); }
        list<variable> &getVarAsign() { return vars; }
        int getSize() { return dim; }
        palabra getVar(){return var.getVariable();}
        variable getVariable() { return var; }
        list<palabra> getOperadores(){ return operadores; }
        palabra getPalabra(){ return this->palabra_clave; }
        string getVarName() { return varname; }
        void construir(){
            if(operadores.size() > 0){
                list<palabra> aux = list<palabra>(operadores.begin(), operadores.end());
                this->r.setOperadores(aux);
                this->r.construir();
                cout << "Tamaño expresion: " << r.getPolish().size() << endl;
                for(palabra p : r.getPolish()){
                    cout << p.getWord() << " ";
                }
                cout << endl;
            }
        }
        bool isArray() { return esArray; }
        static asignacion process(queue<palabra> &q){
            bool asignado = false;
            palabra p;
            asignacion as;
            smatch m;
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
                        
                        if(!asignado)
                        {
                            variable v(p);
                            as.setVar(p);
                            as.setIsArray(v.isArray());
                            as.setSize(v.getDim()); 
                            as.setVarName(v.getVarname());
                            asignado = true;
                        }
                        else
                        {
                            variable v(p);
                            as.insertarOperador(p);
                            as.insertVarAsign(v);
                        }
                        break;
                    
                    case 45: //Para no mantener esta linea vacia :( (es un caracter de espacio =)
                        asignado = true;
                        break;
                    case 46:
                        for(palabra p : as.getOperadores()){
                            cout << p.getWord() << " ";
                        }
                        cout << endl;
                        return as;
                    default:
                        break;
                }
                q.pop();
                
            }
            return as;
        } 
    private:
        variable var;
        string varname;
        list<palabra> operadores;
        list<variable> vars;
        bool esArray;
        int dim;
        rpn r;
};