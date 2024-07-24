#include<iostream>
#include "BalancearArbol.h"
#include "GraficarArbol.h"
#include "Recorridos.h"

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
void eliminar(Nodo *arbol, int n);
void eliminarNodo(Nodo *nodo);
Nodo *minimo(Nodo *arbol);
void reemplazar(Nodo *arbol, Nodo *nuevo);
void destruirNodo(Nodo *nodo);

//Funcion de menu
void menu(){
    int dato, opcion, contador=0, datoEliminar;

    Arbol *a = crearArbol();
    do{
        cout<<"Menu"<<endl;
        cout<<"1. Insertar un nuevo nodo"<<endl;
        cout<<"2. Mostrar el arbol completo"<<endl;
        cout<<"3. Buscar un elemento en el arbol"<<endl;
        cout<<"4. Eliminar nodo del arbol" << endl;
        cout<<"5. PreOrden" << endl;
        cout<<"6. inOrden" << endl;
        cout<<"7. PostOrden" << endl;
        cout<<"8. Salir"<<endl;
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
    case 4:
        cout << "\nDigite el numero a eliminar: ";
        cin >>datoEliminar;
        eliminar(a->raiz,datoEliminar);
        cout << endl;
        system("pause");
        break;
    case 5:
        cout << "\nRecorrido en PreOrden: ";
        preOrden(a->raiz);
        cout << endl;
        system("pause");
        break;
    case 6:
        cout << "\nRecorrido en InOrden: ";
        inOrden(a->raiz);
        cout << endl;
        system("pause");
        break;
    case 7:
        cout << "\nRecorrido en PostOrden: ";
        postOrden(a->raiz);
        cout << endl;
        system("pause");
        break;
    }
        system("cls");
    }while(8!=opcion);

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

//Para eliminar un nodo del arbol
void eliminar(Nodo *arbol, int n){
    if(arbol==NULL){
        return;
    }
    else if(n< arbol->dato){ // si el valor es menor busca por la izquierda
        eliminar(arbol->izq,n);
    }
    else if(n > arbol->dato){ // si el elemento es mayor busca por la derecha
        eliminar(arbol->der,n);
    }
    else{
        eliminarNodo(arbol);
    }
}

Nodo *minimo(Nodo *arbol){
    if(arbol == NULL){
        return NULL;
    }
    if(arbol->izq){
        return minimo(arbol->izq);
    }
    else{
        return arbol;
    }
}

void reemplazar(Nodo *arbol, Nodo *nuevo){
    if(arbol->padre){
        if(arbol->dato == arbol->padre->izq->dato){
            arbol->padre->izq = nuevo;
        }
        else if(arbol->dato == arbol->padre->der->dato){
            arbol->padre->der = nuevo;
        }
    }
    if(nuevo){
        nuevo->padre = arbol->padre;
    }
}

void destruirNodo(Nodo *nodo){
    nodo->izq = NULL;
    nodo->der = NULL;

    delete nodo;
}

void eliminarNodo(Nodo *nodo){
    if(nodo->izq && nodo->der){ //caso 1 el nodo tiene ambos hijos
        Nodo *menor = minimo(nodo->der);
        nodo->dato= menor->dato;
        eliminarNodo(menor);
    }
    else if(nodo->izq){
        reemplazar(nodo, nodo->izq);
        destruirNodo(nodo);
    }
    else if(nodo->der){
        reemplazar(nodo,nodo->der);
        destruirNodo(nodo);
    }
    else{
        reemplazar(nodo,NULL);
        destruirNodo(nodo);
    }
}


