#pragma once
#include <iostream>
#include <fstream>
#include "grafo.h"
#include "queue"
#include "nodo.h"
#include "palabra.hpp"
using namespace std;
class automata{
    public:
        automata(){
            this->inError = false;
        };
        grafo<int, int> &getAutom(){return this->au;};
        void loadAutomata(string nodos, string relacion);
        void move(int value);
        void isFinal();
        nodo<int,int> getHead(){return this->head;};
        void setHead(int value = 100){
            headValue = 100;
            this->head = au.getNodo(value);
            au.setHead(100);
        };
        void reset();
        nodo<int,int> getCurrentState(){
            return this->au.getActualState();
        }
        bool getStatus() { return (this->au.getActualState() == nodo<int,int>::error)? false : true;}
        bool getInFinal() { return (this->au.getActualState().getFinal()); }
    protected:
        string idAutomata;
        grafo<int, int> au;
        int headValue;
        nodo<int, int> head;
        bool inError;
};

void automata::loadAutomata(string nodos, string relacion){
    fstream arch(nodos, ios::in);
    fstream arch2(relacion, ios::in);
    if(arch.good()){  
        if(arch.is_open()){
            int cont = 1;
            string save;
            string id=""; 
            int key, value;     
            bool fin, inicio;
            while(!arch.eof()){ //Carga de automata
                if(cont % 5 != 0){
                    getline(arch, save, ',');
                    int select = cont % 5;
  
                    switch(select){
                        case 1:
                            key = atoi(save.c_str());
                            break;
                        case 2:
                            id = save;
                            break;
                        case 3:
                            value = atoi(save.c_str());
                            break;
                        case 4:
                            inicio = atoi(save.c_str());
                            break;
                    }
                }else{
                    getline(arch, save, '\n');
                    fin = atoi(save.c_str());
                    this->au.load(key, id, value, fin, inicio);
                    key = value = 0;
                    id = "";
                    inicio = false;
                    fin = false;
                }
                cont++;  
            }
        }
    }
    if(arch2.good()){
        if(arch2.is_open()){
            int contador = 1, dir1, dir2, key;
            while(!arch2.eof()){
                string save;
                switch(contador%3){
                    case 1:
                        getline(arch2,save, ',');
                        dir1 = atoi(save.c_str());
                        break;
                    case 2:
                        getline(arch2,save, ',');
                        dir2 = atoi(save.c_str());
                        break;
                    case 0:
                        getline(arch2, save, '\n');
                        key = atoi(save.c_str());
                        au.link(dir1, dir2, key);
                        break;
                }
                contador++;
            }
        }
    }else{
        cout << "No se abrio " << endl;
    }
    arch2.close();

}

void automata::move (int value){
    au.move(value);
    if(this->getCurrentState() == nodo<int,int>::error)
        inError = true;
    
}
void automata::reset(){
    this->au.setHead(head.getValue());
}

