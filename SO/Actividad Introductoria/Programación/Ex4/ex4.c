/*
 * Filename: ex4.c
 * Ejercicio 4
 * Realizado por : Diego Manuel Muñoz Escañuela
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//Con el parametro de entrada argc comprobamos  se hayan  introducido los 8 parametros
//EPIC RARE UNCOMMON COMMON CARDS CHARACTERS WEAPONS POKEMONS
int main(int argc, char* argv[])
{
    //Comprueba que los parámetros de entradas sean 9 el primer parametro es ex4 con lo que ese lo ignoramos
    if (argc != 9){
         printf("----------------------------------------------------------------\n");
         printf("------------Error faltan parametros de entrada------------------\n");
	 printf("--Son 8 parametros en dos grupos que cada grupo debe sumar 100--\n");
	 printf("--------Ejemplo llamada : ./ex4 25 25 25 25 10 20 30 40---------\n");
         printf("----------------------------------------------------------------\n");
         return 0;
    }

    //Comprueba que los paramentros de entradas sean números, no pueden ser letras
    for (int x=1; x==9; x++)
	{
	 if(!isdigit(argv[x]))
	 {
	    printf("----------------------------------------------------------------\n");
            printf("------------Error en los parametros de entrada------------------\n");
            printf("--------------Son 8 parametros , solo números ------------------\n");
	    printf("--Son 8 parametros en dos grupos que cada grupo debe sumar 100--\n");
            printf("--------Ejemplo llamada : ./ex4 25 25 25 25 10 20 30 40---------\n");
            printf("----------------------------------------------------------------\n");
            
	    return 0;
	 }
    }

    //Comprueba que los dos grupos sumen 100 cada uno, sino sale del programa con un error
    int suma1 = atoi(argv[1]) + atoi(argv[2]) + atoi(argv[3]) + atoi(argv[4]);  
    int suma2 = atoi(argv[5]) + atoi(argv[6]) + atoi(argv[7]) + atoi(argv[8]);

    if(suma1 !=100 || suma2 !=100)
         {
            printf("----------------------------------------------------------------\n");
            printf("------------Error en los parametros de entrada------------------\n");
            printf("--Son 8 parametros en dos grupos que cada grupo debe sumar 100--\n");
            printf("--------Ejemplo llamada : ./ex4 25 25 25 25 10 20 30 40---------\n");
            printf("----------------------------------------------------------------\n");
           
	    return 0;
         }
  
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
    int epic = 0;
    int rare = 0;
    int uncommon=0;
    int common = 0;
    int cards = 0;
    int characters = 0;
    int weapons = 0;
    int pokemons = 0;

    for(int i=inicio; i<fin; i++)
    {
	premio = rand() % (max - min);
	//Condición para epic para que determine si está en 1 (1%)
	if (premio==1){
		epic++;
	}
	//Condición para rare para que determine si está entre el 2 y el 6 (5%)
	else if(premio<=6){
		rare++;
	}
	//Condición para uncommon para que determine si está entre el 7 hacia el 21 (20%)
	else if(premio<=21){
		uncommon++;
	}
	//Todos los demás serían common que irían del 22 al 100 (79%)
	else {
		common++;
	}
    }	
    printf("Han dado %d premios EPIC\n", epic);
    printf("Han dado %d premios RARE\n", rare);
    printf("Han dado %d premios UNCOMMON\n", uncommon);
    printf("Han dado %d premios COMMON\n", common);
   
    for(int j=inicio; j<fin; j++)
    {
        premio = rand() % (max - min);
        //Condición para cards para que determine si está en 10 o menos (10%)
        if (premio<=10){
                cards++;
        }
        //Condición para characters para que determine si está entre el 11 y el 31 (20%)
        else if(premio<=31){
                characters++;
        }
        //Condición para weapons para que determine si está entre el 32 hacia el 61 (20%)
        else if(premio<=61){
                weapons++;
        }
        //Todos los demás serían pokemons que irían del 61 al 100 (40%)
        else {
                pokemons++;
        }
    }
    printf("Han dado %d premios CARDS\n", epic);
    printf("Han dado %d premios CHARACTERS\n", rare);
    printf("Han dado %d premios WEAPONS\n", uncommon);
    printf("Han dado %d premios POKEMONS\n", common);

    return 0;
}


