/*
 * Filename: ex4.c
 * Ejercicio 4
 * PEC 4
 * Asignatura Sistemas Operativos
 * Realizado por : Diego Manuel Muñoz Escañuela
 * Para compilar ahora : gcc ex4.c -o ex4 -pthread
 */

/* Incluyo todas las bibliotecas necesarias para el funcionamiento del programa */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>    
#include <time.h>
#include <unistd.h>


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

    if (r == 1)
        return "Epico";
    else if (r < 6)
        return "Raro";
    else if (r < 21)
        return "No Comun";
    else
        return "Comun";
}


// Funcion que que  ejecuta cada hilo
// Es el codigo que antes ejecutaba el proceso hijo que ahora pasaremos por
// parametros en la funcion pthread_create del main
void *dar_premio(void *arg) {

    int id_premio = *(int *)arg;

    // Generacion de una semilla diferente para cada hilo
    // (equivalente al srand del proceso hijo)
    srand(time(NULL) + id_premio);

    const char *coleccion = elegir_coleccion();
    const char *rareza = elegir_rareza();

    // Imprimo el premio que me toca
    printf("Premio ID %d -> Coleccion: %s | Rareza: %s\n",
           id_premio, coleccion, rareza);

    return NULL;
}



// Empieza el programa principal.
// argv[1] será el numero de premios que queremos generar.
int main(int argc, char *argv[]) {

    int premios;

    // Si no introduces el parámetro al ejecutar el programa lanzará el error
    if (argc != 2) {
        printf("Error!!!\nDebe introducir en la ejecucion el numero de premios que desea\n");
        printf("Por ejemplo: ./ex4 4\n");
        return 1;
    }

    // Casting para convertir el parametro de premios en un entero
    premios = atoi(argv[1]);

    //Variable de arrays de  hilos
    pthread_t hilos[premios];
    int ids[premios];

    // Bucle principal en el que irá creando hilos por cada premio

    for (int i = 0; i < premios; i++) {

        ids[i] = i + 1;   // identificador por cada premio

        //Llamada a la función que crea los premios en hilos diferentes.
        if (pthread_create(&hilos[i], NULL, dar_premio, &ids[i]) != 0) {
            printf("ERROR\n No se ha podido crear el hilo \n");
            return 1;
        }
    }

    // El hilo principal espera la finalizacion de todos los hilos creados
    // es equivalente al wait en procesos
    for (int i = 0; i < premios; i++) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}
