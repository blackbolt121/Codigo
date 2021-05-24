#pragma once
#include "allheaders.hpp"
#include <list>
class ciclo : public estructura
{
public:
    ciclo() : estructura()
    {
    }
    static ciclo proccess(queue<palabra> &palabras)
    {
        ciclo c;
        while(!palabras.empty())
        {
            palabra p = palabras.front();
            switch(p){
                case 18:
                    c.setWhile(p);
                    break;
                case 27:
            case 28:
            case 29:
            case 30:
            case 31:
                if(p ==  31){
                    variable var(p);
                    c.insertInVars(var);
                    
                }
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
            case 56:
            case 57:
            case 58:
            case 59:
            case 60:
            case 61:
                c.insertCondicion(p);
                break; //Guarda los operadores
            case 41: // {
                c.setLlave(p);
                c.setBloque(p.getBloque());
                return c;
                break; // En caso de encontrarse con una { devuelve el objeto
            case 46: // ;
                return c;
            default: 
                break;
                    
            }
            palabras.pop();
        }
        return c;
    }
    void setWhile(palabra wh){
        if(wh == 18){
            this->wh = wh; 
        }
    }
    void insertCondicion(palabra &p){
        condicion.push_back(p);
    }
    void insertInVars(variable &v){
        vars.push_back(v);
    }
    void setLlave(palabra &llave){
        this->llave = llave;
    }
    void construir(){
        r.setOperadores(condicion);
        r.construir();
    }
    list<palabra>& getCondicion(){
        return condicion;
    }
    list<palabra> getPolish(){
        return r.getPolish();
    }
    list<variable>& getVars(){
        return vars;
    }
    palabra getLLave(){
        return llave;
    }
    void intermedio(){
        r.notacionPolacaInversa();
    }
    void imprimir(){
        cout << "Ciclo While" << endl;
    }
private:
    list<palabra> condicion;
    list<variable> vars;
    palabra llave;
    palabra wh;
    rpn r;
};