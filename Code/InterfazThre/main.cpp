#include <windows.h>
#include <string>
#include <iostream>
#include "Arboles_insertar_busqueda.h"
using namespace std;
#define ID_LABEL 100
#define ID_BTNSALIR 101
#define ID_BTNINCERCION 102
#define ID_BTNBALANCEO 103
#define ID_BTNRECORRIDOS 104
#define ID_BTNBUSQUEDA 105
#define ID_BTNELIMINACION 106
#define ID_BTNGUARDAR 107
#define ID_TEXT 108
 #define  ID_LABEL_RESULT 109
#define ID_LABEL_TITULO 110


//Ventanas
//Funciones
LRESULT CALLBACK ProcediementoVentana(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProcedimientoVentanaSecundaria(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProcedimientoVentanaTerciaria(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProcedimientoVentanaCuaternaria(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProcedimientoVentanaQuinta(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProcedimientoVentanaSexta(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProcedimientoVentanaSeptima(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//Asiganaciones necesarias para las funciones
HWND hwndVentanaSecundaria = NULL;
HWND hwndVentanaTerciaria= NULL;
HWND hwndVentanaCuaternaria = NULL;
HWND hwndVentanaQuinta = NULL;
HWND hwndVentanaSexta = NULL;
HWND hwndVentanaSeptima = NULL;

//Texto
HWND textEdit;


/*
Secundario = Incersion
Tercero = Recorridos
Cuarto = Busqueda
Quinto = ----------
Sexto = Eliminacion


*/

HINSTANCE hInstancia;
    int dato, opcion, contador=0, datoEliminar;
    Arbol *a = crearArbol();
    string resultado;




int WINAPI WinMain(HINSTANCE hIns, HINSTANCE hInstanciaPrevia, LPSTR lpCmdLinea, int nCmdShow) {
    initwindow(720, 720);
    hInstancia = hIns;
    HWND ventana;
    MSG mensaje;
    WNDCLASSEX clase;
    clase.cbSize = sizeof(WNDCLASSEX);
    clase.cbClsExtra = 0;
    clase.style = CS_HREDRAW | CS_VREDRAW;
    clase.lpfnWndProc = ProcediementoVentana;
    clase.hInstance = hIns;
    clase.hIcon = LoadIcon(NULL, 0);
    clase.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
    clase.hCursor = LoadCursor(NULL, IDC_ARROW);
    clase.lpszClassName = "IdentificadorVentana";
    clase.hbrBackground = CreateSolidBrush(RGB(183, 55, 243));
    if (!RegisterClassEx(&clase)) {
        MessageBox(NULL, "No se pudo ejecutar la aplicacion", "Error", MB_ICONERROR);
        return EXIT_FAILURE;
    }

    ventana = CreateWindowEx(0, "IdentificadorVentana", "Controles", WS_OVERLAPPEDWINDOW | WS_SYSMENU,
                             400, 80, 580, 630, HWND_DESKTOP, NULL, hIns, NULL);

    CreateWindow("Static","Arbol Binario: ",WS_VISIBLE | WS_CHILD |SS_NOTIFY,100 ,10,150,20,ventana,(HMENU)ID_LABEL_TITULO,NULL,NULL);
    CreateWindowEx(0, "BUTTON", "Salir", BS_CENTER | WS_VISIBLE | WS_CHILD, 100, 280, 150, 30, ventana, (HMENU)ID_BTNSALIR, NULL, NULL);
    CreateWindowEx(0, "BUTTON", "Creacion/Insercion", BS_CENTER | WS_VISIBLE | WS_CHILD, 100, 240, 150, 30, ventana, (HMENU)ID_BTNINCERCION, NULL, NULL);
    CreateWindowEx(0, "BUTTON", "Recorridos", BS_CENTER | WS_VISIBLE | WS_CHILD, 100, 200, 150, 30, ventana, (HMENU)ID_BTNBALANCEO, NULL, NULL);
    CreateWindowEx(0, "BUTTON", "Busqueda", BS_CENTER | WS_VISIBLE | WS_CHILD, 100, 160, 150, 30, ventana, (HMENU)ID_BTNBUSQUEDA, NULL, NULL);
    CreateWindowEx(0, "BUTTON", "Eliminacion", BS_CENTER | WS_VISIBLE | WS_CHILD, 100, 120, 150, 30, ventana, (HMENU)ID_BTNELIMINACION, NULL, NULL);

    ShowWindow(ventana, nCmdShow);
    UpdateWindow(ventana);

    while (GetMessage(&mensaje, NULL, 0, 0) > 0) {
        TranslateMessage(&mensaje);
        DispatchMessage(&mensaje);
    }

    return mensaje.wParam;
}

LRESULT CALLBACK ProcediementoVentana(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HWND himg;
    HBITMAP cargar_img;
    cargar_img = (HBITMAP)LoadImageW(NULL, L"calculator.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    static HINSTANCE Instancia;
    switch (msg) {
    case WM_CREATE: {
        Instancia = ((LPCREATESTRUCT)lParam)->hInstance;
        himg = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 80, 340, 0, 0, hwnd, NULL, Instancia, NULL);
        SendMessageW(himg, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)cargar_img);
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case ID_BTNELIMINACION:{
            if (hwndVentanaSexta == NULL) {
                WNDCLASSEX wcSexta = { sizeof(WNDCLASSEX) };
                wcSexta .style = CS_HREDRAW | CS_VREDRAW;
                wcSexta .lpfnWndProc = ProcedimientoVentanaSexta;
                wcSexta .hInstance = hInstancia;
                wcSexta .hIcon = LoadIcon(NULL, IDI_APPLICATION);
                wcSexta .hCursor = LoadCursor(NULL, IDC_ARROW);
                wcSexta .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcSexta .lpszClassName = "ClaseVentanaQuinta";
                wcSexta .hIconSm = LoadIcon(NULL, IDI_APPLICATION);

                if (!RegisterClassEx(&wcSexta) && !(hwndVentanaSexta == NULL) ) {
                    MessageBox(hwnd, "Fallo al registrar la clase de la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }
                hwndVentanaSexta = CreateWindowEx(
                    0,
                    "ClaseVentanaQuinta",
                    "Ventana Quinta",
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                    hwnd,
                    NULL,
                    hInstancia,
                    NULL
                );


                if (hwndVentanaSexta== NULL) {
                    MessageBox(hwnd, "Fallo al crear la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }

                ShowWindow(hwndVentanaSexta, SW_SHOW);
                UpdateWindow(hwndVentanaSexta);
            } else {
               SetForegroundWindow(hwndVentanaSexta);
            }
            break;
        }
        case ID_BTNRECORRIDOS:{
            if (hwndVentanaQuinta == NULL) {
                WNDCLASSEX wcQuinta = { sizeof(WNDCLASSEX) };
                wcQuinta .style = CS_HREDRAW | CS_VREDRAW;
                wcQuinta .lpfnWndProc = ProcedimientoVentanaQuinta;
                wcQuinta .hInstance = hInstancia;
                wcQuinta .hIcon = LoadIcon(NULL, IDI_APPLICATION);
                wcQuinta .hCursor = LoadCursor(NULL, IDC_ARROW);
                wcQuinta .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcQuinta .lpszClassName = "ClaseVentanaQuinta";
                wcQuinta .hIconSm = LoadIcon(NULL, IDI_APPLICATION);

                if (!RegisterClassEx(&wcQuinta) && !(hwndVentanaQuinta == NULL) ) {
                    MessageBox(hwnd, "Fallo al registrar la clase de la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }
                hwndVentanaQuinta = CreateWindowEx(
                    0,
                    "ClaseVentanaQuinta",
                    "Ventana Quinta",
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                    hwnd,
                    NULL,
                    hInstancia,
                    NULL
                );


                if (hwndVentanaQuinta== NULL) {
                    MessageBox(hwnd, "Fallo al crear la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }

                ShowWindow(hwndVentanaQuinta, SW_SHOW);
                UpdateWindow(hwndVentanaQuinta);
            } else {
               SetForegroundWindow(hwndVentanaQuinta);
            }
            break;
        }
        case ID_BTNBUSQUEDA:{
        if (hwndVentanaCuaternaria == NULL) {
                WNDCLASSEX wcCuaternaria = { sizeof(WNDCLASSEX) };
                wcCuaternaria .style = CS_HREDRAW | CS_VREDRAW;
                wcCuaternaria .lpfnWndProc = ProcedimientoVentanaCuaternaria;
                wcCuaternaria .hInstance = hInstancia;
                wcCuaternaria .hIcon = LoadIcon(NULL, IDI_APPLICATION);
                wcCuaternaria .hCursor = LoadCursor(NULL, IDC_ARROW);
                wcCuaternaria .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcCuaternaria .lpszClassName = "ClaseVentanaCuaternaria";
                wcCuaternaria .hIconSm = LoadIcon(NULL, IDI_APPLICATION);

                if (!RegisterClassEx(&wcCuaternaria) && !(hwndVentanaCuaternaria == NULL) ) {
                    MessageBox(hwnd, "Fallo al registrar la clase de la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }
                hwndVentanaCuaternaria = CreateWindowEx(
                    0,
                    "ClaseVentanaCuaternaria",
                    "Ventana Cuatro",
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                    hwnd,
                    NULL,
                    hInstancia,
                    NULL
                );


                if (hwndVentanaCuaternaria== NULL) {
                    MessageBox(hwnd, "Fallo al crear la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }

                ShowWindow(hwndVentanaCuaternaria, SW_SHOW);
                UpdateWindow(hwndVentanaCuaternaria);
            } else {
               SetForegroundWindow(hwndVentanaCuaternaria);
            }
            break;
        }

        case ID_BTNBALANCEO:{
            if (hwndVentanaTerciaria == NULL) {
                WNDCLASSEX wcTerciaria = { sizeof(WNDCLASSEX) };
                wcTerciaria.style = CS_HREDRAW | CS_VREDRAW;
                wcTerciaria.lpfnWndProc = ProcedimientoVentanaTerciaria;
                wcTerciaria.hInstance = hInstancia;
                wcTerciaria.hIcon = LoadIcon(NULL, IDI_APPLICATION);
                wcTerciaria.hCursor = LoadCursor(NULL, IDC_ARROW);
                wcTerciaria.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcTerciaria.lpszClassName = "ClaseVentanaTerciaria";
                wcTerciaria.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

                if (!RegisterClassEx(&wcTerciaria) && !(hwndVentanaTerciaria == NULL) ) {
                    MessageBox(hwnd, "Fallo al registrar la clase de la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }
                hwndVentanaTerciaria = CreateWindowEx(
                    0,
                    "ClaseVentanaTerciaria",
                    "Ventana Terciaria",
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                    hwnd,
                    NULL,
                    hInstancia,
                    NULL
                );


                if (hwndVentanaTerciaria == NULL) {
                    MessageBox(hwnd, "Fallo al crear la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }

                ShowWindow(hwndVentanaTerciaria, SW_SHOW);
                UpdateWindow(hwndVentanaTerciaria);
            } else {
               SetForegroundWindow(hwndVentanaTerciaria);
            }
            break;
        }
        case ID_BTNSALIR: {
            if (MessageBox(hwnd, "¿Desea salir del programa?", "Salir.", MB_OKCANCEL | MB_ICONQUESTION) == IDOK) {
                SendMessage(hwnd, WM_DESTROY, 0, 0);
            }
            break;
        }
        case ID_BTNINCERCION: {
            if (hwndVentanaSecundaria == NULL) {
                WNDCLASSEX wcSecundaria = { sizeof(WNDCLASSEX) };
                wcSecundaria.style = CS_HREDRAW | CS_VREDRAW;
                wcSecundaria.lpfnWndProc = ProcedimientoVentanaSecundaria;
                wcSecundaria.hInstance = hInstancia;
                wcSecundaria.hIcon = LoadIcon(NULL, IDI_APPLICATION);
                wcSecundaria.hCursor = LoadCursor(NULL, IDC_ARROW);
                wcSecundaria.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcSecundaria.lpszClassName = "ClaseVentanaSecundaria";
                wcSecundaria.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

                if (!RegisterClassEx(&wcSecundaria) && !(hwndVentanaSecundaria == NULL) ) {
                    MessageBox(hwnd, "Fallo al registrar la clase de la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }

                hwndVentanaSecundaria = CreateWindowEx(
                    0,
                    "ClaseVentanaSecundaria",
                    "Ventana Secundaria",
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                    hwnd,
                    NULL,
                    hInstancia,
                    NULL
                );

                if (hwndVentanaSecundaria == NULL) {
                    MessageBox(hwnd, "Fallo al crear la ventana secundaria.", "Error", MB_ICONERROR);
                    return -1;
                }

                ShowWindow(hwndVentanaSecundaria, SW_SHOW);
                UpdateWindow(hwndVentanaSecundaria);
            } else {
               SetForegroundWindow(hwndVentanaSecundaria);
            }
            break;
        }
        }
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    case WM_CTLCOLORSTATIC: {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkColor(hdcStatic, RGB(21, 232, 189));
        return (INT_PTR)CreateSolidBrush(RGB(21, 232, 189));
        break;
    }
    default: {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }


    }
    return 0;
}

LRESULT CALLBACK ProcedimientoVentanaSecundaria(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        CreateWindow("Static","Ingrese un numero : ",WS_VISIBLE | WS_CHILD |SS_NOTIFY,20 ,10,150,20,hwnd,(HMENU)ID_LABEL,NULL,NULL);
        textEdit=CreateWindow("EDIT",   // Predefined class; Unicode assumed
                NULL,         // No window title
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT| ES_NUMBER, // Styles
                170,         // x position
                10,         // y position
                200,        // Text box width
                25,        // Text box height
                hwnd,       // Parent window
                (HMENU) ID_TEXT,       // No menu.
                GetModuleHandle(NULL),
                NULL);
        CreateWindow("BUTTON", "Guardar",  WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,80, 50, 100, 30, hwnd,(HMENU)ID_BTNGUARDAR,NULL,NULL);

        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == ID_BTNGUARDAR) {
                char buffer[256];
                GetWindowText(textEdit, buffer, 256);
                dato = atoi(buffer);
                cout<<dato;

                insertarNodo(a,crearNodo(dato));
                setbkcolor(0);
                cleardevice();
                int windowWidth = getmaxx();
                int windowHeight = getmaxy();
                dibujarArbol<Nodo>(a->raiz, windowWidth/2, 100, windowWidth/4, 0);


        }
        break;

    }
    case WM_DESTROY: {
        hwndVentanaSecundaria = NULL;
        break;
    }
    default: {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }



    }
    return 0;
}
LRESULT CALLBACK ProcedimientoVentanaTerciaria(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        // Create a button with the label "Presionar"
        CreateWindow("BUTTON", "Presionar",
                     WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     20, 10, 150, 20, hwnd, (HMENU)ID_BTNGUARDAR, NULL, NULL);
        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == ID_BTNGUARDAR) {

            preOrden(a->raiz, resultado);

            const char* charArray = resultado.c_str();

            CreateWindow("Static", "Preorden",
                         WS_VISIBLE | WS_CHILD | SS_NOTIFY,
                         20, 50, 400, 40, hwnd, (HMENU)ID_LABEL, NULL, NULL);

            CreateWindow("Static", charArray,
                         WS_VISIBLE | WS_CHILD | SS_NOTIFY,
                         20, 80,  400, 40,  hwnd, (HMENU)ID_LABEL_RESULT, NULL, NULL);
            resultado="";
            inOrden(a->raiz, resultado);

            charArray = resultado.c_str();

            CreateWindow("Static", "InOrden",
                         WS_VISIBLE | WS_CHILD | SS_NOTIFY,
                         20, 110,  400, 40,  hwnd, (HMENU)ID_LABEL, NULL, NULL);

            CreateWindow("Static", charArray,
                         WS_VISIBLE | WS_CHILD | SS_NOTIFY,
                         20, 140,  400, 40,  hwnd, (HMENU)ID_LABEL_RESULT, NULL, NULL);
                        inOrden(a->raiz, resultado);
            resultado="";
            postOrden(a->raiz, resultado);

            charArray = resultado.c_str();

            CreateWindow("Static", "PostOrden",
                         WS_VISIBLE | WS_CHILD | SS_NOTIFY,
                         20, 170,  400, 40,  hwnd, (HMENU)ID_LABEL, NULL, NULL);

            CreateWindow("Static", charArray,
                         WS_VISIBLE | WS_CHILD | SS_NOTIFY,
                         20, 200,  400, 40,  hwnd, (HMENU)ID_LABEL_RESULT, NULL, NULL);
        }
        break;
    }
        case WM_DESTROY: {
        hwndVentanaTerciaria = NULL;
        break;
    }
    default: {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    }

}
LRESULT CALLBACK ProcedimientoVentanaCuaternaria(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
        switch (msg) {
    case WM_CREATE: {
        CreateWindow("Static","Ingrese un numero : ",WS_VISIBLE | WS_CHILD |SS_NOTIFY,20 ,10,150,20,hwnd,(HMENU)ID_LABEL,NULL,NULL);
        textEdit=CreateWindow("EDIT",   // Predefined class; Unicode assumed
                NULL,         // No window title
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT| ES_NUMBER, // Styles
                170,         // x position
                10,         // y position
                200,        // Text box width
                25,        // Text box height
                hwnd,       // Parent window
                (HMENU) ID_TEXT,       // No menu.
                GetModuleHandle(NULL),
                NULL);
        CreateWindow("BUTTON", "Buscar",  WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,80, 50, 100, 30, hwnd,(HMENU)ID_BTNGUARDAR,NULL,NULL);


        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == ID_BTNGUARDAR) {
                char buffer[256];
                GetWindowText(textEdit, buffer, 256);
                cout<<buffer;
                dato = atoi(buffer);
                cout<<dato;


            if(busqueda(a->raiz, dato)== true){
            CreateWindow("Static","El elemento ha sido encontrado",WS_VISIBLE | WS_CHILD |SS_NOTIFY,20 ,100,150,80,hwnd,(HMENU)ID_LABEL,NULL,NULL);
            }else{
            CreateWindow("Static","No ha sido encontrado ",WS_VISIBLE | WS_CHILD |SS_NOTIFY,20 ,100,150,80,hwnd,(HMENU)ID_LABEL,NULL,NULL);
            }
        }
        break;
    }
    case WM_DESTROY: {
        hwndVentanaCuaternaria = NULL;
        break;
    }
    default: {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    }
    return 0;
}
LRESULT CALLBACK ProcedimientoVentanaQuinta(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
        switch (msg) {
    case WM_CREATE: {
        CreateWindow(
            "BUTTON",
            "Cerrar",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 50, 100, 30,
            hwnd,
            (HMENU)ID_BTNGUARDAR,
            NULL,
            NULL
        );

        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == ID_BTNGUARDAR) {
            DestroyWindow(hwnd);
        }
        break;
    }
    case WM_DESTROY: {
        hwndVentanaQuinta = NULL;
        break;
    }
    default: {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    }
    return 0;

}
LRESULT CALLBACK ProcedimientoVentanaSexta(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg) {
    case WM_CREATE: {
        CreateWindow("Static","Ingrese un numero : ",WS_VISIBLE | WS_CHILD |SS_NOTIFY,20 ,10,150,20,hwnd,(HMENU)ID_LABEL,NULL,NULL);
        textEdit=CreateWindow("EDIT",   // Predefined class; Unicode assumed
                NULL,         // No window title
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT| ES_NUMBER, // Styles
                170,         // x position
                10,         // y position
                200,        // Text box width
                25,        // Text box height
                hwnd,       // Parent window
                (HMENU) ID_TEXT,       // No menu.
                GetModuleHandle(NULL),
                NULL);
        CreateWindow("BUTTON", "Eliminar",  WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,80, 50, 100, 30, hwnd,(HMENU)ID_BTNGUARDAR,NULL,NULL);



        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == ID_BTNGUARDAR) {
                 char buffer[256];
                GetWindowText(textEdit, buffer, 256);
                cout<<buffer;
                dato = atoi(buffer);
                cout<<dato;

                eliminar(a->raiz,dato);
                                setbkcolor(0);
                cleardevice();
                int windowWidth = getmaxx();
                int windowHeight = getmaxy();
                dibujarArbol<Nodo>(a->raiz, windowWidth/2, 100, windowWidth/4, 0);
        }
        break;
    }
    case WM_DESTROY: {
        hwndVentanaSexta = NULL;
        break;
    }
    default: {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    }
    return 0;

}
