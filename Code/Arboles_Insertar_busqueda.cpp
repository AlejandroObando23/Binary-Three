#include<iostream>
#include "BalancearArbol.h"
#include "GraficarArbol.h"

using namespace std;

struct Nodo{
    int dato;
    int factorEQ;
    Nodo *padre;
    Nodo *der;
    Nodo *izq;
};

struct Arbol{
	int totalIzq;
    Nodo *raiz;
    int totalDer;
};

Arbol* crearArbol(){
	Arbol *aux=new Arbol();
    aux->totalIzq=0;
    aux->totalDer=0;
    aux->raiz=NULL;
    return aux;
}

//Prototipos
void menu();
Nodo *crearNodo(int n);
void insertarNodo(Arbol *a,Nodo *n);
void mostrarArbol(Nodo *arbol, int contador);
bool busqueda(Nodo *arbol, int n);

//Funcion de menu
void menu(){
    int dato, opcion, contador=0;

    Arbol *a = crearArbol();
    do{
        cout<<"Menu"<<endl;
        cout<<"1. Insertar un nuevo nodo"<<endl;
        cout<<"2. Mostrar el arbol completo"<<endl;
        cout<<"3. Buscar un elemento en el arbol"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"Opcion: "<<endl;
        cin>>opcion;
        switch(opcion){
    case 1:
        cout<<"Ingrese un numero: ";
        cin>>dato;
        insertarNodo(a,crearNodo(dato));
        system("pause");
        cout<<"\n";
        break;
    case 2:{
        cout<<"\nMostrando el arbol completo\n";
        mostrarArbol(a->raiz, contador);
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "C:\\TC\\BGI");
        int windowWidth = getmaxx();
        int windowHeight = getmaxy();
        dibujarArbol<Nodo>(a->raiz, windowWidth/2, 100, windowWidth/4, 0);
        cout<<"\n";
        system("pause");
        break;
        }
    case 3:
        cout<<"\nDigite el elemento a buscar: ";
        cin>>dato;
        if(busqueda(a->raiz, dato)== true){
            cout<<"\n El elemento ha sido encontrado en el arbol";

        }else{
        cout<<"\nElemento no encontrado\n";
        }
        system("pause");
        break;
        }
        system("cls");
    }while(4!=opcion);

}



int main(){
    menu();
    return 0;

}
//Funciones
Nodo *crearNodo(int n){
    Nodo *nuevo_nodo = new Nodo();

    nuevo_nodo->dato=n;
    nuevo_nodo->der=NULL;
    nuevo_nodo->izq=NULL;

    return nuevo_nodo;
}

bool busqueda(Nodo *arbol, int n){
    if(arbol==NULL){
        return false;
    }
    else if(arbol->dato ==n){
        return true;

    }else if(n< arbol->dato){
        return busqueda(arbol->izq,n);
    }else{
        return busqueda(arbol->der,n);

        }
}

void insertarNodo(Arbol *a,Nodo *n){
	Nodo *aux,*ant;
	if(a->raiz == NULL){
		a->raiz=n;
	}else{
		aux=a->raiz;
		while(aux!=NULL){
			ant=aux;
			if(n->dato > aux ->dato){
				aux=aux->der;
			}else{
				aux=aux->izq;
			}
		}
		n->padre=ant;
		if(n->dato > ant->dato){
			ant->der=n;
		}else{
			ant->izq=n;
		}
		balancear<Arbol, Nodo>(a,ant);
	}
}

void mostrarArbol(Nodo *arbol,int cont){
    if(arbol == NULL){
        return;
    }else{
        mostrarArbol(arbol->der, cont+1);
        for(int i=0; i<cont; i++){
            cout<<" ";
        }
        cout<<arbol->dato<<endl;
        mostrarArbol(arbol->izq,cont+1);
    }
}
/*
Nodo *recuperarNodo(Nodo *arbol, int n){
    else if(arbol->dato ==n){
        return arbol;

    }else if(n< arbol->dato){
        return busqueda(arbol->izq,n);
    }else{
        return busqueda(arbol->der,n);
        }
}

void eliminarNodo(Nodo *arbol, int n){
    Nodo *encontrado, *aux;
    if(busqueda(arbol,n)){
        encontrado = recuperarNodo(arbol,n);

    }
}
*/
