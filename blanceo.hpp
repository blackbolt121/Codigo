#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include "palabra.hpp"
#include "codeblock.hpp"
using namespace std;
class balanceo{
    public:
        balanceo(){
            nivel = 0;
            bloque = 0;
            bactual = 0;
            temp = true;
            codeblock c;
            bloc.push_back(c);
            cs.push(c);

        }
        void insertarPalabra(palabra &p);
        bool isBalanceado(){
            return (p1.empty() && p2.empty() && error.size() == 0);
        }
        queue<palabra> returnError(){
            return error;
        }
    private:
        list<pair<palabra,palabra>> parentesis, llaves;
        stack<palabra> p1,p2,p3;
        stack<codeblock> cs;
        queue<palabra> error;
        int nivel, bloque, bactual;
        stack<int> b;
        list<codeblock> bloc;
        bool temp;
};
void balanceo::insertarPalabra(palabra &p){
    //Indicamos a que bloque de codigo pertenece la palabra (bloque es un conjunto de palabras que se encuentran entre una llaves)
    switch(p){
        case 39:
            p1.push(p);
            temp = false;
            p.setBloque(bactual);
            p.setCodeBlock(cs.top());
            break;
        case 38:
            if(!p1.empty()){
                p.setBloque(bactual);
                p.setCodeBlock(cs.top());
                parentesis.push_front(pair<palabra,palabra>(p1.top(), p));
                p1.pop();
                temp = false;
            }else{
                error.push(p);
            }
            break;
        case 41:
            bloque++;
            nivel++;
            p2.push(p);
            b.push(bactual); //Guardamos el bloque anterior para cuando se cierre el parentesis;
            bactual = bloque;
            if(p == 41){
                codeblock c;
                cout << b.size() << endl;
                c.insertParents(b);
                c.setBlock((bactual));
                bloc.push_back(c);
                cs.push(c);
            }
            p.setBloque(bactual);
            p.setCodeBlock(cs.top());
            temp = false;
            break;
        case 40:
            if(!p2.empty())
            {
                llaves.push_front(pair<palabra,palabra>(p2.top(), p));
                p2.pop();
                nivel--;
                p.setBloque(bactual);
                p.setCodeBlock(cs.top());
                cs.pop();
                if(!b.empty()){
                    bactual = b.top();
                    b.pop();
                }else{
                    bactual = 0;
                }
                temp = true;
            }
            else
            {
                error.push(p);
            }
            break;
        default:
            p.setBloque(bactual);
            p.setCodeBlock(cs.top());
            break;
    }
    p.setNivel(this->nivel);
}
