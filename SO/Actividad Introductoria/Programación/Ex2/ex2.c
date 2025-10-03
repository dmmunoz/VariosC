/*
 * Filename: ex2.c
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
    int fin = 1000;
    int sorteo[1000];
    int epico = 0;
    int raro = 0;
    int infrecuente = 0;
    int comun = 0;
    int contador = 0;
    for(int x=inicio; x<fin; x++)
    {
	    sorteo[x] = (rand() % (max - min + 1) + min);
    }
    for(int i=inicio; i<fin; i++)
    {
	for(int j=inicio; j<fin; j++)
	{
		if(i == sorteo[j]){
			contador++;
		}
	}
	if (contador<=1){
		epico++;
	}
	if (contador>1&&contador<15){
		raro++;
	}
	if (contador>=15&&contador<79){
		infrecuente++; 
	}
	if (contador>=79){
		comun++;
	}
    }	
    printf("Han dado %d premios epicos\n", epico);
    printf("Han dado %d premios raros\n", raro);
    printf("Han dado %d premios infrecuentes\n", infrecuente);
    printf("Han dado %d premios comunes\n", comun);
  
    return 0;
}

