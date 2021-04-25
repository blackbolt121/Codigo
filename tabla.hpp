#pragma once
#include <iostream>
#include "function.hpp"
#include "condicional.hpp"
#include "palabra.hpp"
#include "declaracion.hpp"
#include "array.hpp"
#include "condicional.hpp"
#include "blanceo.hpp"
#include "encabezado.hpp"
#include "namespacing.hpp"
#include "asignacion.hpp"
#include "fila.hpp"
#include <map>
using namespace std;
class tabla {
    public:
        /*

        */
        void insertar(declaracion d){
            fila f(d);
            cout << f << endl;
            if(contenido.find(d.getVarName()) == contenido.end()){
                contenido.insert(pair<string, fila>(f.getIdentificador(), f));
            }
            else{
                fila aux = contenido[f.getIdentificador()];
                if(aux.getType2() == 0){
                    cout << aux.getIdentificador() << " ya fue definido como variable " << endl;
                    
                }else{
                    cout << aux.getIdentificador() << " ya fue definido como funcion " << endl;
                }
            }
        }
        void insertar(funct f){
            fila d;
            d.setFilaFuncion(f);
            if(contenido.find(d.getIdentificador()) == contenido.end())
                contenido.insert(pair<string, fila>(d.getIdentificador(), d));
            else{
                fila aux = contenido[d.getIdentificador()];
                if(aux.getType2() == 0){
                    cout << aux.getIdentificador() << " ya fue definido como variable " << endl;
                    errors.push_back(0);
                }else{
                    cout << aux.getIdentificador() << " ya fue definido como funcion " << endl;
                }
            }
        }
        void buscar(asignacion as)
        {
            /*
                LINEAS DE CODIGO NECESARIAS PARA VERIFICAR QUE LA VARIABLE A LA QUE SE ESTE HACIENDO REFERENCIA EXISTA
            */
            if(contenido.find(as.getVarName()) != contenido.end()){ //CHECA SI SE ENCUENTRA EN LA TABLA DE SIMBOLOS
                if(contenido[as.getVarName()].getType2() == 0){ //CHECA QUE DE ENCONTRARSE EN LA TABLA, SEA UNA VARIABLE Y NO UNA FUNCION
                    if(as.getVar().getCodeBlock().isChild(contenido[as.getVarName()].getVar().getBloque())){ //CHECA QUE ESTEN DENTRO DEL MISMO SCOPE
                        //AQUI VERIFICAMOS QUE LO QUE TENGA ASIGNADO CORRESPONDA AL TIPO
                        contenido[as.getVarName()].setEstado(1);
                        contenido[as.getVarName()].insertarReferencia(as.getVar().getRenglon());
                    }else{
                        // "Error variable no declarada en este scope ";
                    }
                    
                }else{
                    // "Error variable no encontrada, solo como funcion " << endl;
                }
            }else{
                // "Error variable no declarada en la tabla de simbolos" << endl;
            }

        }
        void buscar(condicional con){

        }
    private:
        map<string, fila> contenido;
        list<int> errors;
};