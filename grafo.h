#pragma once
#include <iostream>
#include <map>
#include "nodo.h"

template<class T, class S>
class grafo
{
    public:
        grafo()
        {
            this->head = nodo<T, S>::error;
            this->actualState = nodo<T, S>::error;
        }
        void link(T id1, T id2, T key);
        void load(T key, string id, int value, bool inicial, bool final);
        void move(T key);
        void setHead(T key);
        nodo<T, S> getNodo(T key);
        nodo<T, S> getHead() 
        { 
            return this->head; 
        }
        nodo<T, S> getActualState() { return this->actualState;}
    private:
        T lastKey;
        nodo<T, S> previousNode;
        nodo<T, S> actualState;
        nodo<T, S> head;
        map<T, nodo<T,S>> nodos;


};
template <class T, class S>
void grafo<T, S>::load(T key, string id, int value, bool inicial, bool final){
    nodo<T, S> aux(id, value, inicial, final);
    aux.setKeyOnGraph(key);
    this->nodos[key] = aux;
}

template <class T, class S>
void grafo<T, S>::move(T key){
    if(!(this->actualState.getNodo(key) == nodo<T, S>::error)){
        this->lastKey = key;
        this->previousNode = actualState;
        this->actualState = nodos.at(actualState.getNodo(key).getGraphKey());
    }
    else
    {
        this->actualState = nodo<T, S>::error;
    }
    
}
template <class T, class S>
void grafo<T, S>::link(T id1, T id2, T key){
    if(nodos.find(id1)!= nodos.end())
    {
        if(nodos.find(id2) != nodos.end())
        {
            nodo<T, S> &aux2 = nodos.at(id2);
            nodo<T, S> &aux = nodos.at(id1);
            aux.insert(key, aux2);
            nodos[id1] = aux;
            if(aux == this->actualState){
                    this->actualState = aux;
                }
                if(aux == this->head){
                    this->head = aux;
                }
            for(auto &aux3 : nodos)
            {
                aux3.second.update(id1, aux);
                aux3.second.update(id2, aux2);
            }
            
        }
    }
}
template <class T, class S>
nodo<T, S> grafo<T, S>::getNodo(T key){
    try
    {
        return this->nodos.at(key);
    
    }catch(std::out_of_range out)
    {
        return nodo<T, S>::error;
    }
}
template <class T, class S>
void grafo<T, S>::setHead(T key){
    try
    {
        this->head = this->nodos.at(key);
        this->actualState = nodos.at(key);
    }
    catch(std::out_of_range out)
    {
        this->head = nodo<T, S>::error;
        this->actualState = nodo<T, S>::error;
    }
}
