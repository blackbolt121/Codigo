#pragma once
#include <iostream>
#include <stack>
#include <list>
#include "rpn.hpp"
#include "palabra.hpp"
using namespace std;
class rpn{
    public:
        rpn(){}
        void setOperadores(list<palabra> &op) { operadores = op; };
        static bool hierarchy(palabra a, palabra b);
        static bool isOperator(palabra p);
        static bool isVarn(palabra p);
        static int getHierarchy(palabra p);
        static bool esAritmetico(palabra p);
        static bool esLogico(palabra p);
        void construir();
        void notacionPolacaInversa();
        list<palabra>& getPolish() {return this->polish; }
    private:
        list<palabra> operadores;
        list<palabra> polish;
        
};

// 
int rpn::getHierarchy(palabra p){
    switch(p){
        case 37: //   * 
        case 44: //   / 
            return 6;
            break;
        case 42: // +
        case 43: // -
            return 5;
            break;
        case 54: // !
            return 4;
            break;
        case 51: // &
        case 60: // &&
              return 1;
              break;
        case 50: // |
        case 61: // ||
            return 2;
            break;
        case 48: // >
        case 49: // <
        case 56: // ==
        case 57: // !=
        case 58: // >=
        case 59: // <=
            return 3;
            break;
        case 38: // )
        case 39: // (
            return 0;
        default:
            throw -1;
            return -1;
            break;
    }
}

bool rpn::isOperator(palabra p){
    return ((p == 37) ||(42<=p && p<= 44) || (48<=p && p<=51) || (56<=p && p<=60));
}
bool rpn::hierarchy(palabra a, palabra b){
    if(!rpn::isOperator(a) && !rpn::isOperator(b)) throw 1;
    return (rpn::getHierarchy(a) <= rpn::getHierarchy(b))? true : false;
}
bool rpn::isVarn(palabra p){
    return (27<=p && p<=31);
}
void rpn::construir(){
    if(operadores.size() > 0){
        stack<palabra> op;
        for(palabra &p : operadores){
            if(rpn::isVarn(p)){
                polish.push_back(p);
            }
            else if(rpn::isOperator(p)){
                if(op.empty()){
                    op.push(p);
                }else{
                    palabra aux = op.top();
                    if(rpn::hierarchy(p, aux)) //Aqui verificamos que p tenga menor jerarquia con el operador que se encuentra en la pila
                    {
                        polish.push_back(aux);
                        op.pop();
                        while(!op.empty()){
                            aux = op.top();
                            if(rpn::hierarchy(p, aux)){
                                if(p != 39)
                                    polish.push_back(aux);
                                op.pop();
                            }else{
                                break;
                            }
                            
                        }
                        getchar();
                        op.push(p);
                    }
                    else
                    {
                        op.push(p);
                    }
                }

            }else if(p == 39) { // Parentesis (
                op.push(p);
            }else if (p == 38) { // Parentesis )
                while(!op.empty()){
                    if(op.top() == 39){
                        op.pop();
                        break;
                    }else{
                        palabra &aux = op.top();
                        if(aux != 39)
                            polish.push_back(aux);
                        op.pop();
                    }
                }
            }
        }
        if(!op.empty()){
            while(!op.empty()){
                palabra &aux = op.top();
                polish.push_back(aux);
                op.pop();
            }
        }
        cout << endl;
    }
}
bool rpn::esAritmetico(palabra p){
    list<string> artimetic = {"+","-","*","/"};
    return (find(artimetic.begin(), artimetic.end(), p.getWord()) != artimetic.end());
}
bool rpn::esLogico(palabra p){
    list<string> logic = {">","<","<=",">=","&","|","&&","||","==","!="};
    return (find(logic.begin(), logic.end(), p.getWord()) != logic.end());
}
void rpn::notacionPolacaInversa(){
    stack<palabra> st;
    for(palabra p : polish){
        if(isVarn(p)){
            st.push(p);
        }else if(isOperator(p)){
            if(st.size() >= 2){
                if(esAritmetico(p)){
                    palabra a = st.top();
                    st.pop();
                    palabra b = st.top();
                    st.pop();
                    cout << p.getWord() << " " << a.getWord() << " " << b.getWord() << " ax" << endl;
                    st.push(palabra("ax"));
                }else if(rpn::esLogico(p)){
                    list<string> cmp = {">","<","<="};
                    map<string,string> jmp = {{">","jng"},{"<","jnl"},{">=","jnge"},{"<=","jnle"},{"==","jne"},{"!=","je"}};
                    cout << jmp[p.getWord()] << " " << st.top().getWord() << " ";
                    st.pop();
                    cout << st.top().getWord() << " etn" << endl;
                    st.pop();
                }
                
            }else{
                
            }
        }
    }
}