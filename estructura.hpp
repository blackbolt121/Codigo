#pragma once
#include <queue>
#include <iostream>
#include "palabra.hpp"
using namespace std;
class estructura {
    public:
        virtual palabra getPalabra(){
            return this->palabra_clave;
        }
        estructura(){
            this->hasError = false;
        }
        ~estructura(){
        }
        virtual void setPalabraClave(palabra p){
            this->palabra_clave = p;
        };
        void setNivel(int nivel){
            this->nivel = nivel;
        }
        void setHasError(bool hasError){
            this->hasError = hasError;
        }
        void setBloque(int bloque){
            this->bloque = bloque;
        }
        virtual void imprimir() {
            cout << "Estructura" << endl;
        }
    protected:
        int nivel, bloque;
        palabra palabra_clave;
        bool hasError;
};