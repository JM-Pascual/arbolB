#ifndef ARBOLB_HPP
#define ARBOLB_HPP

#include "Nodo.hpp"


template<typename tipo_llave, typename tipo_dato, class Nodo>

class arbolB{
private:
    int vias;
    int elementos_totales;
    int elementos_eliminados;

    Nodo* raiz;
    
public:
    arbolB(int vias_del_arbol){
        vias = vias_del_arbol;
        raiz = new Nodo(vias);
        raiz->es_hoja = true;
    }


    void insertar(tipo_llave llave, tipo_dato dato){
        tipo_llave median_llave = llave;
        tipo_dato median_dato = dato; //Estas dos lineas de código sirven únicamente para evitar warnings
        //Debido a que le estoy pasando un valor el cual puede, y va a, cambiar en runtime, el compiler me avisa
        //al definir previamente la variable no se alarma, y debido a que el programa controla insertar la median key correcta está bien

        bool estado_llave_median = false;
        Nodo* nuevo_nodo_derecho = nullptr;

        raiz->insertar(llave, dato, median_llave, median_dato, estado_llave_median, nuevo_nodo_derecho);

        //SIEMPRE que se llena la raíz y la spliteo, separo en dos ramas!
        if (nuevo_nodo_derecho != nullptr){
            Nodo* raiz_nueva = new Nodo(vias);
            raiz_nueva->es_hoja = false;

            raiz_nueva->llaves[0] = median_llave;
            raiz_nueva->datos[0] = median_dato;

            raiz_nueva->cantidad_de_llaves = 1;
            raiz_nueva->cantidad_de_hijos = 2;

            raiz_nueva->hijos[0] = raiz;
            raiz_nueva->hijos[1] = nuevo_nodo_derecho;
            raiz = raiz_nueva;
        }
        elementos_totales++;
    }


    tipo_dato consultar(tipo_llave llave){
        tipo_dato dato = nullptr;
        bool llave_encontrada = false;
        raiz->buscar_dato(llave, llave_encontrada, dato);
        return(dato);
    }


    void eliminar(tipo_llave llave){
        bool fin_eliminacion = false;
        raiz->eliminar_dato(llave, fin_eliminacion);
        elementos_eliminados++;
    }
    

    void recorrer(){
        raiz->recorrer(0);
    }


    void recorrer_datos(){
        raiz->recorrer_datos(0);
    }


    int obtener_elementos_totales(){
        return (elementos_totales);
    }


    int obtener_elementos_disponibles(){
        return (elementos_totales - elementos_eliminados);
    }


    ~arbolB(){
        raiz->limpiar_nodo();
        raiz = nullptr;
    }
};

#endif