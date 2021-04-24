#pragma once
#include <ostream>
#include <iostream>
#include <list>
using namespace std;
template <class T, class S>
class nodo{
    public:
        nodo(){
            id = "";
        };
        nodo(const string& id){
            this->id = id;
        }
        nodo(string id, const int& value, bool final, bool inicial){
            this->id = id;
            this->value = value;
            this->final = final;
            this->inicial = inicial;
        }
        bool isEmpty();
        static nodo<T, S> error;
        static nodo<T, S> finalNode;
        nodo<T, S>& getNodo(T key);
        void insert(const T &key,const nodo<T, S> &node);
        void setID(const string id) {this->id = id;}
        void setValue(int value) {this->value = value;}
        void setFinal(bool final) {this->final = final;}
        void setInicial(bool inicial){this->inicial = inicial;}
        void update(const T& key, const nodo<T, S>& node);
        string getID(){return this->id;}
        int getValue(){return this->value;}
        bool getFinal(){return this->final;}
        bool getInicial(){return this->inicial;}
        void setKeyOnGraph(T key){this->key = key;};
        T getGraphKey() {return key;}
        list<T> getPosibleSaltos(){
            return this->posiblesSaltos;
        }
    private:
        T key;
        string id;//Aqui asignamos el identificador del nodo el cual debe ser único
        int value; //En este caso podemos guardar una expresión regular en un string*
        map<T, nodo<T, S>> mapa; //Guardamos todos los nodos adyacentes en un map
        bool final, inicial; //Guardamos si es un estado final o inicial
        list<T> posiblesSaltos;
        
};
template <class T, class S>
void nodo<T, S>::update(const T&key, const nodo<T, S>& node){
    if(mapa.find(key) != mapa.end()){
        mapa[key] = node;
    }
}
template <class T, class S>
void nodo<T, S>::insert(const T& key, const nodo<T, S>& node){
    if(mapa.find(key) == mapa.end()){
        mapa.insert(pair<T, nodo<T, S>>(key, node));
        posiblesSaltos.push_back(key);
    }
}
template <class T, class S>
bool nodo<T, S>::isEmpty(){
    return mapa.empty();
}
template <class T, class S>
bool operator == (nodo<T, S> a, nodo<T, S> b)
{
    return (a.getID().compare(b.getID().c_str())==0)? true : false;   
}
template <class T, class S>
nodo<T, S> nodo<T, S>::error = nodo<T, S>("error", 999, true, true);
template <class T, class S>
nodo<T, S>& nodo<T, S>::getNodo(T key)
{
    try{
        return mapa.at(key);
    }catch(std::out_of_range out){
        return nodo<T, S>::error;
    }
}
template <class T, class S>
ostream& operator << (ostream& out, nodo<T, S> aux)
{
    return out << "ID: " << aux.getID() << " Valor: " << aux.getValue() << " Estado Incial: " << aux.getInicial() << " Estado Final: " << aux.getFinal(); 
}
template <class T, class S>
bool operator < (nodo<T, S> a, nodo<T, S>b)
{
    return (a.getID()<b.getID())? true : false;
}
template <class T, class S>
bool operator > (nodo<T, S> a, nodo<T, S>b)
{
    return (a.getID()>b.getID())? true : false;
}
