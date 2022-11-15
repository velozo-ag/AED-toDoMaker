#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>
#include "colors.h"

typedef char tString[200];

typedef struct{
    tString titulo;
    tString descripcion;
}tDatos;

typedef struct{
    bool isChecked;
    bool esPadre;
    tDatos datos;
}tElemento;

tElemento crearElemento(int);
tElemento constructorElemento(int esPadre, int check, tString titulo, tString descripcion);

// Creador de elemento por teclado
tElemento crearElemento(int esPadre){

    tElemento nuevoElemento;

    nuevoElemento.isChecked = false;
    nuevoElemento.esPadre = false;
    
    printf(BG_WHITE BLACK);
    printf("\n Ingrese el titulo: ");
    printf(BG_BLACK WHITE " ");
    gets(nuevoElemento.datos.titulo);
    
    printf(BG_WHITE BLACK);
    printf("Ingrese la descripcion: ");
    printf(BG_BLACK WHITE " ");
    gets(nuevoElemento.datos.descripcion);
    
    if(esPadre == 1){
        nuevoElemento.esPadre = true;
    }
    
    return nuevoElemento;

}

// Constructor de elemento por parametros
tElemento constructorElemento(int esPadre, int check, tString titulo, tString descripcion){
    
    tElemento nuevoElemento;

    nuevoElemento.esPadre = esPadre;
    nuevoElemento.isChecked = check;

    strcpy(nuevoElemento.datos.titulo, titulo);
    strcpy(nuevoElemento.datos.descripcion, descripcion);

    return nuevoElemento;

}
