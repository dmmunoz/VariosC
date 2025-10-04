/*
 * Filename: ex2.c
 * Ejercicio 2
 * Realizado por : Diego Manuel Muñoz Escañuela
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    //Inicio de semilla para generar numero random
    srand(time(NULL));
    //Variables para el intervalo de numeros del 1 al 100 para el sorteo
    int min = 1;
    int max = 100;
    //Variables para el numero de sorteos que se harán
    int inicio = 0;
    int fin = 1000;
    //Variable para almacenar el premio  
    int premio;
    //Variables para almacenar la cantidad de premios que podrán salir
    int epico = 0;
    int raro = 0;
    int infrecuente=0;
    int comun = 0;

    for(int i=inicio; i<fin; i++)
    {
	//Genero un numero random que iría del 1 al 100 por ello el random primero hace 99 y suma 1
	premio = rand() % (max - min) + min;
	//Condición para que si es igual a 1 (1%) sume dicho premio
	if (premio==1){
		epico++;
	}
	//Condiciṕn para que si sale de 6 al 1 (5%)
	else if(premio<=6){
		raro++;
	}
	//Condición por si sale del 21 al 6 (15%)
	else if(premio<=21){
		infrecuente++; 
	}
	//Resto de los premios serían comunes del 22 al 100 (79%) 
	else {
		comun++;
	}
    }	
    printf("Han dado %d premios epicos\n", epico);
    printf("Han dado %d premios raros\n", raro);
    printf("Han dado %d premios infrecuentes\n", infrecuente);
    printf("Han dado %d premios comunes\n", comun);
  
    return 0;
}

