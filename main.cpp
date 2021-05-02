#include <iostream>
#include <queue>
#include "grafo.h"
#include "palabra.hpp"
#include "parser.h"
#include "blanceo.hpp"
using namespace std;
/*
    PROGRAMA DE ANALIZADOR SINTACTICO
    JOSE ARMANDO ARROYO RANGEL 19140288
    RUBEN EMMANUEL GARCIA ORDAZ 19140291

*/
queue<palabra> getPalabras(string s){
    int y;
    return palabra::getPalabras(s);
}
void mostrarPalabras(){
    queue<palabra> a = getPalabras("prueba.cpp");
    while(!a.empty()){
        cout << a.front().getWord() << " " << palabra::translateToken(a.front().getType()) << endl;
        if(a.front().getWord().compare("namespace") == 0){
            cout << a.front() << endl;
        }
        a.pop();
    }
}
int main(){
    int y = 3 > 2;
    parser parser("nodos.csv","relaciones.csv", 100);
    parser.analize("prueba.cpp");

    return 0;
}