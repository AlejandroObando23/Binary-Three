#include <iostream>
#include <string>

using namespace std;


template <typename T>
void preOrden(T *arbol, string& resultado){
    if(arbol == NULL){
        return;
    }
    else{
        resultado += to_string(arbol->dato) + " - ";
        preOrden(arbol->izq, resultado);
        preOrden(arbol->der, resultado);
    }
}

template <typename T>
void inOrden(T *arbol, string& resultado){
    if(arbol == NULL){
        return;
    }
    else{
        inOrden(arbol->izq, resultado);
        resultado += to_string(arbol->dato) + " - ";
        inOrden(arbol->der, resultado);
    }
}

template <typename T>
void postOrden(T *arbol, string& resultado){
    if(arbol == NULL){
        return;
    }
    else{
        postOrden(arbol->izq, resultado);
        postOrden(arbol->der, resultado);
        resultado += to_string(arbol->dato) + " - ";
    }
}
