/*
 * Filename: ex1.c
 * Ejercicio 1
 * Realizado por : Diego Manuel Muñoz Escañuela
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    //Genero la semilla para que pueda ser diferente siempre el numero random
    srand(time(NULL));
    //Variables que determina que iría desde un numero 1 al 100 
    int min = 1;
    int max = 100;
    //Variables que serían las casillas donde almacenaré en un array los numeros para analizar como se repiten
    int inicio = 0;
    int fin = 999;
    //Array donde almacenaré los 1000 sorteos
    int numeros[1000];
    //Variable para contador de los bucles.
    int contador;

    //Inicio de un bucle para almacenar todos los sorteos en el array
    for(int x=inicio; x < fin; x++)
    {
	    numeros[x]= (rand() % (max - min + 1) + min);
	    //printf("%d\n", numeros[x]);
    }

    //Analizo mediante dos bucles for si los numeros de los array se repiten. Cojo uno y lo compara con todos
    //Cojo el siguiente y lo comparo con todos menos con él
    //Asi sucesivamente hasta que se acaba el array
    //Si se repite voy sumando contador y al final de cada comparación imprimo las veces que se ha repetido
    for(int i=min; i<max; i++)
    {
	  contador = 0;
	  for(int j=inicio; j<fin; j++)
	  {
		 if(i == numeros[j]){
			 contador++;
		 }
	  }
	  printf("El numero %d se ha repetido %d veces\n", numeros[i], contador); 
    }	  

    return 0;
}

