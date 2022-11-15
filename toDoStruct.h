#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>
#include "colors.h"
#define EP "431982561387653891"

// ------------------------ Inclusion de los tipo Elemento y sus funciones
#include "element.h"


// ------------------------ Definicion de tipos/estructuras
typedef struct nodoHijo{
    tElemento elemento;
    struct nodoHijo * siguiente;
}tHijo;

typedef struct nodo{
    tElemento elemento;
    struct nodo *siguiente;
    tHijo * hijo;
}tLista;

// ------------------------ Prototipado de metodos
void inicializarLista(tLista *);
int dimensionLista(tLista *);

// Metodos para los nodos 'principales' o 'padres'
void insertarPrimerNodo(tLista **, tElemento);
void insertarNodo(tLista **, tElemento);
void eliminarPadre(tLista **, int);
tLista * buscarNodo(tLista *,int);

// Metodos para los nodos 'hijos'
void insertarPrimerHijo(tLista *,tElemento);
void insertarHijo(tLista *,tElemento);
int dimensionHijo(tHijo *);
tHijo * buscarHijo(tLista *, int);
void eliminarHijos(tHijo **);

void mostrarTodos(tLista *, int);
void mostrarHijos(tLista *, int);
void padreSeleccionado(tLista * , int, int);
tElemento modificarElemento(tElemento);


// ------------------------ Definicion de Metodos
// Metodos genericos de Listas Enlazadas
void inicializarLista(tLista * pTodoList){
    pTodoList = NULL;
}

void insertarNodo(tLista** pTodoList, tElemento pElem){

    tLista * nuevoNodo = (tLista*) malloc(sizeof(tLista));
    
    nuevoNodo->elemento = pElem;
    nuevoNodo->siguiente = (*pTodoList);
    nuevoNodo->hijo = NULL;

    (*pTodoList) = nuevoNodo;

}

void insertarPrimerNodo(tLista ** pTodoList,tElemento pElem){

    tLista * nuevoNodo;

    nuevoNodo = (tLista*) malloc(sizeof(tLista));

    nuevoNodo->elemento = pElem;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->hijo = NULL;

    (*pTodoList) = nuevoNodo;

}

void insertarHijo(tLista * pPadre, tElemento pElem){

    if(pPadre->hijo == NULL){
        insertarPrimerHijo(pPadre, pElem);
        return;
    }

    tHijo * nuevoHijo = (tHijo*) malloc(sizeof(tHijo));

    nuevoHijo->elemento = pElem;
    nuevoHijo->siguiente = pPadre->hijo;
    
    pPadre->hijo = nuevoHijo;

}

void insertarPrimerHijo(tLista * pPadre, tElemento pElem){
    tHijo * nuevoHijo;

    nuevoHijo = (tHijo*) malloc(sizeof(tHijo));

    nuevoHijo->elemento = pElem;
    nuevoHijo->siguiente = NULL;

    pPadre->hijo = nuevoHijo;

    printf("a");

}

// Metodos para muestra de todos los elementos
void mostrarTodos(tLista * pTodoList, int cursor){

    tLista * aux = pTodoList;
    tElemento elemento;
    int cant = 1;

    system("cls");

    printf("------------- ToDo List -------------\n");

    while(aux != NULL){

        elemento = aux->elemento;

        if(cant == dimensionLista(pTodoList)){

            if(cant == cursor){
                printf(BG_BLACK BLUE "+ ");
                printf(BG_WHITE BLACK "  %s \t\n", elemento.datos.titulo);
            }else{
                printf(BG_BLACK BLUE "+ ");
                printf(BG_BLACK WHITE "%s \t\n", elemento.datos.titulo);
            }

        }else{

            if(cant == cursor){
                if(aux->elemento.isChecked){
                    printf(BG_BLACK GREEN "X ");
                    printf(BG_WHITE BLACK "  %s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
                }else{
                    printf(BG_BLACK CYAN "O ");
                    printf(BG_WHITE BLACK "  %s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
                }
            }else{
                if(aux->elemento.isChecked){
                    printf(BG_BLACK GREEN "X ");
                    printf(WHITE "%s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
                }else{
                    printf(BG_BLACK CYAN "O ");
                    printf(WHITE "%s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
                }
            }
        
            if(aux->hijo != NULL){
                mostrarHijos(aux, 0);
            }

        }

        printf("\n");

        cant++;
        aux = aux->siguiente;

        printf(BG_BLACK WHITE);

    }

}

void mostrarHijos(tLista * pPadre, int hijoSelect){

    int cant = 1;

    tHijo * aux = pPadre->hijo;
    tElemento elemento;

    while(aux != NULL){
    
        elemento = aux->elemento;

        if(cant == hijoSelect){
            if(aux->elemento.isChecked){
                printf(BG_BLACK GREEN "  X ");
                printf(BG_WHITE BLACK "  %s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
            }else{
                printf(BG_BLACK CYAN "  O ");
                printf(BG_WHITE BLACK "  %s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
            }
        }else{
            if(aux->elemento.isChecked){
                printf(BG_BLACK GREEN "  X ");
                printf(WHITE "%s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
            }else{
                printf(BG_BLACK CYAN "  O ");
                printf(WHITE "%s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
            }
        }

        cant++;
    
        aux = aux->siguiente;

    }

}

void padreSeleccionado(tLista * pTodoList,int pPadrePos, int hijoSelect){

    tLista * aux = pTodoList;
    tElemento elemento;
    int cant = 1;

    system("cls");

    printf("---------- ToDo List ----------\n");

    while(aux != NULL){

        elemento = aux->elemento;

        if(cant != dimensionLista(pTodoList)){ // IMRIMIR TODOS LOS ELEMENTOS EXCEPTO ELEMENTO MADRE

            if(cant == pPadrePos){

                if(aux->elemento.isChecked){
                    printf(BG_BLACK GREEN "X ");
                    printf(BG_WHITE BLACK "  %s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
                }else{
                    printf(BG_BLACK CYAN "O ");
                    printf(BG_WHITE BLACK "  %s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
                }
                
                mostrarHijos(aux, hijoSelect);

            }else{

                if(aux->elemento.isChecked){
                    printf(BG_BLACK GREEN "X ");
                    printf(WHITE "%s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
                }else{
                    printf(BG_BLACK CYAN "O ");
                    printf(WHITE "%s | %s \t\n", elemento.datos.titulo, elemento.datos.descripcion);
                }

                mostrarHijos(aux, 0);

            }
        
        }else{ // IMPRIMIR ELEMENTO MADRE -> CREADOR DE ELEMENTOS

            printf(BG_BLACK BLUE "+ ");
            printf(BG_BLACK WHITE "%s \t\n", elemento.datos.titulo);

        }

        printf("\n");

        cant++;
        aux = aux->siguiente;

        printf(BG_BLACK WHITE);

    }

}

// Metodos para Hallar nodos K
tLista * buscarNodo(tLista * pLista, int k){

    int i;
    tLista * aux = pLista;

    for(i = 1; i < k; i++){
        aux = aux->siguiente;
    }

    return aux;

}

tHijo * buscarHijo(tLista * pPadre, int k){

    int i;
    tHijo * aux = pPadre->hijo;

    for(i = 1; i < k; i++){
        aux = aux->siguiente;
    }

    return aux;

}

// Metodos para Hallar la dimension de las listas
int dimensionLista(tLista * pTodoList){

    tLista * aux = pTodoList;
    int cont = 0;

    while(aux != NULL){
        cont++;
        aux = aux->siguiente;
    }

    return cont;

}

int dimensionHijo(tHijo * pHijo){

    tHijo * aux = pHijo;
    int cont = 0;

    while(aux != NULL){
        cont++;
        aux = aux->siguiente;
    }

    return cont;

}

// Metodos de eliminacion
void eliminarPadre(tLista ** pTodoList, int posPadre){
    
    tLista * nodoAEliminar;

    if(posPadre == 1){
     
        nodoAEliminar = (*pTodoList);
        (*pTodoList) = (*pTodoList)->siguiente;

    }else{

        tLista * aux;
        aux = (*pTodoList);
        int i;

        for(i = 1; i < posPadre -1; i++){
            aux = aux->siguiente;
        }

        nodoAEliminar = aux->siguiente;
        aux->siguiente = nodoAEliminar->siguiente;

    }

    free(nodoAEliminar);
    nodoAEliminar = NULL;

}

void eliminarHijos(tHijo ** pHijo){

    if((*pHijo)->siguiente != NULL){
        eliminarHijos(&(*pHijo)->siguiente);
    }
    free(*pHijo);

    printf("Hijo eliminado \n");

}

tElemento modificarElemento(tElemento pElemento){

    printf(BG_WHITE BLACK);
    printf("\n Ingrese el Nuevo Titulo: ");
    printf(BG_BLACK WHITE " ");
    gets(pElemento.datos.titulo);
    
    printf(BG_WHITE BLACK);
    printf("Ingrese la Nueva Descripcion: ");
    printf(BG_BLACK WHITE " ");
    gets(pElemento.datos.descripcion);

    return pElemento;

}