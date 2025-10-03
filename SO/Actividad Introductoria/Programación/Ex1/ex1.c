/*
 * Filename: ex1.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int min = 1;
    int max = 100;
    int inicio = 0;
    int fin = 999;
    int numeros[1000];
    int contador;
    for(int x=inicio; x < fin; x++)
    {
	    numeros[x]= (rand() % (max - min + 1) + min);
	    //printf("%d\n", numeros[x]);
    }
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

