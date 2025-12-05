/*
 * Filename: ex4.c
 * Ejercicio 4
 * PEC 3
 * Asignatura Sistemas Operativos
 * Realizado por : Diego Manuel Muñoz Escañuela
 */

/*Incluyo todas las bibliotecas necesarias para el funcionamiento del programa */

#include <stdio.h>   
#include <stdlib.h>
#include <string.h>
#include <time.h>    // Para inicializar el generador de numeros aleatorios

//Creo un typedef struct donde guardaré las colecciones con el nombre y la probabilidad
typedef struct {
    char nombre[65];
    int  probabilidad;
} Coleccion;

//Creo otro typedef struct para guardar las rarezas con el nombre y la probabilidad
typedef struct {
    char nombre[65];
    int  probabilidad;
} Rareza;

/*
 * Funcion que devuelve el indice de una coleccion elegida aleatoriamente
 * segun sus probabilidades.
 * Recibe el array de colecciones y el numero total de colecciones.
 * Genera un numero aleatorio entre 0 y 99, recorre las colecciones
 * acumulando probabilidades hasta que el numero aleatorio cae dentro
 * de uno de los intervalos.
 */
int elegirIndiceColeccion(Coleccion colecciones[], int numeroColecciones)
{
    int numeroAleatorio;
    int acumulador = 0;
    int i;

    //Genero un numero aleatorio entre 0 y 99
    numeroAleatorio = rand() % 100;

    //Voy sumando las probabilidades hasta que el numeroAleatorio
    //queda dentro de uno de los rangos
    for (i = 0; i < numeroColecciones; i++) {
        acumulador = acumulador + colecciones[i].probabilidad;
        if (numeroAleatorio < acumulador) {
            return i; //Devuelvo el indice de la coleccion elegida
        }
    }

    //Por seguridad, si algo falla devolvemos la ultima coleccion
    printf("Algo ha fallado en la función devuelvo la última colección");
    return numeroColecciones - 1;
}

/*
 * Funcion que devuelve el indice de una rareza elegida aleatoriamente
 * segun sus probabilidades.
 * Es igual que la funcion anterior pero trabajando con el array de rarezas.
 */
int elegirIndiceRareza(Rareza rarezas[], int numeroRarezas)
{
    int numeroAleatorio;
    int acumulador = 0;
    int i;
    
    //Genero un numero aleatorio entre 0 y 99
    numeroAleatorio = rand() % 100;
    
    //Voy sumando las probabilidades hasta que el numeroAleatorio
    //queda dentro de uno de los rangos
    for (i = 0; i < numeroRarezas; i++) {
        acumulador = acumulador + rarezas[i].probabilidad;
        if (numeroAleatorio < acumulador) {
            return i; //Devuelvo el indice de la rareza elegida
        }
    }
    //Por seguridad, si algo falla devolvemos la ultima rareza
    printf("Algo ha fallado en la función devuelvo la última rareza");
    return numeroRarezas - 1;
}

//Empieza el programa principal.
//argv[1] será el fichero de probabilidades (probabilities2-1.txt)
//argv[2] será el numero de premios que queremos generar.
int main(int argc, char *argv[])
{
    //Declaro las variables necesarias para el programa
    FILE *f; //Puntero al fichero de probabilidades
    FILE *ficheroLog;            //Puntero al fichero de registro (logfile)
    int numeroColecciones, numeroRarezas; //Para almacenar el numero de Colecciones y Rarezas
    Coleccion colecciones[100]; //Array donde almaceno las colecciones
    Rareza rarezas[100];        //Array donde almaceno las rarezas
    int i;                      //Contador para bucles
    int sumaColecciones = 0;    //Variable para calcular la suma de probabilidades de Colecciones
    int sumaRarezas = 0;        //Variable para calcular la suma de probabilidades de Rarezas
    int numeroPremios;          //Numero de premios que queremos simular
    int indiceColeccion;        //Indice de la coleccion elegida aleatoriamente
    int indiceRareza;           //Indice de la rareza elegida aleatoriamente
    double probabilidadConjunta;//Probabilidad conjunta de coleccion y rareza

    // Comprobar que el usuario pasa los argumentos necesarios,
    // en total deben ser 3: ./ex4 fichero_probabilidades numero_premios
    if (argc != 3) {
        printf("Error: debes indicar el nombre del fichero y el numero de premios en la ejecucion del programa.\n");
        printf("Ejemplo : ./ex4 probabilities2-1.txt 10\n");
        return 1;
    }

    //Convertimos el argumento argv[2] (cadena) a entero para obtener el numero de premios
    numeroPremios = atoi(argv[2]);
    if (numeroPremios <= 0) {
        printf("Error: el numero de premios debe ser mayor que 0.\n");
        return 1;
    }

    //Abrimos el fichero de probabilidades en modo lectura
    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error: no se puede abrir el fichero de probabilidades.\n");
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

    //Comprobamos que las sumas de probabilidades de colecciones y rarezas son 100
    //Si alguna no es 100 informamos del error y terminamos el programa
    if (sumaColecciones != 100 || sumaRarezas != 100) {
        printf("ERROR: las probabilidades no suman 100.\n");
        printf("Suma colecciones = %d\n", sumaColecciones);
        printf("Suma rarezas     = %d\n", sumaRarezas);
        return 1;
    }

    //Abrimos el fichero de registro (logfile) en modo append.
    //De esta forma no se pierde el contenido anterior, solo se añaden nuevas lineas al final.
    ficheroLog = fopen("logfile.txt", "a");
    if (ficheroLog == NULL) {
        printf("Error: no se puede abrir el fichero de registro logfile.txt.\n");
        return 1;
    }

    //Inicializamos el generador de numeros aleatorios con la hora actual. La semilla
    //para que en cada ejecucion los resultados sean diferentes.
    srand((unsigned int)time(NULL));

    //Bucle principal: repetimos el proceso tantas veces como premios queremos generar
    for (i = 0; i < numeroPremios; i++) {

        //Elegimos aleatoriamente una coleccion segun sus probabilidades
        indiceColeccion = elegirIndiceColeccion(colecciones, numeroColecciones);

        //Elegimos aleatoriamente una rareza segun sus probabilidades
        indiceRareza = elegirIndiceRareza(rarezas, numeroRarezas);

        //Calculamos la probabilidad conjunta de la coleccion y la rareza elegidas
        probabilidadConjunta = (colecciones[indiceColeccion].probabilidad *
                                rarezas[indiceRareza].probabilidad) / 100.0;

        //Informamos por pantalla al usuario del premio obtenido
        printf("Premio %d:\n", i + 1);
        printf("  Coleccion: %s (prob %d%%)\n",
               colecciones[indiceColeccion].nombre,
               colecciones[indiceColeccion].probabilidad);
        printf("  Rareza   : %s (prob %d%%)\n",
               rarezas[indiceRareza].nombre,
               rarezas[indiceRareza].probabilidad);
        printf("  Probabilidad conjunta: %.2f%%\n\n", probabilidadConjunta);

        //Añadimos una linea al fichero de registro con los detalles del premio
        fprintf(ficheroLog,
                "Premio %d: Coleccion=%s (prob %d%%), Rareza=%s (prob %d%%), Probabilidad conjunta=%.2f%%\n",
                i + 1,
                colecciones[indiceColeccion].nombre,
                colecciones[indiceColeccion].probabilidad,
                rarezas[indiceRareza].nombre,
                rarezas[indiceRareza].probabilidad,
                probabilidadConjunta);
    }

    //Cerramos el fichero de registro
    fclose(ficheroLog);

    //Finalizamos el programa correctamente
    return 0;
}
