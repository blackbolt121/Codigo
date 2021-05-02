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
            f = nullptr;
            d = nullptr;
        }
        fila(declaracion &d){
            f = nullptr;
            es = &d;
            this->d = &d;
            estado = 0;
            var = d.getID();
            (d.isArray()) ? dim = d.getSize() : dim = 1;
            esArray = d.isArray();
            identificador = d.getVarName();
            type2 = 0;
            type = d.getType();
            bloque = d.getID().getCodeBlock().getBlock();
        }
        fila(funct &f){
            d = nullptr;
            es = &f;
            this->f = &f;
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
            f = nullptr;
            es = &d;
            this->d = &d;
            estado = 0;
            var = d.getID();
            (d.isArray()) ? dim = d.getSize() : dim = 1;
            esArray = d.isArray();
            identificador = d.getVarName();
            type2 = 0;
            type = d.getType();
            bloque = d.getID().getCodeBlock().getBlock();
        }
        void setFilaFuncion(funct &f){
            d = nullptr;
            es = &f;
            this->f = &f;
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
        bool isArray() { return esArray; }
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
        funct* getFunct(){
            return this->f;
        }
        declaracion* getDeclaracion(){
            return this->d;
        }
    private:
        int dim;
        bool esArray;
        palabra var, type;
        string identificador;
        int type2, estado, bloque;
        estructura *es;
        declaracion *d;
        funct *f;
        vector<int> referencias;
};