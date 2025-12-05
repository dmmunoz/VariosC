/*
 * Filename: ex3.c
 * Ejercicio 3
 * PEC 3
 * Asignatura Sistemas Operativos
 * Realizado por : Diego Manuel Muñoz Escañuela
 */

/*Incluyo todas las bibliotecas necesarias para el funcionamiento del programa */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creo un tipedef struct donde guardaré las colecciones con el nombre y la probabilidad
typedef struct {
    char nombre[65];
    int  probabilidad;
} Coleccion;

//Creo otro typedef Struct para guardar las rarezas con el nombre y la probabilidad
typedef struct {
    char nombre[65];
    int  probabilidad;
} Rareza;

//Empieza el programa principal. Por el argumento argv[1] introduciremos el nombre del
//fichero que nos entregan en el enunciado de la PEC3 probabilities1-1.txt o el probabilities2-1.txt
int main(int argc, char *argv[])
{
    //Declaro las variables necesarias para el programa	
    FILE *f;//Puntero que apunta al fichero que se abrirá
    int numeroColecciones, numeroRarezas; //Para almacenar el numero de Colecciones y Rarezas
    Coleccion colecciones[100]; //Donde almaceno array de colecciones
    Rareza rarezas[100]; //Array de rarezas
    int i, j; //Contadores para los bucles que recorrere para almacenar datos
    int sumaColecciones = 0; //Variable para calcular la suma de probabilidades Colecciones
    int sumaRarezas = 0; //Variable para calcular la suma de probabilidades de Rarezas


    // Comprobar que el usuario pasa un argumento, si no se introduce
    // el argv[1] es porque falta el parametro con el fichero que debemos leer
    // Si hay error informamos del error y finalizamos el programa
    if (argc != 2) {
        printf("Error: debes indicar el nombre del fichero en la ejecucion del programa.");
	printf("Ejemplo 1 : ./ex3 probabilities1-1.txt");
	printf("Ejemplo 2 : ./ex3 probabilities2-1.txt");
        return 1;
    }

    
    //Abrimos el fichero en modo lectura
    //Si hay error en la apertura avisamos del error y finalizamos el programa
    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error: no se puede abrir el fichero.\n");
        return 1;
    }

    // Leemos el  número de colecciones, si devuelve 1 la funcion fscanf es correcto
    // Siginifica que no hay error de EOF, tetxo inválido, etc..
    if (fscanf(f, "%d", &numeroColecciones) != 1) {
        printf("Error al leer el numero de colecciones.\n");
        fclose(f);
        return 1;
    }

    //Leeremos  las colecciones e iremos añadiendolas al array
    //En cada vuelta del for añadimos el nombre y la probabilidad
    //de coleccion
    //Al final de cada for sumamos la probabilidad. 
    //Se supone que al final dicha suam debe devolver 100
    for (i = 0; i < numeroColecciones; i++) {
        if (fscanf(f, "%s", colecciones[i].nombre) != 1) {
            printf("Error al leer el nombre de una coleccion.\n");
            fclose(f);
            return 1;
        }
        if (fscanf(f, "%d", &colecciones[i].probabilidad) != 1) {
            printf("Error al leer la probabilidad de una coleccion.\n");
            fclose(f);
            return 1;
        }

        sumaColecciones += colecciones[i].probabilidad;
    }

    // Leere el número de rarezas al igual que las colecciones
    // Si la funcion fscanf devuelve un 1 es que no hay error y todo sigue
    // sino cierra el programa avisando del error de lectura

    if (fscanf(f, "%d", &numeroRarezas) != 1) {
        printf("Error al leer el numero de rarezas.\n");
        fclose(f);
        return 1;
    }

    //Leeremos  las rarezas e iremos añadiendolas al array
    //En cada vuelta del for añadimos el nombre y la probabilidad
    //de rareza
    //Al final de cada for sumamos la probabilidad. 
    //Se supone que al final dicha suam debe devolver 100
    
    for (i = 0; i < numeroRarezas; i++) {
        if (fscanf(f, "%s", rarezas[i].nombre) != 1) {
            printf("Error al leer el nombre de una rareza.\n");
            fclose(f);
            return 1;
        }
        if (fscanf(f, "%d", &rarezas[i].probabilidad) != 1) {
            printf("Error al leer la probabilidad de una rareza.\n");
            fclose(f);
            return 1;
        }

        sumaRarezas += rarezas[i].probabilidad;
    }
    
    //Cierro el fichero ya que ya no lo necesito
    fclose(f);

    //Comprobaremos las  sumas de probabilidades que sean 100 sino damos el error y
    //Terminamos el programa
    if (sumaColecciones != 100 || sumaRarezas != 100) {
        printf("ERROR: las probabilidades no suman 100.\n");
        printf("Suma colecciones = %d\n", sumaColecciones);
        printf("Suma rarezas     = %d\n", sumaRarezas);
        return 1;
    }

    // Calcularemos la probabilidad
    // de combinacion de  colecciones y rarezas 
    // Con el primer bucle recorro el array de colecciones
    // Con el otro bucle recorro el array de rarezas
    // El valor de la probalidad combinada es la multiplicacion de cada una de 
    // las probabilidades en cada bucle dividido por 100. Como es un valor
    // de tipo real declaro como double la variable y la imprimo.
    double conjunta;
    printf("Probabilidades de la combinacion Coleccion y Rareza:\n");
    for (i = 0; i < numeroColecciones; i++) {
        for (j = 0; j < numeroRarezas; j++) {
            conjunta = (colecciones[i].probabilidad * rarezas[j].probabilidad) / 100.0;
            printf("%s + %s = %.2f%%\n",
                   colecciones[i].nombre,
                   rarezas[j].nombre,
                   conjunta);
        }
    }

    return 0;
}
