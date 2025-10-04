/*
 * Filename: ex2.c
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
    int cromosFutbol = 0;
    int personajesRol = 0;
    int armas=0;
    int monstruos = 0;

    for(int i=inicio; i<fin; i++)
    {
	premio = rand() % (max - min);
	//Condición para que determine si está entre el 1 y el 10 (10%)
	if (premio<10){
		cromosFutbol++;
	}
	//Condición para que determine si está entre el 31 hacia el 11 (20%)
	else if(premio<31){
		personajesRol++;
	}
	//Condición para que determine si está entre el 61 y el 31 (30%)
	else if(premio<61){
		armas++; 
	}
	//Todos los demás serían monstruso que irían del 60 al 100 (40%)
	else {
		monstruos++;
	}
    }	
    printf("Han dado %d Cromos de futbol\n", cromosFutbol);
    printf("Han dado %d Personajes de juego de Rol\n", personajesRol);
    printf("Han dado %d Armas del juego corporativo\n", armas);
    printf("Han dado %d Monstruos de bolsillo\n", monstruos);
  
    return 0;
}


