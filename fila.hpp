#include <iostream>
#include <vector>
#include "palabra.hpp"
#include "declaracion.hpp"
#include "function.hpp"
class fila {
    public: 
        fila(){
            
        }
        fila(declaracion p){
        }
        fila(funct f){

        }
    private:
        int dim;
        palabra var, type;
        string identificador;
        int type2, estado, bloque;
        vector<int> referencias;
};