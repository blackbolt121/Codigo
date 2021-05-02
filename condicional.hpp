#pragma once
#include "estructura.hpp"
#include "variable.hpp"
#include <vector>
using namespace std;

class condicional : public estructura
{

    public:

        condicional() {}
        void setPalabraClave(palabra &p){
             if(p == 24){
                 this->palabra_clave = p;
                 pif = p;
             }
        }
        void insertInCondicion(palabra p){
            condicion.push_back(p);
        }
        static condicional process(queue<palabra> &q){
            condicional con;
            while(!q.empty()) {
                palabra &actual = q.front();
                switch(actual){
                    case 24:
                        con.setPalabraClave(actual);
                        break;
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                        if(actual == 31){
                            variable var(actual);
                            con.insertVarsInCondition(var);
                        }
                    case 37:
                    case 38:
                    case 39:
                    case 42:
                    case 43:
                    case 44:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                        con.insertInCondicion(actual);
                        break; //Guarda los operadores
                    case 41:
                        con.setBloque(actual.getBloque());
                        return con;
                        break; // En caso de encontrarse con una { devuelve el objeto
                    case 46:
                        return con;
                    default:

                        break; // En caso de que encuentre palabra no validas no las procesa
                }
                q.pop();
            }
            return con;
        }
        void insertVarsInCondition(variable &v){
            vars.push_back(v);
        }
        vector<palabra> getCondicion(){
            return condicion;
        }
        vector<variable> getVarsInCondition(){
            return vars;
        }
        palabra getPalabra() {
            return pif;
        }

    private:

        palabra pif;
        vector<palabra> condicion;
        vector<variable> vars;
        condicional *con;
        
};