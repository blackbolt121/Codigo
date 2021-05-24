#include "allheaders.hpp"
class ciclofor : public estructura
{
public:
    ciclofor() : estructura(){

    }
    static ciclofor process(queue<palabra> &l, tabla &t)
    {
        ciclofor c;
        queue<palabra> p;
        queue<palabra> aux;
        int cont = 0;
        while(!l.empty()){
            palabra p = l.front();

            switch(p){
                case 17: // Palabra for
                    c.setFor(p);
                    break;
                case 46: //Punto y coma
                    if(cont == 0){
                        //Comentario
                        queue<palabra> aux2;
                        int cont2 = 0;
                        while(!aux.empty()){
                            if(aux.front().getWord().compare("(")!=0 && cont2 == 0){
                                aux2.push(aux.front());
                                cont2++;
                            }
                            aux.pop();
                            if(aux.front().getWord().compare(";")==0)
                                break;
                        }
                        queue<palabra> decaux;
                        palabra variable = aux2.front();
                        decaux.push(aux2.front());
                        aux2.pop();
                        decaux.push(aux2.front());
                        aux2.pop();
                        declaracion dec = declaracion::process(decaux);
                        t.insertar(dec);
                        decaux.push(variable);
                        while(!aux2.empty()){
                            decaux.push(aux2.front());
                            aux2.pop();
                        }
                        asignacion as = asignacion::process(decaux);
                        t.buscar(as);
                        c.insertAsignacion(as);
                        c.setDec(dec);
                        cont++;

                    }else if(cont == 1){
                        //Comentario
                        while(!aux.empty()){
                            c.insertCondicion(aux.front());
                            aux.pop();
                        }
                        cont++;
                    }
                    break;
                case 41: //
                    c.setPar(p);
                    aux.push(p);
                    if(cont == 2){
                        //Comentario
                        queue<palabra> aux2;
                        while(!aux.empty()){
                            palabra f = aux.front();
                            aux.pop();
                            if(aux.size() > 0){
                                if(aux.front().getWord().compare("{") != 0){
                                    aux2.push(p);
                                }
                            }
                        }
                        asignacion as = asignacion::process(aux2);
                        c.insertAsignacion(as);

                    }
                    break;
                default: //Guardamos en la pila
                    aux.push(p);
                    break;
            }

            l.pop();
        }

        return c;
    }
    void setPar(palabra &p){
        this->par = p;
    }
    void setFor(palabra &p){
        this->cfor = p;
    }
    void setDec(declaracion &dec){
        this->dec = dec;
    }
    void insertCondicion(palabra &p){
        this->con.push_back(p);
    }
    void insertAsignacion(asignacion &as){
        this->as.push_back(as);
    }
    void insertarDeclaracion(declaracion &dec){
        this->dec = dec;
    }
    void construir(){
        rpn r;
        r.setOperadores(this->con);
        r.construir();
    }

private:
    declaracion dec;
    list<palabra> con;
    list<asignacion> as;
    palabra par, cfor;
};