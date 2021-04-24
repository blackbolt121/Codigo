#pragma once
#include "estructura.hpp"
#include <vector>
using namespace std;

class condicional :public estructura{

    public:
        condicional() : estructura (){}
        void setPalabraClave(palabra p){
             if(p == 24){
                 this->palabra_clave = p;
                 pif = p;
             }
        }
        void insertInCondicion(palabra p){
            condicion.push_back(p);
        } 
        static condicional process(queue<palabra> q){
            condicional con;
            while(!q.empty()) {
                palabra actual = q.front();
                switch(actual){
                    case 24:
                        con.setPalabraClave(actual);
                        break;
                    case 27-31:
                    case 37-39:
                    case 42:
                    case 43-44:
                    case 56:
                    case 57-60:
                        con.insertInCondicion(actual);
                        break; //Guarda los operadores
                    case 41:
                        con.setBloque(actual.getBloque());
                        return con;
                        break; // En caso de encontrarse con una { devuelve el objeto
                    case 46:
                        if(q.size() == 1){
                            return con;
                        }
                    default:

                        break; // En caso de que encuentre palabra no validas no las procesa
                }
                q.pop();
            }
            return con;
        }

    private:
        palabra pif;
        palabra elsef;
        vector<palabra> elif;
        vector<palabra> condicion;
};