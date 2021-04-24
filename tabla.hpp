#include <iostream>
#include "declaracion.hpp"
#include "function.hpp"
#include "fila.hpp"
#include "asignacion.hpp"
#include "condicional.hpp"
#include <map>
using namespace std;
class tabla {
    public:
        /*
            
        */
        void insertar(declaracion d){
            fila f(d);
            contenido.insert(pair<string, fila>(f.getIdentificador(), f));
        }
        void insertar(funct f){
            fila d(f);
            contenido.insert(pair<string, fila>(d.getIdentificador(), d));
        }
        void buscar(asignacion as){

        }
        void buscar(condicional con){

        }
    private:
        map<string, fila> contenido;
};