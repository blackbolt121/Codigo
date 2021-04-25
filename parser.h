#pragma once
#include <sstream>
#include "semantica.hpp"
#include "automata.h"
#include "blanceo.hpp"
class parser : public automata{

    public:
        parser(const string& nodos, const string& relaciones, const int& head) : automata(){
            this->fileNodes = nodos;
            this->fileRelations = relaciones;
            this->loadAutomata(nodos, relaciones);
            this->setHead(head);
            this->hasError = false;
        }
        void move(palabra value);
        void analize(const string& rute);
    private:
        static string imprimirError(nodo<int, int> aux, palabra value);
        void error(nodo<int,int> aux, palabra value);
        palabra lastWord;
        string fileNodes, fileRelations;
        bool hasError;
        list<string> errors;
        semantica s;
        balanceo b;
};
void parser::move(palabra value){
    nodo<int,int> aux = this->au.getActualState();
    if(lastWord.getRenglon() == value.getRenglon()){
        //Buscamos controlar que las palabras que se vayan analizando sean linea por linea
        this->au.move(value);
        if(this->getCurrentState() == nodo<int,int>::error){
            /*
                Imprime que esta en un estado de error, puesto que se esperaba otra palabra
                y establece el estado en uno valido y luego se devuelve al estado inicial-final del automata diseñado
            */
            error(aux, lastWord);
            inError = false;
        }
        this->lastWord = value;
    }else{
        //De no estar en el mismo renglon, entonces se verifica que el automata se encuentra en el estado final
        if(this->getInFinal()){
            //De estarlo se cambia last word y se mueve de estado el automata
            this->lastWord = value;
            au.move(value);
            if(this->getCurrentState() == nodo<int,int>::error)
                inError = true;
            if(inError){
                error(aux, lastWord);
                lastWord = value;
                inError = false;
            }
        }else{
            /*
            En caso de que la siguiente palabra no este en el siguiente renglon de la palabra anterior y no este
            en un estado final, imprimira un error; luego devolvera al automata al estado final y aplicara recursividad
            para evaluar la palabra actual  
            */
            error(aux, lastWord);
            this->lastWord = value;
            this->move(value);
        }
    }
}
void parser::error(nodo<int, int> auxiliar, palabra value){
    this->hasError = true;
    this->errors.push_back(parser::imprimirError(auxiliar, value));
    this->setHead(headValue);
}
string parser::imprimirError(nodo<int, int> auxiliar, palabra value){
    stringstream s;
    if(value.getType() == 999)
        cout << "Error lexico en palabra" << value.getWord() << endl;
    cout << auxiliar.getID() << endl;
    s << "error en (" << value.getRenglon() << ":" << value.getFin() << ")\n";
    s << "Se esperaba cualquiera de los siguientes: \n";
    list<int> aux = auxiliar.getPosibleSaltos();
    for(int v : aux){
        s << "\t" << palabra::translateToken(v) << " (type:" << v << ")\n";
    }
    return s.str();
}
void parser::analize(const string& rute){
    queue<palabra> cola = palabra::getPalabras(rute); //Guardamos todas las palabras del archivo en una cola y clasifican su tipo
    queue<palabra> cola2;
    while(!(cola.empty() || this->hasError)){ //Ley de Morgan a condicion !cola.empty() && this->hasError
        palabra &aux = cola.front();
        this->move(aux);
        b.insertarPalabra(aux);
        cola2.push(aux);
        cola.pop();
    }
    //En caso de haber error de balanceo de parentesis o llaves ó un error de sintaxis entonces 
    if(hasError || b.isBalanceado() == false){
        if(!b.isBalanceado()){
            cout << "Error de balanceo en parentesis: ";
        }
        if(hasError){
            for(string s : errors){
                cout << s << endl;
            }
        }
    }else{
        cola = cola2;
        while(!cola.empty()){
            s.analalize(cola.front());
            cola.pop();
        }
        s.mostrarDeclaraciones();
        s.mostrarAsignaciones();
    }
}