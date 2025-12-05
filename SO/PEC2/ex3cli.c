/*
 * Filename: ex3cli.c
 * Ejercicio 3
 * PEC 2
 * Asignatura Sistemas Operativos
 * Realizado por : Diego Manuel Muñoz Escañuela
 */

/*Incluyo todas las bibliotecas necesarias para el funcionamiento del programa
 * en este caso trabajaremos con numeros Random, con Socket, con IP, con tiempo del sistema, ...)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//Empiezo con la creación de los tipos de datos que iré necesitando y algunas funciones

//Tipo de  datos que enviaremos al servidor. En este caso la colección y rareza para que 
//procese y nos devuelva por cada una de ellas un premio exacto
struct Peticion {
    int coleccion;
    int rareza;
};

// Tipo de datos que recibiremos del servidor. En este caso cadenas de caracteres con premios
struct Respuesta {
    char premio[100];
};

// Función que devuelve la rareza según las probabilidades. Me baso en el ejercicio 2 de la PEC0
int elegir_rareza() {
    int numero = rand() % 100;

    if (numero < 21) return 0;      // común 79%
    else if (numero < 85) return 1; // infrecuente 15%
    else if (numero < 95) return 2; // raro 5%
    else return 1;                  // épico 1%
}


//Inicio del programa principal

int main(int argc, char *argv[]) {

    int conexion;            // socket del cliente
    struct sockaddr_in servidor;  // IP y puerto del servidor
    int cantidad_premios;               // cuántos premios pide el usuario
    int contador;                       // índice del bucle
    struct Peticion peticion;     // lo que enviamos
    struct Respuesta respuesta;   // lo que recibimos


    // Listas de texto para mostrar al usuario como dice el enunciado
    const char *lista_colecciones[] = {
        "Cromos de fútbol",
        "Personajes de rol",
        "Armas de juego cooperativo",
        "Monstruos de bolsillo"
    };
    //Lita de tipos de rarezas tal y como está en el enunciado
    const char *lista_rarezas[] = {
        "común",
        "infrecuente",
        "raro",
        "épico"
    };
    
    //Control de error en la ejecucion. El usuario debe ejecutar de esta manera el programa:
    //./exc3cli 127.0.0.0 5003 <-- Esto es un ejemplo con localhost para el servidor y 
    //el puerto 5003 si el servidor está en otro pc poner la ip y el puerto que esté destinado
    //Si no se introducen los 3 parametros dará el error y explica como deberías ejecutar
    //Pero se finaliza el programa

    if (argc != 3) {
        printf("Uso: %s <IP_servidor> <puerto>\n", argv[0]);
	printf("Error en la entrada de datos\n");
        printf("Ejemplo de ejecución: ./ex3cli 127.0.0.1 5003\n");
        return 1;
    }

    //Todo marcha bien y continua el programa:    
    srand((int) time(NULL)); // semilla para números aleatorios

    // Crear socket para la conexion
    conexion = socket(AF_INET, SOCK_STREAM, 0);
    if (conexion < 0) {
        printf("Error al crear el socket\n");
        return 1;
    }

    servidor.sin_family = AF_INET;//Se define que se trabajará con direcciones IPV4
    servidor.sin_port = htons(atoi(argv[2]));//Asignamos el puerto con  el parametro. Casting con atoi

    //Condicion que establece 
    if (inet_pton(AF_INET, argv[1], &servidor.sin_addr) <= 0) {
        printf("La dirección IP introducida es correcta\n");
        close(conexion);
        return 1;
    }

    // Conectamos al servidor y si hay error imprimimos el Error y termina el programa, sino se continua
    if (connect(conexion,
                (struct sockaddr *)&servidor,
                sizeof(servidor)) < 0) {
        printf("Error al conectar con el servidor\n");
        close(conexion);
        return 1;
    }
    //Se imprime el exito de la conexion
    printf("Exito en la coneccion con el servidor %s:%s\n", argv[1], argv[2]);

    // Preguntar al usuario cuántos premios quiere
    printf("¿Cuántos premios quieres recibir? ");
    if (scanf("%d", &cantidad_premios) != 1 || cantidad_premios <= 0) {
        printf("Número de premios no válido.\n");
        close(conexion);
        return 1;
    }

    /* Bucle principal que se repitirá tantas veces como premios hemos introducido
     * que queremos. En cada bucle se elige las de manera random tanto la coleccion como 
     * la rareza. Cuando se haya asigando dicha coleccion y rareza se imprime por Consola
     * los resultados y se envían al servidor para lo procese y nos devuelva el premio exacto 
     * que luego imprimiremos en el mismo bucle for. Cuando terminan todas las vueltas del for
     * se cierra la conexion y termina el cliente.
     */

    for (contador = 0; contador < cantidad_premios; contador++) {

        peticion.coleccion = rand() % 4;
        peticion.rareza = elegir_rareza();

        printf("\nPremio %d:\n", contador + 1);
        printf("  Colección: %s\n", lista_colecciones[peticion.coleccion]);
        printf("  Rareza:    %s\n", lista_rarezas[peticion.rareza]);
        printf("  Enviando petición al servidor...\n");
	
	//Si hay error en el envío de los datos imprimo Error 
        if (write(conexion, &peticion, sizeof(peticion))
            != sizeof(peticion)) {

            printf("Error al enviar la petición\n");
            break;
        }
        //Si hay error enla recepcion de datos imprimo Error
        if (read(conexion, &respuesta, sizeof(respuesta)) <= 0) {
            printf("Error al recibir la respuesta del servidor\n");
            break;
        }
        //Añado el fin de char con \0 e imprimo el Premio obtenido
        respuesta.premio[99] = '\0';
        printf("  --> Premio obtenido: %s\n", respuesta.premio);
    }
    
    //Fin del programa cierro la conexion
    printf("\nFin del cliente.\n");
    close(conexion);
    return 0;
}


