#include "allheaders.hpp"
using namespace std;
class tabla {
    public:
        /*

        */
        void insertar(declaracion d){
            fila f(d);
            cout << f << endl;
            if(contenido.find(d.getVarName()) == contenido.end()){
                if(d.getType().getType() != 12)
                    contenido.insert(pair<string, fila>(f.getIdentificador(), f));
            }
            else{
                fila aux = contenido[f.getIdentificador()];
                if(aux.getType2() == 0){
                    cout << aux.getIdentificador() << " ya fue definido como variable " << endl;
                    
                }else{
                    cout << aux.getIdentificador() << " ya fue definido como funcion " << endl;
                }
            }
        }
        void insertar(funct f){
            fila d;
            d.setFilaFuncion(f);
            if(contenido.find(d.getIdentificador()) == contenido.end())
                contenido.insert(pair<string, fila>(d.getIdentificador(), d));
            else{
                fila aux = contenido[d.getIdentificador()];
                if(aux.getType2() == 0){
                    cout << aux.getIdentificador() << " ya fue definido como variable " << endl;
                    errors.push_back(0);
                }else{
                    cout << aux.getIdentificador() << " ya fue definido como funcion " << endl;
                }
            }
        }
        void buscar(asignacion as)
        {
            /*
                LINEAS DE CODIGO NECESARIAS PARA VERIFICAR QUE LA VARIABLE A LA QUE SE ESTE HACIENDO REFERENCIA EXISTA
            */
            if(isInBars(as)){
                cout << "Si se puede asignar..." << endl;
                
            }else{
                cout << "no se puede asignar..." << endl;
            }

        }
        void buscar(condicional con){

        }
        bool isInBars(string varname){ //Solo pregunta si la variable esta en la tabla de simbolos
            if (contenido.find(varname)!=contenido.end()) { //Verifica que este en la tabla de simbolos
                if(contenido[varname].getType2() == 0){ //Verfica que lo que esta en la tabla sea una variable
                    return true;
                }
            }
            return false;   
        }
        bool isInBars(variable as){
            string varname = as.getVarname();
            cout << varname << endl;
            if (contenido.find(varname)!=contenido.end()) { //Verifica que este en la tabla de simbolos
                if(contenido[varname].getType2() == 0){ //Verfica que lo que esta en la tabla sea una variable
                    if(as.getVariable().getCodeBlock().isChild(contenido[varname].getBloque())){ //Verifica que este en el escope
                        if(contenido[varname].getDim() == 1){
                            return true;
                        }else{
                            if( contenido[varname].getDim() > as.getDim() && as.getDim() >= 0 ){
                                return true;
                            }else{
                                cout << "Direccion no valida..." << endl;
                            }
                        }
                        
                    }
                }
            }else{
                cout << "Variable no en tabla" << endl;
            }
            return false;
        };
        bool isInBars(asignacion as){
            string varname = as.getVarName();
            cout << varname << endl;
            if (contenido.find(varname)!=contenido.end()) { //Verifica que este en la tabla de simbolos
                if(contenido[varname].getType2() == 0){ //Verfica que lo que esta en la tabla sea una variable
                    if(as.getVar().getCodeBlock().isChild(contenido[varname].getBloque())){ //Verifica que este en el escope
                        if(contenido[varname].getDim() == 1){
                            return true;
                        }else{
                            if( contenido[varname].getDim() > as.getSize() && as.getSize() >= 0 ){
                                return true;
                            }else{
                                cout << "Direccion no valida..." << endl;
                            }
                        }
                        
                    }
                }
            }else{
                cout << "Variable no en tabla" << endl;
            }
            return false;
        }
        bool verificarCoherencia(list<variable> vars, string ref){
            int type = contenido[ref].getType().getType();
            bool evaluation = true;
            auto validar = [type](variable var) -> bool {
                switch(type){
                    case 11:
                        if(var.getType() == 11){
                            return true;
                        }else{
                            return false;
                        }
                        break;
                    case 13: //No puede asignarse un valor void
                        return false;
                        break;
                    //En caso de que sean numeros
                    case 8:
                    case 9:
                    case 10:
                    case 12:
                        if( var.getType() == 8 || var.getType() == 9 || var.getType() == 10 || var.getType() == 12 ){
                            return true;
                        }else{
                            return false;
                        }
                        break;
                    default:
                        return false;
                        break;
                }
            };
            for(variable v : vars){
                evaluation = evaluation && validar(v);
                if(!isInBars(v)){
                    evaluation = evaluation && false;
                    cout << "Operando no valido...";
                }
            }
            return evaluation;
        }
    private:
        map<string, fila> contenido;
        list<int> errors;
};