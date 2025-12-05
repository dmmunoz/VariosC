/*
 * Filename: ex3serv.c
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


//Empiezo con la creación de los tipos de datos que iré necesitando

// Datos recibidos del cliente
struct Peticion {
    int coleccion;
    int rareza;
};

// Datos enviados al cliente
struct Respuesta {
    char premio[100];
};

// Tabla de premios por colección y rareza
const char *tabla_premios[4][4][3] = {
    {
        { "Cromo comun Defensor", "Cromo comun Centrocampista", "Cromo comun Delantero" },
        { "Cromo infrecuente Defensor", "Cromo infrecuente Centrocampista", "Cromo infrecuente Delantero" },
        { "Cromo raro Defensor", "Cromo raro Centrocampista", "Cromo raro Delantero" },
        { "Cromo epico Defensor", "Cromo epico Centrocampista", "Cromo epico Delantero" }
    },
    {
        { "Rol comun Guerrero", "Rol comun Mago", "Rol comun Clérigo" },
        { "Rol infrecuente Kobolds", "Rol infrecuente Lulu", "Rol infrecuente Ann" },
        { "Rol raro Norimaro", "Rol raro Ivern", "Rol raro Rosalind" },
        { "Rol epico Combatiente", "Rol epico Lider", "Rol epico Monstruo" }
    },
    {
        { "Arma comun Palo", "Arma comun Daga", "Arma comun Espada" },
        { "Arma infrecuente Arpon", "Arma infrecuente Cadena con palos", "Arma infrecuente Machete de cobre" },
        { "Arma rara Krummlauf", "Arma rara Rifle OiW", "Arma rara Rayo de Gran Saxo" },
        { "Arma epica Pistola de gravedad", "Arma epica Espada del Caos", "Arma epica Megabuster" }
    },
    {
        { "Monstruo comun Goblins", "Monstruo comun Araña", "Monstruo comun Lobo" },
        { "Monstruo infrecuente Dhole", "Monstruo infrecuente Dragons", "Monstruo infrecuente Tarasca" },
        { "Monstruo raro Akuma", "Monstruo raro Blindheim", "Monstruo raro Kaijus" },
        { "Monstruo epico Behemonth", "Monstruo epico Baron Nashor", "Monstruo epico Leviathan" }
    }
};

//Inicio del programa principal
int main(int argc, char *argv[]) {

    int socket_servidor;               // Socket principal para aceptar conexiones
    int socket_cliente;                // Socket para hablar con el cliente
    struct sockaddr_in datos_servidor; // Datos del servidor
    struct sockaddr_in datos_cliente;  // Datos del cliente
    socklen_t longitud_cliente;        // Longtitud de  

    struct Peticion datos_peticion;
    struct Respuesta datos_respuesta;

    if (argc != 2) {
        printf("Uso: %s <puerto>\n", argv[0]);
        printf("Ejemplo: ./ex3serv 5001\n");
        return 1;
    }

    srand((int) time(NULL));

    // Crear socket de conexion del servidor
    socket_servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_servidor < 0) {
        printf("Error al crear el socket del servidor\n");
        return 1;
    }

    datos_servidor.sin_family = AF_INET; //Se define que se trabajará con direcciones IPV4
    datos_servidor.sin_addr.s_addr = INADDR_ANY; //Definimos que acepte cualquier IP de entrada del PC
    datos_servidor.sin_port = htons(atoi(argv[1])); //Asignamos el puerto con  el parametro. Casting con atoi

    // Asociar IP/puerto al socket
    if (bind(socket_servidor, (struct sockaddr *)&datos_servidor,
             sizeof(datos_servidor)) < 0) {

        printf("Error en bind\n");
        close(socket_servidor);
        return 1;
    }

    if (listen(socket_servidor, 1) < 0) {
        printf("Error en listen\n");
        close(socket_servidor);
        return 1;
    }

    printf("Servidor escuchando en el puerto %s...\n", argv[1]);

    //Guardo el tamaño de la estuctura de los datos del cliente para que se le pueda pasar por 
    //parametros en la creacion del socket del cliente.
    longitud_cliente = sizeof(datos_cliente);

    //Creo el socket cliente con los datos que ya se han definido
    socket_cliente = accept(socket_servidor,
                            (struct sockaddr *)&datos_cliente,
                            &longitud_cliente);

    //SI hay error se cierra la conexion, informa al usuario e imprime error por consola
    if (socket_cliente < 0) {
        printf("Error en la conexión, se debe cerrar el servidor\n");
        close(socket_servidor);
        return 1;
    }

    printf("Cliente conectado.\n");

    // Bucle principal del servidor para ir recibiendo datos del cliente. Bucle infinito, se finaliza cuando se cierra el servidor

    while (1) {
        //Lectura de datos que envia el cliente    
        ssize_t recibido = read(socket_cliente, &datos_peticion, sizeof(datos_peticion));
    
        //Control de error no recepción de datos
        if (recibido == 0) {
            printf("Cliente desconectado.\n");
            break;
        }

        //Control de error datos erroneos
        if (recibido < 0) {
            printf("Error al leer datos del cliente\n");
            break;
        }
    
        //Procesamiento de datos . Imprimo que hemos recibido del cliente
        printf("Petición recibida: coleccion=%d rareza=%d\n",
               datos_peticion.coleccion, datos_peticion.rareza);

        //Genero premios random
        int aleatorio = rand() % 3;

        //Variable para ir añadiendo los premios que se enviarán al cliente
        const char *texto_premio;

        // Guardamos en una variable auxiliar el premio elegido
        texto_premio = tabla_premios[datos_peticion.coleccion][datos_peticion.rareza][aleatorio];

        // Copio el texto dentro del campo premio de la estructura Respuesta
        strcpy(datos_respuesta.premio, texto_premio);

        //Envío los datos al cliente, si hay error se imprime el error y pasa al siguiente flujo de datos que envíe el cliente
        if (write(socket_cliente, &datos_respuesta, sizeof(datos_respuesta))
            != sizeof(datos_respuesta)) {

            printf("Error al enviar respuesta\n");
            break;
        }
    }

    close(socket_cliente);
    close(socket_servidor);

    printf("Servidor terminado.\n");
    return 0;
}
