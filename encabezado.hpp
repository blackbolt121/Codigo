#include "estructura.hpp"
class encabezado : estructura{
    public:
        encabezado() : estructura(){
            include = palabra();
            numeral = palabra();
            library = palabra();

        }
        static encabezado process(queue<palabra> &q){
            encabezado en;
            en.setBloque(0);
            while(!q.empty()){
                palabra p = q.front();
                switch(p){
                    case 0:
                        en.setNumeral(p);
                        break;
                    case 1:
                        en.setInclude(p);
                        break;
                    case 2:
                    case 30:
                    case 31: //En caso de encontrar una "variable", iostream o string lo setea como liberia
                        en.setLibrary(p);
                        break;
                    case 49: //En caso de encontrar > retorna el encabezado
                        return en;
                        break;
                    default:
                       break;
                }
                q.pop();
            }
            return en;
        }
        void setNumeral(palabra p) {(p == 0)? numeral = p : numeral = numeral;}
        void setInclude(palabra p) {(p == 1)? include = p : include = include;}
        void setLibrary(palabra p) {(p == 30 || p == 31 || p == 30)? this->library = p : this->library = library;}
    private:
        palabra numeral, include, library;
};