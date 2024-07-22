#include<iostream>
using namespace std;

struct Nodo{
    int dato;
    Nodo *der;
    Nodo *izq;
};
//Prototipos
void menu();
Nodo *crearNodo(int n);
void insertarNodo(Nodo *&arbol, int n);
void mostrarArbol(Nodo *arbol, int contador);
bool busqueda(Nodo *arbol, int n);
Nodo *arbol=NULL;

//Funcion de menu
void menu(){
    int dato, opcion, contador=0;
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
        insertarNodo(arbol, dato);
        cout<<"\n";
        break;
    case 2:
        cout<<"\nMostrando el arbol completo\n";
        mostrarArbol(arbol, contador);
        cout<<"\n";
        system("pause");
        break;
    case 3:
        cout<<"\nDigite el elemento a buscar: ";
        cin>>dato;
        if(busqueda(arbol, dato)== true){
            cout<<"\n El elemento ha sido encontrado en el arbol";

        }else{
        cout<<"\nElemento no encontrado\n";
        }

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
void insertarNodo(Nodo *&arbol, int n){
    if(arbol == NULL){
        Nodo *nuevo_nodo =crearNodo(n);
        arbol = nuevo_nodo;

    }else{
        int valorRaiz =arbol->dato;
        if(n < valorRaiz){
            insertarNodo(arbol->izq,n);
        }else{
            insertarNodo(arbol->der,n);
        }

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


