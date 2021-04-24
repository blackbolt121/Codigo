#include "estructura.hpp"
class namespacing : estructura{
    public:
        namespacing() : estructura() {
            use = name = std = palabra();
        }
        static namespacing process(queue<palabra>& q){
            namespacing retorno;
            if(q.size() == 3){
                while(!q.empty()){
                    palabra p = q.front();
                    switch(p){
                        case 3:
                            retorno.palabra_clave = p;
                            retorno.setUsing(p);
                            break;
                        case 4:
                            retorno.setName(p);
                            break;
                        case 5:
                            retorno.setSTD(p);
                            break;
                        default:
                            //Un comentario
                            break;
                    }
                }
            }
            return retorno;
        }
        void setUsing(palabra p) {(p == 3)? this->use = p : this->use = use;;}
        void setName(palabra p) {(p == 4)? this->name = p : this->name = name;}
        void setSTD(palabra p) {(p == 5)? this->std = p : this->std = std;}
    private:
        palabra use, name, std;
};