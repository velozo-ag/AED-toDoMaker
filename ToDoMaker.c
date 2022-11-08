#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

// Definicion de tipos
typedef char tString[200];

typedef struct{
    int id;
    bool esPadre;
    bool isChecked;
    tString titulo;
    tString descripcion;
}tElemento;

typedef struct nodo{
    tElemento elemento;
    struct nodo *siguiente;
    struct nodo *hijo;
}tLista;

// Lista Enlazada
tLista * toDoList;

// Prototipos
void inicializarLista();
tElemento crearElemento(int);

void insertarPrimerNodo(tElemento);
void insertarNodo(tElemento);

tLista * buscarNodo(tLista*,int);

void insertarPrimerHijo(tLista *,tElemento);
void insertarHijo(tLista*,tElemento);

void mostrar();
void mostrarHijos(tLista*);

int main()
{

    inicializarLista();
    insertarNodo(crearElemento(1));
    insertarNodo(crearElemento(1));
    insertarNodo(crearElemento(1));
    mostrar();

    insertarHijo(buscarNodo(toDoList,2),crearElemento(0));
    insertarHijo(buscarNodo(toDoList,2),crearElemento(0));
    insertarHijo(buscarNodo(toDoList,2),crearElemento(0));

    mostrar();

    return 0;
}


void inicializarLista(){
    toDoList = NULL;
}

tElemento crearElemento(int esPadre){
    tElemento nuevoElemento;

    if(esPadre == 1){
        nuevoElemento.esPadre = true;
    }else{
        nuevoElemento.esPadre = false;
    }
    
    printf("Ingrese el titulo: ");
    gets(nuevoElemento.titulo);
    printf("Ingrese la descripcion: ");
    gets(nuevoElemento.descripcion);
    nuevoElemento.isChecked = false;

    return nuevoElemento;
}

void insertarPrimerNodo(tElemento elem){

    tLista * nuevoNodo;

    nuevoNodo = (tLista*) malloc(sizeof(tLista));

    nuevoNodo->elemento = elem;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->hijo = NULL;

    toDoList = nuevoNodo;

}

void insertarNodo(tElemento elem){

    if(toDoList==NULL){
        insertarPrimerNodo(elem);
        return;
    }

    tLista * nuevoNodo = (tLista*) malloc(sizeof(tLista));
    tLista * aux = toDoList;
    
    while(aux->siguiente != NULL){
        aux = aux->siguiente;
    }

    nuevoNodo->elemento = elem;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->hijo = NULL;

    aux->siguiente = nuevoNodo;

}

void insertarHijo(tLista * padre, tElemento elem){

    if(padre->hijo == NULL){
        insertarPrimerHijo(padre,elem);
        return;
    }

    tLista * nuevoHijo = (tLista*) malloc(sizeof(tLista));
    tLista * aux = padre->hijo;
    
    while(aux->siguiente != NULL){
        aux = aux->siguiente;
    }

    nuevoHijo->elemento = elem;
    nuevoHijo->siguiente = NULL;
    
    aux->siguiente = nuevoHijo;

}

void insertarPrimerHijo(tLista* padre, tElemento elem){
    tLista * nuevoHijo;

    nuevoHijo = (tLista*) malloc(sizeof(tLista));

    nuevoHijo->elemento = elem;
    nuevoHijo->siguiente = NULL;
    nuevoHijo->hijo = NULL;

    padre->hijo = nuevoHijo;
}

void mostrar(){

    tLista * aux = toDoList;
    tElemento elemento = aux->elemento;

    printf("\n\n---------- Nashe ----------\n");

    while(aux != NULL){
        printf("%s, %s\n", elemento.titulo, elemento.descripcion);
        
        if(aux->hijo != NULL){
            mostrarHijos(aux);
        }

        aux = aux->siguiente;
        
        if(aux != NULL){
            elemento = aux->elemento;
        }

    }

}

void mostrarHijos(tLista * padre){

    tLista * aux = padre->hijo;
    tElemento elemento = aux->elemento;

    while(aux != NULL){
        printf("\t%s, %s\n", elemento.titulo, elemento.descripcion);
        
        aux = aux->siguiente;
        
        if(aux != NULL){
            elemento = aux->elemento;
        }
    }

}

tLista * buscarNodo(tLista * lista, int k){

    int i;
    tLista * aux = lista;

    for(i = 1; i < k; i++){
        aux = aux->siguiente;
    }

    return aux;

}
