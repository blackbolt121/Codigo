#pragma once
#include <iostream>
#include <list>
#include <regex>
#include "tabla.hpp"
class semantica{
    public:
        semantica(){
            this->setAllFalse();
            r = regex(".+\\[.+\\]");
        }
        balanceo b;
        void analalize(palabra p);
        static semantica analizar(queue<palabra> &q){
            semantica s;
            balanceo b;
            while(!q.empty()) {
                b.insertarPalabra(q.front());
                s.analalize(q.front());
                q.pop();
            }
            s.mostrarAsignaciones();
            s.mostrarDeclaraciones();

            return s;
        }
        void mostrarDeclaraciones();
        void mostrarAsignaciones();
        void mostrarTabla();
    private:
        void controller(palabra p);
        tabla simbolos;
        list<estructura*> es;
        void limpiarCola(){
            while(!cache.empty()){
                cache.pop();
            }
        }
        //list<pair<palabra,list<palabra>>> asignaciones;
        bool esDeclarado, noParentesis, esAsignado, esFuncion, esCondicional, noGuardar, esArray, cabecera, esIF,esFor,esWhile;
        void setAllFalse(){
            esDeclarado = noParentesis = esAsignado = esFuncion = esCondicional = noGuardar = esArray = cabecera = esIF = esFor = esWhile = false;
        }
        palabra last, lastvar;
        queue<palabra> cache;
        regex r;

};

void semantica::mostrarTabla(){
    simbolos.mostrarTabla();
    
}
void semantica::analalize(palabra p){
   this->controller(p);

}
void semantica::controller(palabra p){
    this->cache.push(p);
    switch(p){
        case 0:
        case 1:
            cabecera = true; //Decimos que se asigna una cabecera
            break;
        case 8: //Indicadores de tipo
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            if(esFuncion == false) //En caso de que la bandera de esFuncion este prendida entonces no activa la bandera de es asignado porque rompería con el funcionamiento del programa
                esDeclarado = true; //Decimos que si recibe un parentesis guarde
            break;
        case 17: //Indicador de que se trata de un ciclo for

            setAllFalse();        
            esFor = true; //Decimos que si recibe una palabra for entonces seteamos esta variable en true y los otros en false
            
            break; // Así activamos la bandera de for

        case 18: //Indicador de que se trata de un ciclo while (palabra while encontrada)
            
            setAllFalse();
            esWhile = true;
            
            //Así activamos la bandera de while
            break;

        case 24: //Palabra IF

            setAllFalse();
            esIF = true;
            //Así activamos la bandera de if
            break;

        case 27:
        case 28: 
        case 29: 
        case 30: //Tipo de valores (entero, float, double, string)

            if(cabecera && p == 30){ //Para el caso en que se encuentre un string y se trate de una cabecera guarda y setea todas la banderas en falso
                //En caso de encontrarse con un string entonces debe guardarlo en la estructura de cabecera
                encabezado en = encabezado::process(cache);
                limpiarCola();
                setAllFalse();
            }
            break;
        case 31: //Para un ID
            if(!esDeclarado && (last == "{" || last == "}" || last == ";")){
                setAllFalse();
                esAsignado = true;
            }else {
                //Si la palabra anterior es un tipo se activa la vandera de declaracion
                if(8<=last && last<=13 && !(last == "(" || last == ";")){
                    esAsignado = true;
                    lastvar = p;
                }
            }
            break;
        case 39: //Parentesis izquierdo (
            if(last == 31){
                if((esDeclarado || esAsignado) && last == 31){ //Si la palabra anterior era una variable entonces s y tenemos una bandera de declaracion o asignacion entonces se trata de una funcion
                //llamada de una funcion o una declaracion de una funcion
                //Para una llamada o declaracion de una funcion
                    this->setAllFalse();
                    esFuncion = true;
                }
            }
            
            break;

        case 40: // Llave derecha
            
            break;

        case 41: //Llave izquierda
            if(esIF){
                condicional con = condicional::process(cache);
                simbolos.buscar(con);
                es.push_back(&con);
                limpiarCola();
                //Aqui vaciamos la cola;
            }else if(esFor){

                //Aqui vaciamoOS la cola
            }else if(esFuncion){
                funct foo = funct::process(cache);
                simbolos.insertar(foo);
                es.push_back(&foo);
                limpiarCola();
                //Aqui vaciamos la cola
            }else if(esWhile){
                ciclo c = ciclo::proccess(cache);
                simbolos.buscar(c);
                es.push_back(&c);
                //Aqui vaciamos la cola 
            }else if(esFor){

            }
            setAllFalse();
            break;

        case 45: //Igual
            if(esDeclarado){
                //Se debe guardar la declaracion
                declaracion dec = declaracion::process(cache);
                simbolos.insertar(dec);
                es.push_back(&dec);
                setAllFalse();
                esAsignado = true;
                cache.push(lastvar);
                cache.push(p);
            }else{
                //En caso de que no se active la bandera de declaracion y se requiera hacer otra cosa
                setAllFalse();
                esAsignado = true;
            }

            break;

        case 46: //Punto y coma
            if(esDeclarado){ //En caso de que se haya declarado entonces se guarda la declaracion
                declaracion dec = declaracion::process(cache);
                es.push_back(&dec);
                simbolos.insertar(dec);
                
                setAllFalse();

            }else if(esFuncion){
                
                funct f = funct::process(cache);
                es.push_back(&f);
                simbolos.insertar(f);
                setAllFalse();
                
            }else if(esAsignado){
                asignacion as = asignacion::process(cache);
                es.push_back(&as);
                simbolos.buscar(as);
                
                limpiarCola();
                setAllFalse();

            }else{

            }
            break;
        case 48: // >
            if(cabecera){
                encabezado cab = encabezado::process(cache);
                setAllFalse();
            }
            break;
        case 49: // <
            
            break;
    }
    last = p;
}


