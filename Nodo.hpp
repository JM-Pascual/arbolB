#ifndef _NODO_HPP
#define _NODO_HPP

#include <stddef.h>

#include <string>

#include <iostream>

using namespace std;

template<typename tipo_llave, typename tipo_dato, class Nodo> class arbolB; //Forward declaration

template<typename tipo_llave, typename tipo_dato>

class Nodo{
private:
    int vias;

    tipo_llave *llaves;
    tipo_dato*datos;
    bool *eliminado;

    Nodo** hijos;

    bool es_hoja;

    int cantidad_de_llaves;
    int cantidad_de_hijos;

    void partir_nodo(tipo_llave &median_llave, tipo_dato &median_dato, bool& estado_llave_median, Nodo* &nuevo_nodo_derecho){
    nuevo_nodo_derecho = new Nodo(vias);
    nuevo_nodo_derecho->es_hoja = es_hoja; //El nodo que se parte reconoce si es hoja o no

    median_llave = llaves[(vias-1)/2];
    median_dato = datos[(vias-1)/2];
    estado_llave_median = eliminado[(vias-1)/2];
    cantidad_de_llaves--;

    for(int i = 0; i < (vias/2); i++){ 
        nuevo_nodo_derecho->llaves[i] = llaves[((vias-1)/2) +1 +i]; //copio la derecha de la median key en el nuevo nodo (llaves)
        nuevo_nodo_derecho->datos[i] = datos[((vias-1)/2) +1 +i]; //copio la derecha de la median key en el nuevo nodo (datos)
        nuevo_nodo_derecho->eliminado[i] = eliminado[((vias-1)/2) +1 +i]; ////copio la derecha de la median key en el nuevo nodo (eliminados)

        cantidad_de_llaves--; //Resto 1 llave en el nodo "viejo"
        nuevo_nodo_derecho->cantidad_de_llaves++; //Sumo 1 llave al nodo derecho que cree
    }

    for (int j = 0; j < ((vias/2)+1); j++){
        if (hijos[((vias-1)/2) +1 +j] != nullptr){
            nuevo_nodo_derecho->hijos[j] = hijos[((vias-1)/2) +1 +j];
            cantidad_de_hijos--;
            nuevo_nodo_derecho->cantidad_de_hijos++; 
            hijos[((vias-1)/2) +1 +j] = nullptr;
        }
    }
}

    
    void limpiar_nodo(){
        int i;
        for (i = 0; i < cantidad_de_hijos; i++) {
            hijos[i]->limpiar_nodo();
            hijos[i] = nullptr;
        }
        delete this;
    }


public:
    Nodo(int vias_arbol){
        vias = vias_arbol;
        hijos = new Nodo*[vias +1]();
        
        llaves = new tipo_llave[vias]();
        datos = new tipo_dato[vias]();
        eliminado = new bool[vias]();

        cantidad_de_llaves = 0;
        cantidad_de_hijos = 0;

        es_hoja = true;
    }

    void recorrer(int tabulacion){
        int i;
        string tabulaciones;
        for (int i = 0; i < tabulacion; i++) {
            tabulaciones += '\t';
        }
        for (i = 0; i < cantidad_de_llaves; i++) {
            if (!es_hoja){ 
                hijos[i]->recorrer(tabulacion + 1);
            }
            cout << tabulaciones << llaves[i] <<endl;
        }
        if (!es_hoja){
            hijos[i]->recorrer(tabulacion + 1);
        }
    }



    void insertar(tipo_llave llave, tipo_dato dato, tipo_llave &median_llave, tipo_dato &median_dato, bool& estado_llave_median, Nodo* &nuevo_nodo_derecho){
        if (!es_hoja){ //NUNCA se inserta un nuevo valor en un nodo que no es hoja
            int i = 0;
            while (i < cantidad_de_llaves && llave > llaves[i]){
                i++;
            }

            hijos[i]->insertar(llave, dato, median_llave, median_dato, estado_llave_median, nuevo_nodo_derecho);

            //CASOS POST RECURSIÓN!

            if(nuevo_nodo_derecho == nullptr){
                return;
            }

            else{ //Else ---> subió algo!
                int i = cantidad_de_llaves;

                while (i > 0 && median_llave < llaves[i -1]){
                    llaves[i] = llaves[i -1];
                    datos[i] = datos[i-1];
                    eliminado[i] = eliminado[i-1];
                    i--;
                }
                llaves[i] = median_llave;
                datos[i] = median_dato;
                eliminado[i] = estado_llave_median; //inicializo la llave con la condicion con la que subio
                cantidad_de_llaves++; //Falta el while de los hijos

                int j = cantidad_de_hijos -1;

                while (j > i){
                    hijos[j +1] = hijos[j];
                    j--;
                }
                hijos[i +1] = nuevo_nodo_derecho;
                cantidad_de_hijos++;

                if (cantidad_de_llaves == vias){
                    nuevo_nodo_derecho = nullptr;
                    partir_nodo(median_llave, median_dato, estado_llave_median, nuevo_nodo_derecho);
                    return;
                }
                else{
                    nuevo_nodo_derecho = nullptr; //Una vez agregando el hijo lo setea en nullptr
                    return;
                }
            }
        }

        else{
            int i = cantidad_de_llaves; 
            while (i > 0 && llave < llaves[i -1]){
                    llaves[i] = llaves[i -1];
                    datos[i] = datos[i -1];
                    eliminado[i] = eliminado[i -1];
                    i--;
            }
            llaves[i] = llave;
            datos[i] = dato;
            eliminado[i] = false; //al insertar una llave en una hoja, siempre va a inicializarse como NO eliminada. 
            cantidad_de_llaves++;

            if (cantidad_de_llaves == vias){
                nuevo_nodo_derecho = nullptr;
                partir_nodo(median_llave, median_dato, estado_llave_median, nuevo_nodo_derecho);
                return;
            }
            else{
                return;
            }
        }
    }



    void buscar_dato(tipo_llave llave, bool llave_encontrada, tipo_dato &dato){
        int i = 0;
        while(!llave_encontrada && i < cantidad_de_llaves){
            if (!es_hoja){
                hijos[i]->buscar_dato(llave, llave_encontrada, dato);
            }
            if(!llave_encontrada && llaves[i] == llave && !eliminado[i]){
                dato = datos[i];
                llave_encontrada = true;
            }
            i++;
        }
        if(!llave_encontrada && !es_hoja){
            hijos[i]->buscar_dato(llave, llave_encontrada, dato);
        }
    }


    void eliminar_dato(tipo_llave llave, bool& fin_eliminacion){
        int i = 0;
        while(!fin_eliminacion && i < cantidad_de_llaves){
            if (!fin_eliminacion && !es_hoja){
                hijos[i]->eliminar_dato(llave, fin_eliminacion);
            }
            if(!fin_eliminacion && llaves[i] == llave){
                fin_eliminacion = true;
                eliminado[i] = true;
            }
            i++;
        }
        if(!fin_eliminacion && !es_hoja){
            hijos[i]->eliminar_dato(llave, fin_eliminacion);
        }    
    }
    
    ~Nodo(){
        delete [] llaves;
        delete [] datos;
        delete [] eliminado;
        delete [] hijos;

        llaves = nullptr;
        datos = nullptr;
        eliminado = nullptr;
        hijos = nullptr;

        cantidad_de_llaves = 0;
        cantidad_de_hijos = 0;
    }

friend class arbolB<tipo_llave, tipo_dato, class Nodo>;
};


#endif