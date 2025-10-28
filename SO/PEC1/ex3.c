/*
 * Filename: ex3.c
 * Ejercicio 3
 * PEC 1
 * Asignatura Sistemas Operativos
 * Realizado por : Diego Manuel Muñoz Escañuela
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Definición de los estados posibles
typedef enum { READY=0, RUN=1, BLOCKED=2 } Estado;


int main(int argc, char* argv[])
{
    //Crea el estado inicial del tipo Estado y lo inicio en READY
    Estado estado = READY;

    int paso = 0;
    int opcion;

    //Inicio de la semilla para aleatorios
    srand(time(NULL)); 

    //Impresion en pantalla del inicio del programa
    printf("Simulador de estados Ready / Run / Blocked\n");
    printf("Finaliza solo si, en RUN, se elige destruir el proceso.\n\n");
    printf("--------------------------------------------------------------\n");
    printf("--------------------------------------------------------------\n");
    printf("--------------------------------------------------------------\n");


    //Inicio del blucle principal
    while (true) {
	//Al principio del bucle siempre imprime el numero de iteración y el estado en el que está
	//Este estado vendrá dado de manera aleatoria
        printf("[Iteracion %d] Estado actual: ", paso++);

        // Mostrar el nombre del estado
        if (estado == READY)
            printf("READY\n");
        else if (estado == RUN)
            printf("RUN\n");
        else
            printf("BLOCKED\n");

        // Decisión aleatoria según el estado actual
	// Como el estado inicial esta definido en READY en el primer bucle luego podrá ser 
	// otro estado
	// iniciará eligiendo de manera aleatoria un numero random para la opcion
	// Si es 1 pasa a el estado a RUN sino seguirá en READY y volvera a hacer una 
	// iteración el bucle.
	
        if (estado == READY) {
            opcion = rand() % 3;  // 0, 1 o 2
            if (opcion == 1) {
                printf("Evento: El proceso ocupa CPU → READY → RUN\n");
                estado = RUN;
            } else {
                printf("Permanece en READY (esperando CPU)\n");
            }
	
        //Si entra en la condición que está en RUN vuelve a buscar una opción 
	//en este caso del 0 a 3. La 3 será la unica que podrá finalizar el programa
	//Si la opción vuelve a ser 1 el estado vuelve a estar en READY
	//Si la opción es 2 pasa a estar en BLOCKED
	//Si la opción sale 4 finaliza el programa
	    
        } else if (estado == RUN) {
            opcion = rand() % 4;  // valores 0..3
            if (opcion == 1) {
                printf("Evento: El proceso pierde CPU → RUN → READY\n");
                estado = READY;
            } else if (opcion == 2) {
                printf("Evento: Llamada sistema bloqueante → RUN → BLOCKED\n");
                estado = BLOCKED;
	//Si la opción que es igual a 3 termina el programa
            } else if (opcion == 3) {
                printf("Evento: Destruccion del  proceso → RUN → FINAL\n");
                break;  // termina el programa
            } else {
                printf("Permanece en RUN (sigue ejecutando)\n");
            }


        //Estado BLOCKED 
        } else { 
            opcion = rand() % 3;  // 0, 1 o 2
            if (opcion == 2) {
                printf("Evento: Finalizacion de una llamada al sistema bloqueante  → BLOCKED → READY\n");
                estado = READY;
            } else {
                printf("Permanece en BLOCKED (esperando IO)\n");
            }
        }

        printf("\n");
    }

    printf("Fin del programa.\n");
    return 0;
}
 
