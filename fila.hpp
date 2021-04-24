#include <iostream>
#include <vector>
#include "palabra.hpp"
#include "declaracion.hpp"
#include "function.hpp"
class fila {
    public: 
        fila(){
            estado = 0;
            es = NULL;
        }
        fila(declaracion d){
            *es = d;
            (d.isArray()) ? dim = d.getSize() : dim = 1;
            identificador = d.getVarName();
            type2 = 0;
            type = d.getType();
            bloque = d.getID().getCodeBlock().getBlock();
        }
        fila(funct f){
            *es = f;
            dim = 0;
            var = f.getPalabra();
            type = f.getType();
            type2 = 1;
            if(f.isDeclared()){
                estado = 1;
            }
            bloque = f.getNombre().getCodeBlock().getBlock();
            identificador = f.getNombre().getWord();
        }
        void insertarReferencia(int ref){ referencias.push_back(ref); }
        int getDim() { return dim; }
        palabra getVar() { return var; }
        palabra getType() { return type; }
        string getIdentificador() { return identificador; }
        int getType2() { return type2; }
        int getEstado() { return estado; }
        int getBloque() { return bloque; }
        estructura* getEstructura() { return es; }
        vector<int> getRef() { return referencias; }

    private:
        int dim;
        palabra var, type;
        string identificador;
        int type2, estado, bloque;
        estructura *es;
        vector<int> referencias;
};