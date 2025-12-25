/*
 * Filename: ex3.c
 * Ejercicio 3
 * PEC 4
 * Asignatura Sistemas Operativos
 * Realizado por : Diego Manuel Muñoz Escañuela
 */

/*Incluyo todas las bibliotecas necesarias para el funcionamiento del programa */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


// Funcion para elegir de manera random la coleccion con diferente probabilidad
const char *elegir_coleccion() {
    int r = rand() % 100;

    if (r < 10)
        return "Cromos de Futbol";
    else if (r < 31)
        return "Personajes de Rol";
    else if (r < 61)
        return "Armas";
    else
        return "Monstruos";
}



// Funcion para elegir de manera random la rareza con diferente probabilidad
const char *elegir_rareza() {
    int r = rand() % 100;

    if (r ==1)
        return "Epico";
    else if (r < 6)
        return "Raro";
    else if (r < 21)
        return "No Comun";
    else
        return "Comun";
}



//Empieza el programa principal.
//argv[1] será el numero de premios que queremos generar.
int main(int argc, char *argv[]) {
    int premios;
    pid_t pid;

    //Si no introduces el parámetro al ejecutar el programa lanzará el error
    if (argc != 2) {
        printf("Error!!!\nDebe introducir en la ejecucion el numero de premios que desea\n");
        printf("Por ejemplo: ./ex3 4");
        return 1;
    }

    //Casting para convertir el parametro de premios en un entero
    premios = atoi(argv[1]);


    //Bucle principal en el que irá creando procesos por cada premio , eligiendo e imprimiendo por consola
    for (int i = 0; i < premios; i++) {
        pid = fork();

        if (pid < 0) {
            printf("ERROR\n No se ha podido crear el proceso \n");
            exit(EXIT_FAILURE);
        }

        // Creacion del un proceso hijo
        if (pid == 0) {
            //Generacion de una semilla diferente en la que le sumo el pid de cada fork 
            //asi me aseguro que la semilla siempre es diferente
            srand(time(NULL) + getpid());

            const char *coleccion = elegir_coleccion();
            const char *rareza = elegir_rareza();

            // ID único del premio
            int premio_id = getpid();

            //Imprimo el premio que me toca
            printf("Premio ID %d -> Coleccion: %s | Rareza: %s\n",
                   premio_id, coleccion, rareza);

            exit(0);
        }
    }

    // El proceso padre espera la finalizacion de todos los procesos hijo creados
    for (int i = 0; i < premios; i++) {
        wait(NULL);
    }

    return 0;
}
