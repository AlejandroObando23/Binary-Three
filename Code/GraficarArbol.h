#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
void dibujarArbol(T *raiz, int x, int y, int distancia, int nivel ){
    if(raiz == NULL){
        return;
    }

    int radioCirculo = 20;
    int tamanioFuente = 1;
    setbkcolor(5);
    setcolor(CYAN);
    circle(x,y,radioCirculo);
    setfillstyle(SOLID_FILL, 5);
    floodfill(x, y, 3);
    setcolor(15);
    settextstyle(6, HORIZ_DIR, tamanioFuente);
    char buffer[10];
    sprintf(buffer, "%d", raiz->dato);
    outtextxy(x - 10, y - 10, buffer);

    int nuevoX = x - distancia;
    int nuevoY = y + 80;

    if (raiz->izq) {
        setcolor(GREEN);
        line(x, y + radioCirculo, nuevoX, nuevoY - radioCirculo);
        dibujarArbol(raiz->izq, nuevoX, nuevoY, distancia/2, nivel++);
    }

    nuevoX = x + distancia;
    if (raiz->der) {
        setcolor(RED);
        line(x, y + radioCirculo, nuevoX, nuevoY - radioCirculo);
        dibujarArbol(raiz->der, nuevoX, nuevoY, distancia/2, nivel++);
    }

}
