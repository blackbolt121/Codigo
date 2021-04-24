#pragma once
#include <iostream>
#include <list>
#include <regex>
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
                cout << q.front().getWord() << endl;
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
    private:
        void controller(palabra p);
        list<declaracion> declaraciones;
        list<encabezado> enc;
        list<namespacing> name;
        list<condicional> con;
        list<arreglo> arr;
        list<asignacion> asig;
        list<funct> funciones;
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
void semantica::mostrarDeclaraciones(){
    cout << endl << "Tipo\tNombre" << endl;
    for(declaracion d : declaraciones){
        cout << d.getType().getWord() << "\t" << d.getVarName() << " variable en bloque "  << d.getID().getBloque() << " Padres: ";
        for(int i : d.getID().getCodeBlock().getParent()){
            cout << i << " "; 
        }
        cout << endl;
    }
    
}
void semantica::mostrarAsignaciones(){
    cout << "Variable Asignacion" << endl;
    for(asignacion d : asig){
        cout << d.getVar().getWord() << d.getVar().getBloque() << " ";
        cout << "= ";
        for(palabra aux : d.getOperadores()){
            cout << aux.getWord() << " ";
        }
        cout << endl;
    }
}
void semantica::analalize(palabra p){
    /*
    //Este analizador parte del hecho de que la sintaxis esta bien puesto que ya paso por un parse
    cout << p.getWord() << " " << p.getBloque() << endl;
    getchar();
    b.insertarPalabra(p);
    if(p != 45 && p != 46 && p != 38 && p != 39 && p != 40 && p != 41){
        cache.push(p);
        cout << cache.size() <<" " << cache.front().getWord() << endl;
    }    
    if(8<=p && p<=12){
        esDeclarado = true;
    }
    if(p == 0){
    }
    if(p == 31 && !esDeclarado){
        //Se trata de una asignación puesto que al recibir un ID y no se detecto una declaracion puede ser una asignación o llamada a una funcion
        esAsignado = true;
    }else if(p == 31){
        smatch s;
        lastVar = p;
        regex r(".+\\[.+\\]");
        string aux = p.getWord();
        esArray = regex_search(aux, s, r);

    }else if(p == 39 && !noParentesis){
        esDeclarado = false;
        esAsignado = false;
        esFuncion = true;
    }
    if(esDeclarado){
            if(p == 39){
                esFuncion = true;
                esDeclarado = false;
                esAsignado = false;
                cout << "Es una funcion" << endl;
            }
            if(p == 46 || p == 45){ //Si es un punto y coma o igual
                if(p == 45){ //En caso de tener un igual en la misma linea de declaracion entonces, activamos la bandera de asignacion
                    esAsignado = true;
                    declaracion d = declaracion::process(cache);
                    cout << d.id.getWord() << " " << d.palabra_clave.getWord() << endl;
                    declaraciones.push_back(d);
                }
                if(p == 46){ //Si es un punto y coma se procesa la cola...
                    lastVar = palabra();
                    if(esArray == false){
                        //Se va a guardar una declaracion
                        declaracion d = declaracion::process(cache);
                        cout << d.id.getWord() << " " <<  d.palabra_clave.getWord();
                        declaraciones.push_back(d);
                    }
                    else{
                        esArray = false;
                    }
                }
                esDeclarado = false; //Como ya recibimos un igual ó un punto y coma entonces la asignación a terminado
            }
        }
    if(esAsignado){
        if(p == 45 && !noParentesis){
            noParentesis = true;
        }
        if(p == 46){
            cout << "Creando asignacion" << endl;
            asignacion as = asignacion::process(cache);
            cout << as.getPalabra().getWord() << endl;
            for(palabra aux : as.getOperadores()){
                cout << aux.getWord() << " ";
            }
            cout << endl;
            this->asig.push_back(as);
            esAsignado = false;

        }
        
    }
    if(esFuncion){
        if(p == 38){
            while(!cache.empty()){
                cache.pop();
            }
            esFuncion = false;
        }
    }
    if(p == 46){
        this->setAllFalse();
    }
    getchar();
    */
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
            cout << "Encontramos un if" << endl;
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
                enc.push_back(en);
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
            cout << "Posible funcion...";
            if(last == 31){
                if((esDeclarado || esAsignado) && last == 31){ //Si la palabra anterior era una variable entonces s y tenemos una bandera de declaracion o asignacion entonces se trata de una funcion
                //llamada de una funcion o una declaracion de una funcion
                //Para una llamada o declaracion de una funcion
                    this->setAllFalse();
                    esFuncion = true;
                }
            }else{
                cout << "No se trata de una funcion...";
            }
            
            break;

        case 40: // Llave derecha
            
            break;

        case 41: //Llave izquierda
            if(esIF){
                condicional con = condicional::process(cache);
                limpiarCola();
                //Aqui vaciamos la cola;
            }else if(esFor){

                //Aqui vaciamoOS la cola
            }else if(esFuncion){
                funct foo = funct::process(cache);
                funciones.push_back(foo);
                limpiarCola();
                //Aqui vaciamos la cola
            }else if(esWhile){
                
                //Aqui vaciamos la cola
                
            }
            setAllFalse();
            break;

        case 45: //Igual
            if(esDeclarado){
                //Se debe guardar la declaracion
                declaracion d = declaracion::process(cache);
                declaraciones.push_back(d);
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
                declaraciones.push_back(dec);
                
                setAllFalse();

            }else if(esFuncion){
                
                funct f = funct::process(cache);
                funciones.push_back(f);
                setAllFalse();
                
            }else if(esAsignado){
                cout << cache.size() << endl;
                asignacion as = asignacion::process(cache);
                asig.push_back(as);
                limpiarCola();
                setAllFalse();

            }else{

            }
            break;
        case 48: // >
            if(cabecera){
                encabezado cab = encabezado::process(cache);
                enc.push_back(cab);
                setAllFalse();
            }
            break;
        case 49: // <
            
            break;
    }
    last = p;
}


