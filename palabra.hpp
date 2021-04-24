#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <ostream>
#include <fstream>
#include <string>
#include <regex>
#include "codeblock.hpp"
#include <map>
using namespace std;
class palabra{
    public:
        enum diccionario{
            ERROR = 999,
            GATITO = 0,
            INCLUDE = 1,
            IOSTREAM = 2,
            USING = 3,
            NAMESPACE = 4,
            STD = 5, 
            COUT = 6,
            ENDL = 7,
            INT = 8,
            DOUBLE = 9,
            FLOAT = 10,
            STRING = 11,
            BOOL =12,
            VOID = 13,
            CLASS = 14,
            PUBLIC = 15,
            PRIVATE = 16,
            FOR = 17,
            WHILE = 18,
            DO = 19,
            STRUCT = 20,
            SHORT = 21,
            UNION = 22,
            SIZEOF = 23,
            IF = 24,
            ELSE_IF = 25,
            ELSE = 26,
            ID_INT = 27,
            ID_DOUBLE = 28,
            ID_FLOAT = 29,
            ID_STRING = 30,
            ID = 31,
            SWITCH = 32,
            CASE = 33,
            TEMPLATE = 34,
            TRY = 35,
            CATCH = 36,
            ASTERISCO = 37,
            PARENTESIS_DERECHO = 38,
            PARENTESIS_IZQUIERDO = 39,
            LLAVE_DERECHA = 40,
            LLAVE_IZQUIERDA = 41,
            S_MAS = 42,
            S_MENOS = 43,
            DIV_DIAG = 44,
            IGUAL = 45,
            PUNTO_Y_COMA = 46,
            COMA = 47,
            MENOR_QUE = 48,
            MAYOR_QUE = 49,
            PIPE = 50,
            AND = 51, 
            BREAK = 52,
            DOS_PUNTOS = 53,
            DIFERENT = 54,
            RETURN = 55,
            IGUAL_IGUAL = 56,
            DIFERENTE_D = 57,
            MENOR_IGUAL = 58,
            MAYOR_IGUAL = 59,
            LOGIC_AND = 60,
            LOGIC_OR = 61,
            PLUS_PLUS = 62,
            MINUS_MINUS = 63,
            LESS_LESS = 64

        };
        static queue<palabra> getPalabras(string arch);
        palabra(){
            this->word = "";
            this->comienzo = 0;
            this->fin = 0;
            this->renglon = 0;
            this->type = -1;
            this->nivel = 0;
        };
        palabra(string palabra) {
            this->word = palabra;
            this->comienzo = 0;
            this->fin = 0;
            this->renglon = 0;
            this->setType();
            this->nivel = 0;
        }
        palabra(string palabra, int comienzo, int fin, int renglon);
        string getWord(){return this->word;}
        void setNivel(int nivel){
            this->nivel = nivel;
        }
        void setBloque(int bloque){
            this->bloque = bloque;
        }
        int getRenglon(){return this->renglon;}
        int getType(){return this->type;}
        int getInicio() {return this->comienzo;}
        int getFin() {return this->fin;}
        friend ostream& operator<<(ostream& out, palabra p);
        string getName() {return name;}
        int getNivel(){return this->nivel;}
        int getBloque(){ return bloque; }
        static string translateToken(const int & i);
        operator int() {return this->type;}
        friend bool operator==(palabra b, palabra a) {
            return (a.getInicio() == b.getInicio() && a.getRenglon() == b.getRenglon() && a.getWord().compare(b.getWord().c_str()) == 0);
        }
        friend bool operator==(palabra p, string s){
            return (p.word.compare(s.c_str()) == 0)? true : false;
        }
        friend bool operator==(palabra p, int n){
            return (p.getType() == n)? true : false;
        }
        friend bool operator<(palabra b, palabra a) {
            if(a.getRenglon() < b.getRenglon())
                if(a.getInicio() < b.getInicio())
                    return true;
            return false;
        }
        friend bool operator>(palabra a, palabra b) {
            if(a.getRenglon() < b.getRenglon())
                if(a.getInicio() > b.getInicio())
                    return true;
            return false;
        }
        operator string() {
            return this->getWord();
        }
        void setCodeBlock(codeblock block){ this->block = block; }
        codeblock getCodeBlock() {return this->block;}
    private:
        int type, comienzo, fin, renglon, nivel, bloque;
        string word, name;
        codeblock block;
        void setType();
        static map<string, int> conv;
        static map<int,string> reverseConv;
        static map<string,int> setTypes();
        static map<int,string> setRevTypes();
        

};
map<string, int> palabra::conv = palabra::setTypes();
map<int, string> palabra::reverseConv = palabra::setRevTypes();

ostream& operator<<(ostream& out, palabra p){
    return out << p.getWord() << "\nTipo: " << p.getType() << "\nComienza: " << p.getInicio() << "\nTermina: " << p.getFin() << "\nRenglon: " << p.getRenglon();
}
queue<palabra> palabra::getPalabras(string arch){
    queue<palabra> retorno;
    fstream archivo(arch.c_str(), ios::in);
    if(archivo.good()){
        if(archivo.is_open()){
            int i = 1, j = 1;
            bool comienzo = true;
            while(!archivo.eof()){
                int a = 1;
                i=1;
                string aux, aux2="";
                bool lastEspecial = false,lc = false;
                getline(archivo, aux, '\n');
                aux+=" ";
                for(char s : aux){
                    if(((65<=s && s<=90) || (97<=s && s<=122) || (48<=s && s<=57) || (s=='.') || s == '_' || s == '"')  && comienzo ==true){
                        if(aux2.length()>0){
                            retorno.push(palabra(aux2, i, i, j));
                            lc = false;
                            comienzo = true;
                            aux2 = "";
                        }
                        a = i;
                        comienzo = false;
                    }
                    if(!lastEspecial){
                        if(s == ' '){
                            if(aux2.length()>0){
                                retorno.push(palabra(aux2, a, i-1, j));
                                aux2="";
                                lc = false;
                                comienzo = true;

                            }
                        
                    }else if((65<=s && s<=90) || (97<=s && s<=122) || (48<=s && s<=57) || (s=='.') || s == '_' || s == '"' || s == '[' || s == ']'){
                        aux2+=s;
                        if(s == '"'){
                            lastEspecial = true;
                        }
                        
                    }else if(s == '(' || s == ')' || s == '{' || s == '}' ||s == '#' || s == ';'  || s == ',' || s == ':'){
                        if(aux2.length()>0){
                                retorno.push(palabra(aux2, a, i-1, j));
                                aux2="";
                                lc = false;
                                comienzo = true;

                        }
                        aux2 = s;
                        retorno.push(palabra(aux2, i, i, j));
                        aux2="";

                    }
                    else if(s == '<' || s == '>' || s == '|'  || s == '&' || s == '=' || s == '+' || s == '-' || s == '/' || s == '*'  || s == '!' ){
                        if((aux2.length()>0 && lc==false)){
                            retorno.push(palabra(aux2, a, i-1, j));
                            aux2="";
                            comienzo = true;
                            
                        }
                        aux2 += s;
                        lc = true;
                    }
                    }else{
                        aux2+=s;
                        if(s=='"'){
                            lastEspecial = false;
                        }
                    }
                    if(s == '\n'){
                        i = 0;
                    }
                    i++;
                }
                
                j++;
            }

        }
    }
    return retorno;
}
palabra::palabra(string palabra, int comienzo, int fin, int renglon){
    this->word = palabra;
    this->comienzo = comienzo;
    this->fin = fin;
    this->renglon = renglon;
    this->setType();
}
void palabra::setType(){
    smatch match;
    regex reservado("^(include|iostream|using|namespace|std|int|void|double|float|string|bool|class|public|private|for|while|do|struct|short|union|sizeof|if|else|switch|case|break|template|try|catch|cout|endl|return)$");
    regex estring("(^\".*\"$)");
    regex integer("(^\\d+$)");
    regex flotant("(^\\d+\\.\\d+$)");
    regex id("((^[_$a-zA-Z]+[_$a-zA-Z0-9]*$)|(^[_$a-zA-Z]+[_$a-zA-Z0-9]*(\\[([_$a-zA-Z]+[_$a-zA-Z0-9]*|[0-9]+)\\])+$))");
    regex op("^(\\+|\\-|\\*|\\/|\\(|\\)|\\{|\\}|\\>|\\<|\\=|\\||\\&|;|,|:|!|<=|>=|\\&\\&|\\|\\||!=|==|#)$");
    if(regex_search(word, match, reservado)||regex_search(word, match, op)){
        try{
            this->type = conv[word];
            if(word.compare("namespace") == 0){
                this->type = 4;
            }
        }catch(std::out_of_range out){
            this->type = 999;
        }

    }else if(regex_search(word, match, id)){
        this->type = diccionario::ID; 
    }else if(regex_search(word, match, estring)){
        this->type = diccionario::ID_STRING;
    }else if(regex_search(word, match, integer)){
        this->type = diccionario::ID_INT;
    }else if(regex_search(word, match, flotant)){
        this->type = diccionario::ID_DOUBLE;
    }
    else{
        if(word.compare("&&")==0 || word.compare("!=")==0 || word.compare("<<")==0 || word.compare("==")==0 || word.compare("||")==0 || word.compare("<=")==0 || word.compare(">=")==0 || word.compare("++")==0 || word.compare("--")==0){
            this->type = conv[word];
        }else{
            this->type = 999;
        }
        
    }
}
map<string, int> palabra::setTypes(){
    map<string, int> convert;
    convert.insert(pair<string, int>("#", diccionario::GATITO));
    convert.insert(pair<string, int>("include", diccionario::INCLUDE));
    convert.insert(pair<string, int>("iostream", diccionario::IOSTREAM));
    convert.insert(pair<string, int>("using", diccionario::USING));
    convert.insert(pair<string, int>("namepace", diccionario::NAMESPACE));
    convert.insert(pair<string, int>("std", diccionario::STD));
    convert.insert(pair<string, int>("cout", diccionario::COUT));
    convert.insert(pair<string, int>("endl", diccionario::ENDL));
    convert.insert(pair<string, int>("return", diccionario::RETURN));
    convert.insert(pair<string, int>("int", diccionario::INT));
    convert.insert(pair<string, int>("bool", diccionario::BOOL));
    convert.insert(pair<string, int>("double",diccionario::DOUBLE));
    convert.insert(pair<string, int>("float",diccionario::FLOAT));
    convert.insert(pair<string, int>("string",diccionario::STRING));
    convert.insert(pair<string, int>("void",diccionario::VOID));
    convert.insert(pair<string, int>("class",diccionario::CLASS));
    convert.insert(pair<string, int>("public",diccionario::PUBLIC));
    convert.insert(pair<string, int>("private",diccionario::PRIVATE));
    convert.insert(pair<string, int>("for",diccionario::FOR));
    convert.insert(pair<string, int>("while",diccionario::WHILE));
    convert.insert(pair<string, int>("do",diccionario::DO));
    convert.insert(pair<string, int>("struct",diccionario::STRUCT));
    convert.insert(pair<string, int>("short",diccionario::SHORT));
    convert.insert(pair<string, int>("union",diccionario::UNION));
    convert.insert(pair<string, int>("sizeof",diccionario::SIZEOF));
    convert.insert(pair<string, int>("switch",diccionario::SWITCH));
    convert.insert(pair<string, int>("break", diccionario::BREAK));
    convert.insert(pair<string, int>("case",diccionario::CASE));
    convert.insert(pair<string, int>("if",diccionario::IF));
    convert.insert(pair<string, int>("else",diccionario::ELSE));
    convert.insert(pair<string, int>("template",diccionario::TEMPLATE));
    convert.insert(pair<string, int>("try", diccionario::TRY));
    convert.insert(pair<string, int>("catch", diccionario::CATCH));
    convert.insert(pair<string, int>("(", diccionario::PARENTESIS_IZQUIERDO));
    convert.insert(pair<string, int>(")", diccionario::PARENTESIS_DERECHO));
    convert.insert(pair<string, int>("=", diccionario::IGUAL));
    convert.insert(pair<string, int>("*", diccionario::ASTERISCO));
    convert.insert(pair<string, int>("/", diccionario::DIV_DIAG));
    convert.insert(pair<string, int>("+", diccionario::S_MAS));
    convert.insert(pair<string, int>("-", diccionario::S_MENOS));
    convert.insert(pair<string, int>("{", diccionario::LLAVE_IZQUIERDA));
    convert.insert(pair<string, int>("}", diccionario::LLAVE_DERECHA));
    convert.insert(pair<string, int>(";", diccionario::PUNTO_Y_COMA));
    convert.insert(pair<string, int>(",", diccionario::COMA));
    convert.insert(pair<string, int>("<", diccionario::MENOR_QUE));
    convert.insert(pair<string, int>(">", diccionario::MAYOR_QUE));
    convert.insert(pair<string, int>("|", diccionario::PIPE));
    convert.insert(pair<string, int>("&", diccionario::AND));
    convert.insert(pair<string, int>(":", diccionario::DOS_PUNTOS));
    convert.insert(pair<string, int>("!", diccionario::DIFERENT));
    convert.insert(pair<string, int>("!=", diccionario::DIFERENTE_D));
    convert.insert(pair<string, int>("<=", diccionario::MENOR_IGUAL));
    convert.insert(pair<string, int>(">=", diccionario::MAYOR_IGUAL));
    convert.insert(pair<string, int>("==", diccionario::IGUAL_IGUAL));
    convert.insert(pair<string, int>("&&", diccionario::LOGIC_AND));
    convert.insert(pair<string, int>("||", diccionario::LOGIC_OR));
    convert.insert(pair<string, int>("!=", diccionario::DIFERENTE_D));
    convert.insert(pair<string, int>("++", diccionario::PLUS_PLUS));
    convert.insert(pair<string, int>("--", diccionario::MINUS_MINUS));
    convert.insert(pair<string, int>("<<", diccionario::LESS_LESS));
    return convert;
}
map<int,string> palabra::setRevTypes(){
    map<int,string> aux;
    aux[0] = "#";
    aux[1] = "include";
    aux[2] = "iostream";
    aux[3] = "using";
    aux[4] = "namespace";
    aux[5] = "std";
    aux[6] = "cout";
    aux[7] = "endl";
    aux[8] = "int";
    aux[9] = "double";
    aux[10] = "float";
    aux[11] = "string";
    aux[12] = "bool";
    aux[13] = "void";
    aux[14] = "class";
    aux[15] = "public";
    aux[16] = "private";
    aux[17] = "for";
    aux[18] = "while";
    aux[19] = "do";
    aux[20] = "struct";
    aux[21] = "short";
    aux[22] = "union";
    aux[23] = "sizeof";
    aux[24] = "if";
    aux[25] = "else_if";
    aux[26] = "else";
    aux[27] = "integer value";
    aux[28] = "double value";
    aux[29] = "float value";
    aux[30] = "string value";
    aux[31] = "var name";
    aux[32] = "switch";
    aux[33] = "case";
    aux[34] = "template";
    aux[35] = "try";
    aux[36] = "catch";
    aux[37] = "*";
    aux[38] = ")";
    aux[39] = "(";
    aux[40] = "}";
    aux[41] = "{";
    aux[42] = "+";
    aux[43] = "-";
    aux[44] = "/";
    aux[45] = "=";
    aux[46] = ";";
    aux[47] = ",";
    aux[48] = "<";
    aux[49] = ">";
    aux[50] = "|";
    aux[51] = "&";
    aux[52] = "break";
    aux[53] = ":";
    aux[54] = "!";
    aux[55] = "return";
    aux[56] = "==";
    aux[57] = "!=";
    aux[58] = "<=";
    aux[59] = ">=";
    aux[60] = "&&";
    aux[61] = "||";
    aux[62] = "++";
    aux[63] = "--";
    aux[64] = "<<";
    return aux;  
}
string palabra::translateToken(const int &i){
    try{
        return palabra::reverseConv[i];
    }catch(std::exception e){
        return "Token desconocido";
    }
    
}