#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include "palabra.hpp"
using namespace std;
class codeblock {
    public:
        codeblock(){
            this->bloq = 0;
            parent.push_back(0);
        }
        int getBlock() { return bloq;}
        void insertParents(stack<int> vec){
            while(!vec.empty()){
                if(!isChild(vec.top()))
                    parent.push_back(vec.top());
                vec.pop();
            }
        }
        void setBlock(int bloq){ this->bloq = bloq; parent.push_back(bloq);} // Indicamos de que bloque hablamos y agregamos el bloque dentro de los hijos
        friend bool operator == (codeblock b, int n){ return (b.bloq == n) ? true : false; }
        bool isChild(int n){ return ( ( (find(parent.begin(), parent.end(), n) != parent.end()) || n == bloq ) )? true: false; }
        vector<int> getParent() {return parent;}
    private:
        int bloq;
        vector<int> parent;

};