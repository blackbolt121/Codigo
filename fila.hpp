#pragma once
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
        fila(declaracion &d){
            estado = 0;
            var = d.getID();
            (d.isArray()) ? dim = d.getSize() : dim = 1;
            identificador = d.getVarName();
            type2 = 0;
            type = d.getType();
            bloque = d.getID().getCodeBlock().getBlock();
        }
        fila(funct &f){
            estado = 0;
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
        void setFilaDeclaracion(declaracion &d){
            estado = 0;
            var = d.getID();
            (d.isArray()) ? dim = d.getSize() : dim = 1;
            identificador = d.getVarName();
            type2 = 0;
            type = d.getType();
            bloque = d.getID().getCodeBlock().getBlock();
        }
        void setFilaFuncion(funct &f){
            estado = 0;
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
        void setEstado( int estado ) { this->estado = estado; }  
        int getDim() { return dim; }
        palabra getVar() { return var; }
        palabra getType() { return type; }
        string getIdentificador() { return identificador; }
        int getType2() { return type2; }
        int getEstado() { return estado; }
        int getBloque() { return bloque; }
        estructura* getEstructura() { return es; }
        vector<int> getRef() { return referencias; }
        friend ostream& operator<< (ostream& os, fila f){ 
            //Identificador 
            os << f.identificador << " " << ((f.estado == 0)? "no definido ": "definido ") << f.var.getRenglon() << " " << f.getDim() << " " << f.type.getWord() << ((f.type2 == 0)? " variable" : " funcion ");
            os << " ( ";
            for(int n : f.referencias){
                os << n << " ";
            }
            os << ")";
            return os;
        }
    private:
        int dim;
        palabra var, type;
        string identificador;
        int type2, estado, bloque;
        estructura *es;
        vector<int> referencias;
};