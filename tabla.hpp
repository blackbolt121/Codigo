#include "allheaders.hpp"
using namespace std;
class tabla
{
public:
    /*

        */
    void insertar(declaracion &d)
    {
        fila f(d);
        if (contenido.find(d.getVarName()) == contenido.end())
        {
            if (d.getType().getType() != 12)
                contenido.insert(pair<string, fila>(f.getIdentificador(), f));
        }
        else
        {
            fila aux = contenido[f.getIdentificador()];
            if (aux.getType2() == 0)
            {
                cout << aux.getIdentificador() << " ya fue definido como variable " << endl;
            }
            else
            {
                cout << aux.getIdentificador() << " ya fue definido como funcion " << endl;
            }
        }
    }
    void insertar(funct &f)
    {
        fila d;
        d.setFilaFuncion(f);
        if (contenido.find(d.getIdentificador()) == contenido.end())
            contenido.insert(pair<string, fila>(d.getIdentificador(), d));
        else
        {
            fila &aux = contenido[d.getIdentificador()];
            if (aux.getType2() == 0)
            {
                cout << aux.getIdentificador() << " ya fue definido como variable " << endl;
                errors.push_back(0);
            }
            else
            {
                if (f.getType() == -1)
                {
                    if (f.getArguments().size() == contenido[d.getIdentificador()].getFunct()->getNArg())
                    {
                        cout << aux.getFunct()->getArguments().size() << " " << f.getArguments().size() << endl;
                        aux.insertarReferencia(f.getPalabra().getRenglon()); //Verificamos que tengan la misma cantidad de argumentos
                    }
                    else
                    {
                        cout << "Faltan argumentos..." << endl;
                    }
                }
                else
                {
                    cout << aux.getIdentificador() << " ya fue definido como funcion " << endl;
                }
            }
        }
    }
    void buscar(asignacion as)
    {
        /*
                LINEAS DE CODIGO NECESARIAS PARA VERIFICAR QUE LA VARIABLE A LA QUE SE ESTE HACIENDO REFERENCIA EXISTA
            */
        if (isInBars(as))
        { //Si la asignacion esta dentro de las variables, entonces verificamos la coherencia de la expresion
            cout << "Construyendo" << endl;
            bool areDeclared = true;
            areDeclared = true && verificarCoherencia(as);
            if (areDeclared)
            {
                as.construir();
            }
            else
            {
                cout << "La asignacion no es valida " << endl;
            }
        }
        else
        {
            cout << "Variable por asignar sin declarar previamente... ";
        }
    }
    void buscar(condicional con)
    {
        if (verificarCoherencia(con))
        {
            
        }
    }
    bool isInBars(string varname)
    { //Solo pregunta si la variable esta en la tabla de simbolos con su identificador
        if (contenido.find(varname) != contenido.end())
        { //Verifica que este en la tabla de simbolos
            if (contenido[varname].getType2() == 0)
            { //Verfica que lo que esta en la tabla sea una variable
                return true;
            }
        }
        return false;
    }
    bool isInBars(variable as)
    { //Verificamos si una variable esta dentro de la tabla de simbolos
        string varname = as.getVarname();
        if (contenido.find(varname) != contenido.end())
        { //Verifica que este en la tabla de simbolos
            if (contenido[varname].getType2() == 0)
            { //Verfica que lo que esta en la tabla sea una variable
                if (as.getVariable().getCodeBlock().isChild(contenido[varname].getBloque()))
                { //Verifica que este en el escope
                    if (!contenido[varname].isArray())
                    {
                        if (!as.isArray())
                        {
                            contenido[varname].setEstado(1);
                            return true;
                        }
                    }
                    else
                    {
                        if (as.isArray())
                        { //Comparamos que la variable
                            if (contenido[varname].getDim() > as.getDim() && as.getDim() >= 0)
                            {
                                contenido[varname].setEstado(1);
                                return true;
                            }
                            else
                            {
                                cout << "Direccion no valida..." << endl;
                            }
                        }
                        else
                        {
                        }
                    }
                }
                else
                {
                    cout << "Variable no disponible...";
                }
            }
        }
        else
        {
            cout << "Variable no en tabla" << endl;
        }
        return false;
    };
    bool isInBars(asignacion as)
    { //Verificamos que la variable por asignar este en la tabla de simbolos
        string varname = as.getVarName();
        if (contenido.find(varname) != contenido.end())
        { //Verifica que este en la tabla de simbolos
            if (contenido[varname].getType2() == 0)
            { //Verfica que lo que esta en la tabla sea una variable
                if (as.getVar().getCodeBlock().isChild(contenido[varname].getBloque()))
                {                                      //Verifica que este en el escope
                    if (!contenido[varname].isArray()) //Si la variable en la tabla no es un arreglo
                    {
                        if (!as.isArray())
                        {
                            if (verificarCoherencia(as))
                            {
                                contenido[varname].insertarReferencia(as.getVar().getRenglon());
                                contenido[varname].setEstado(1);
                                return true;
                            }
                            else
                            {
                                cout << "Asignacion no valida " << endl;
                            }
                        }
                    }
                    else
                    {
                        if (as.isArray())
                        {
                            if (contenido[varname].getDim() > as.getSize() && as.getSize() >= 0)
                            {
                                if (verificarCoherencia(as))
                                {
                                    contenido[varname].insertarReferencia(as.getVar().getRenglon());
                                    contenido[varname].setEstado(1);
                                    return true;
                                }
                                else
                                {
                                    cout << "Los operandos ingresado no son validos..." << endl;
                                }
                            }
                            else
                            {
                                cout << "Direccion no valida..." << endl;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            cout << "Variable no en tabla" << endl;
        }
        return false;
    }
    bool verificarCoherencia(condicional con)
    {
        list<variable> vars = con.getVarsInCondition();
        int type = 29;
        bool evaluation = true;
        for (palabra p : con.getCondicion())
        {                           //Verificamos que todos
            if (27 <= p && p <= 30) //Validamos el valor
                evaluation = evaluation && validarValores(type, p);
            else if (p == 37 || (42 <= p && p <= 44) || (48 <= p && p <= 51) || (56 <= p && p <= 61)) //Validamos el operador
                evaluation = evaluation && validarOperadores(type, p);
            else if (p == 31)
            {
                variable v(p);
                evaluation = evaluation && validarVariables(type, v);
                if (!isInBars(p.getWord())) //Si la variable no esta en la variable de simbolos entonces
                {
                    evaluation = evaluation && false;
                }
                else
                {
                    list<variable>::iterator it;
                    if (find(vars.begin(), vars.end(), p) != vars.end())
                    {
                        it = find(vars.begin(), vars.end(), p);
                        if (it != vars.end())
                        { //Validación por seguridad
                            if (isInBars(*it))
                            {                                                           //Si la variable esta en la tabla de simbolos entonces verificamos que sean del mismo tipo
                                evaluation = evaluation && validarVariables(type, *it); //Esta funcion nos ayuda a verificar que la variable contra la que estemos asignando sea del mismo tipo
                            }
                        }
                        else
                        {
                            evaluation = evaluation && false;
                        }
                    }
                    else
                    {
                        evaluation = evaluation && false;
                    }
                    //Insertamos la referencia a la variable a la que se llamo
                }
            }
        }
        return evaluation;
    }
    bool verificarCoherencia(asignacion as)
    { //Verificamos lo coherencia de la asignacion
        string ref = as.getVarName();
        list<variable> &vars = as.getVarAsign();
        int type = contenido[ref].getType().getType();
        bool evaluation = true;
        for (palabra p : as.getOperadores())
        {                           //Verificamos que todos
            if (27 <= p && p <= 30) //Validamos el valor
                evaluation = evaluation && validarValores(type, p);
            else if (p == 37 || (42 <= p && p <= 44) || (48 <= p && p <= 51) || (56 <= p && p <= 61)) //Validamos el operador
                evaluation = evaluation && validarOperadores(type, p);
            else if (p == 31)
            {
                variable v(p);
                evaluation = evaluation && validarVariables(type, v);
                if (!isInBars(p.getWord())) //Si la variable no esta en la variable de simbolos entonces
                {
                    evaluation = evaluation && false;
                }
                else
                {
                    list<variable>::iterator it;
                    if (find(vars.begin(), vars.end(), p) != vars.end())
                    {

                        it = find(vars.begin(), vars.end(), p);

                        if (it != vars.end())
                        { //Validación por seguridad
                            if (isInBars(*it))
                            { //Si la variable esta en la tabla de simbolos entonces verificamos que sean del mismo tipo

                                evaluation = evaluation && validarVariables(type, *it); //Esta funcion nos ayuda a verificar que la variable contra la que estemos asignando sea del mismo tipo
                            }
                        }
                        else
                        {
                            evaluation = evaluation && false;
                        }
                    }

                    else
                    {
                        evaluation = evaluation && false;
                    }
                    //Insertamos la referencia a la variable a la que se llamo
                }
            }
        }
        return evaluation;
    }
    void mostrarTabla()
    {
        for (auto aux : contenido)
        {
            cout << aux.second << endl;
        }
    }
    bool validarVariables(int type, variable var)
    {
        if (8 <= type && type <= 12)
        {
            switch (type)
            {
            //En caso de que la variable sea un string
            case 11:
                if (var.getType() == 11)
                { //El tipo de la variable debe ser un string si no entonces no puede ser una variable que se le pueda asignar
                    return true;
                }
                else
                {
                    return false;
                }
                break;
            case 13: //No puede asignarse un valor void
                return false;
                break;
            //En caso de que la variable sea numerica
            case 8:
            case 12:
                if (var.getType() >= 9 || var.getType() <= 10)
                { //En caso de ser un int no se le puede asignar un double
                    return false;
                }
                else
                {
                    return true;
                }
                break;
            case 9:
            case 10:
                if ((var.getType() >= 8 && var.getType() <= 10) || var.getType() == 12)
                { //Solo se verifica que las variables sean numericas de tipo flotantes
                    return true;
                }
                else
                { //De no ser numerico entonces no es valido
                    return false;
                }
                break;
            default:
                return false;
                break;
            }
        }
        return false;
    }
    bool validarOperadores(int type, palabra p)
    {
        if (p == 37 || (42 <= p && p <= 44) || (48 <= p && p <= 51) || (56 <= p && p <= 61))
        {
            if ((8 <= type && type <= 10) || type == 12) // Los numericos se pueden comparar o hacer operaciones
            {
                return true;
            }
            if (type == 11) // Los strings solo se pueden sumar
            {
                if (p == 42)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool validarValores(int type, palabra p)
    {
        if ((8 <= type && type <= 10) || type == 12)
        {
            switch (p)
            { //Si el tipo es numerico y la palabra es un numero entonces tiene coherencia el operando
            case 27:
            case 28:
            case 29:
                if (type == 8 && (p == 28 || p == 29)) //A un int no le podemos asignar un double o float
                {
                    return false;
                }
                return true;
                break;
            default:
                break;
            }
        }
        else if (type == 11)
        { //Si el operador es un string entonces la palabra debe ser un string
            if (p == 30)
            {
                return true;
            }
        }
        return false;
    }
    palabra getTypeInTable(palabra p)
    {
        if (isInBars(p.getWord()))
        {
            return contenido[p.getWord()].getType();
        }
        else
            return palabra();
    }
    bool isAsignable(string a, string b)
    {
        if (isInBars(a) && isInBars(b))
        {
            int type1 = contenido[a].getType().getType(), type2 = contenido[b].getType().getType();
            if (type2 == 11 && type1 == 11)
            {
                return true;
            }
            else
            {
                return (8 <= type1 && type1 <= 10 && 8 <= type2 && type2 <= 10) ? true : false;
            }
        }
        else
            return false;
    }
    bool isAsignable(palabra a, palabra b)
    {
        if (a != 31 && b != 31)
            return false;
        if (isInBars(a.getWord()) && isInBars(b.getWord()))
        {
            int type1 = contenido[a.getWord()].getType().getType(), type2 = contenido[b.getWord()].getType().getType();
            if (type2 == 11 && type1 == 11)
            {
                return true;
            }
            else
            {
                return (8 <= type1 && type1 <= 10 && 8 <= type2 && type2 <= 10) ? true : false;
            }
        }
        else
            return false;
    }

private:
    map<string, fila> contenido;
    list<int> errors;
};