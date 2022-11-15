#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>
#include "colors.h"

// ------------------------ TAD estructuras y metodos de toDo, con sus respectivos tipos y elementos
#include "toDoStruct.h"

// ------------------------ Definicion de Variables
tLista * toDoList;
tElemento elementoAux;
FILE * archivo;

bool esPadre;

// Funciones de navegacion y verificacion de elementos
void navegar();
void opciones();
void selectElementPadre(tLista *);
void selectElementHijo(tHijo *);
void padreSeleccionado(tLista *, int, int);
void verificarHijosSeleccionados(tLista *);
bool verificacionEliminar(tString);

// Funciones para corte de control
void inicializarPrograma();
void leerRegistro();
void procesoCorte();
void principioCorte();
void finCorte();
void unElemento();
void unHijo();

// Guardado de archivos
void guardarArchivo();
void guardarPadres(tLista *);
void guardarHijos(tHijo *);

int main(){
    
    system("cls");

    inicializarLista(toDoList);
    inicializarPrograma();

    navegar();

    guardarArchivo();

    return 0;
    
}

void navegar(){

    int padreSelect = 1;
    int hijoSelect = 0;
    int dimension = dimensionLista(toDoList);
    int input;

    mostrarTodos(toDoList, padreSelect);
    opciones();

    while(1){   

        Sleep(10);

        input = tolower(getch());

        if(input == 119){ // W - Arriba

            if(padreSelect == 1){
                padreSelect = dimension;
            }else{
                padreSelect--;                
            }

        }
        
        if(input == 115){ // S - Abajo

            if(padreSelect == dimension){
                padreSelect = 1;
            }else{
                padreSelect++;
            }

        }

        if(input == 13){ // Enter - Check
            
            if(padreSelect == dimension){
                insertarNodo(&toDoList, crearElemento(1));
                dimension = dimensionLista(toDoList);
                padreSelect = 1;
            }else{
                selectElementPadre(buscarNodo(toDoList,padreSelect));
            }
            
        }

        if(input == 109){ // M - Modificar

            if(padreSelect != dimension){
                tLista * padreAux = buscarNodo(toDoList,padreSelect);
                padreAux->elemento = modificarElemento(padreAux->elemento);
            }

        }

        if(input == 97){ // A - Add hijo

            if(padreSelect != dimension){
                insertarHijo(buscarNodo(toDoList,padreSelect), crearElemento(0));
            }

        }

        if(input == 101){ // E - Ingreso a lista hijos

            hijoSelect = 1;
            padreSeleccionado(toDoList, padreSelect, hijoSelect);
            opciones();

            int dimHijo = dimensionHijo(buscarNodo(toDoList,padreSelect)->hijo);
            int inputHijo;

            while(1){

                Sleep(10);

                inputHijo = tolower(getch());
                
                if(inputHijo == 119){ // W - Arriba

                    if(hijoSelect == 1){
                        hijoSelect = dimHijo;
                    }else{
                        hijoSelect--;                
                    }

                    padreSeleccionado(toDoList, padreSelect, hijoSelect);
                    opciones();

                }

                if(inputHijo == 115){ // S - Abajo
                    
                    if(hijoSelect == dimHijo){
                        hijoSelect = 1;
                    }else{
                        hijoSelect++;
                    }

                    padreSeleccionado(toDoList, padreSelect, hijoSelect);
                    opciones();

                }
                
                if(inputHijo == 13){ // Enter - Seleccionar
                    
                    selectElementHijo(buscarHijo(buscarNodo(toDoList,padreSelect),hijoSelect));
                    verificarHijosSeleccionados(buscarNodo(toDoList,padreSelect));

                    padreSeleccionado(toDoList, padreSelect, hijoSelect);
                    
                    opciones();
                 
                }        

                if(inputHijo == 109){ // M - Modificar

                    tHijo * hijoAux = buscarHijo(buscarNodo(toDoList,padreSelect),hijoSelect);
                    hijoAux->elemento = modificarElemento(hijoAux->elemento);

                }

                if(inputHijo == 120){ // X - Salir hijo
                    padreSelect = 1;
                    mostrarTodos(toDoList, padreSelect);
                    opciones();
                    hijoSelect = 0;
                    break;
                }

            }

        }
        
        if(input == 100){ // D - Eliminar padre

            tLista * padreAux = buscarNodo(toDoList,padreSelect);

	        if(verificacionEliminar(padreAux->elemento.datos.titulo)){
	            eliminarPadre(&toDoList,padreSelect);    
	            dimension--;
	        }

            mostrarTodos(toDoList, padreSelect);

        }

        mostrarTodos(toDoList, padreSelect);
        opciones();

        if(input == 120){ // X - Terminar programa
            break;
        }

    }

}

void selectElementPadre(tLista * pTodoList){

    pTodoList->elemento.isChecked = !pTodoList->elemento.isChecked;
    tHijo * hijoAux;

    if(pTodoList->hijo != NULL){
        hijoAux = pTodoList->hijo;  
        if(pTodoList->elemento.isChecked){
            while(hijoAux != NULL){
                hijoAux->elemento.isChecked = true;
                hijoAux = hijoAux->siguiente;
            }
        }else{
            while(hijoAux != NULL){
                hijoAux->elemento.isChecked = false;
                hijoAux = hijoAux->siguiente;
            }
        }   
    }
}

void selectElementHijo(tHijo * pHijo){
    pHijo->elemento.isChecked = !pHijo->elemento.isChecked;
}

void verificarHijosSeleccionados(tLista * pTodoList){
    bool bandera = true;
    tHijo * hijoAux = pTodoList->hijo;

    while(hijoAux != NULL){
        if(!hijoAux->elemento.isChecked){
            bandera = false;
        }
        hijoAux = hijoAux->siguiente;
    }
    if(bandera){
        pTodoList->elemento.isChecked = true;
    }else{
        pTodoList->elemento.isChecked = false;
    }
}

// ------------------------ PROCESO CORTE DE CONTROL
void inicializarPrograma(){
    insertarNodo(&toDoList, constructorElemento(0,0,"Add new task",EP));
    archivo = fopen("TodoList-Elements.dat","rb");

    if(archivo != NULL){
        fread(&elementoAux, sizeof(tElemento), 1, archivo);
        procesoCorte();
    }

    fclose(archivo);

}

void procesoCorte(){

    while(!feof(archivo)){
        
        principioCorte();

        while(!feof(archivo) && esPadre == elementoAux.esPadre){
            unElemento();
            leerRegistro();
        }

        finCorte();
    }

}

void leerRegistro(){
    fread(&elementoAux, sizeof(tElemento), 1, archivo);
}

void principioCorte(){
    esPadre = elementoAux.esPadre;
}

void finCorte(){
    while((!feof(archivo)) && (elementoAux.esPadre == 0)){
        unHijo();
        leerRegistro();
    }
}

void unElemento(){
    insertarNodo(&toDoList,elementoAux);
}

void unHijo(){
    insertarHijo(buscarNodo(toDoList,1), elementoAux);
}

void guardarArchivo(){

    archivo = fopen("TodoList-Elements.dat","wb");

    guardarPadres(toDoList);

    fclose(archivo);

}

void guardarPadres(tLista * pPadre){

    tHijo * hijoAux;

    if(pPadre->siguiente != NULL){
        guardarPadres(pPadre->siguiente);
    }

    elementoAux = pPadre->elemento;

    // Compara si no es el elemento creador
    if(strcmp(elementoAux.datos.descripcion,EP)){
        fwrite(&elementoAux, sizeof(tElemento), 1, archivo);

        if(pPadre->hijo != NULL){
            guardarHijos(pPadre->hijo);
        }
    }
}

void guardarHijos(tHijo * pHijo){
    if(pHijo->siguiente != NULL){
        guardarHijos(pHijo->siguiente);
    }

    elementoAux = pHijo->elemento;
    fwrite(&elementoAux, sizeof(tElemento), 1, archivo);
}


// ------------------------ IMPRIMIR OPCIONES
void opciones(){

    printf(BG_WHITE BLACK " W ");
    printf(BG_BLACK WHITE "- Up     | ");
    printf(BG_WHITE BLACK " A ");
    printf(BG_BLACK WHITE "- AddSub | ");
    printf(BG_WHITE BLACK " Enter ");
    printf(BG_BLACK WHITE "- Check \n");

    printf(BG_WHITE BLACK " S ");
    printf(BG_BLACK WHITE "- Down   | ");
    printf(BG_WHITE BLACK " E ");
    printf(BG_BLACK WHITE "- NavSub | ");
    printf(BG_WHITE BLACK " X ");
    printf(BG_BLACK WHITE "- Exit   \n");

    printf(BG_WHITE BLACK " D ");
    printf(BG_BLACK WHITE "- Delete | ");
    printf(BG_WHITE BLACK " M ");
    printf(BG_BLACK WHITE "- Modificar \n");

}

bool verificacionEliminar(tString titulo){

    int op;
    printf(BG_WHITE BLACK "\nSeguro de eliminar %s? Y/n:", titulo);
    printf(BG_BLACK WHITE " - ");
    op = tolower(getch());

    if(op == 121){
        return true;
    }else{
        return false;
    }

}
