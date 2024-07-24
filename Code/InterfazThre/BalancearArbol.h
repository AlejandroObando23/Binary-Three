#include <iostream>

using namespace std;

template <typename T>
int calcularAltura(T *nodo){
    if(nodo!= NULL){
        int alturaIzquierda = calcularAltura(nodo->izq);
        int alturaDerecha = calcularAltura(nodo->der);

        if(alturaIzquierda < alturaDerecha){
            return alturaDerecha +1;
        }else{
            return alturaIzquierda +1;
        }
    }else{
        return 0;
    }
}

template <typename T>
int calcularFactorEquilibrio(T *nodo){
    return calcularAltura(nodo->der)-calcularAltura(nodo->izq);
}
template <typename T, typename Y>
void rotarIzquierda(T *a, Y *n){
    Y *aux,*p,*q;
	aux=n->der;
	q=aux->izq;
	p=n->padre;

	n->der=q;
	aux->izq=n;

	if(q!=NULL){
		q->padre=n;
	}
	n->padre=aux;
	aux->padre=p;
	if(p==NULL){
		a->raiz=aux;
	}else{
		if(aux->dato > p->dato){
			p->der=aux;
		}else{
			p->izq=aux;
		}
	}
	aux->factorEQ=calcularFactorEquilibrio(aux);
	n->factorEQ=calcularFactorEquilibrio(n);
}

template <typename T, typename Y>
void rotarDerecha(T *a, Y *n){
	Y *aux,*p,*q;
	aux=n->izq;
	q=aux->der;
	p=n->padre;

	n->izq=q;
	aux->der=n;

	if(q!=NULL){
		q->padre=n;
	}
	n->padre=aux;
	aux->padre=p;
	if(p==NULL){ //la raiz del arbol
		a->raiz=aux;
	}else{
		if(aux->dato > p->dato){
			p->der=aux;
		}else{
			p->izq=aux;
		}
	}
	aux->factorEQ=calcularFactorEquilibrio(aux);
	n->factorEQ=calcularFactorEquilibrio(n);
}

template <typename T, typename Y>
void rotarDobleDerecha(T *raiz, Y *nodo){
    rotarDerecha(raiz, nodo->der);
    rotarIzquierda(raiz, nodo);
}

template <typename T, typename Y>
void rotarDobleIzquierda(T *raiz, Y *nodo){
    rotarIzquierda(raiz, nodo->izq);
    rotarDerecha(raiz, nodo);
}

template <typename T, typename Y>
void balancear(T *a, Y *p){
	Y *padre;
	if(p!=NULL){
		padre=p->padre;
		p->factorEQ=calcularFactorEquilibrio(p);
		if(p->factorEQ>1){ //desbalanceo derecho
			if(calcularFactorEquilibrio(p->der)<0){
				rotarDobleIzquierda(a,p);
			}else{
				rotarIzquierda(a,p);
			}
		}else if(p->factorEQ<-1){ //desbalanceo izquierda
			if(calcularFactorEquilibrio(p->izq)>0){
				rotarDobleDerecha(a,p);
			}else{
				rotarDerecha(a,p);
			}
		}
		balancear(a,padre);
	}
}
