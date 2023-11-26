/*
Cajeras.c
Autor original: Edgardo Adrian Franco Martinez
Autor que lo implementa: Juarez Jimenez Mariam

Descripcion: Ejemplo de atencion de dos colas de clientes, la simulacion
de tiempo se realiza con la funcion Sleep (solo funciona en windows), cada X
tiempo llega un cliente y escoge pseudoaleatoriamente una cola y el tiempo
de atencion es Y.

Observaciones: Se puede emplear la libreria TADPilaEstCir.h, TADColaEstCirc.h o TADColaDin.h implementadas
en clase. Ambas estructuras elemento, ya sea la de las implementaciones estaticas o dinamicas deberan
tener un campo int n.

Compilacion:
Windows: gcc -o Cajeras Cajeras.c TADCola/TADCola(Din|Est|EstCirc).o (Si se tiene el objeto de la implementacion)
		 gcc -o Cajeras Cajeras.c TADCola/TADCola(Din|Est|EstCirc).c (Si se tiene el fuente de la implementacion)
		 
Ejecucion: Cajeras.exe (En Windows)
*/

//LIBRERIAS
#include <stdio.h>
#include <windows.h>
#include <time.h>				//Funciona unicamente en Windows para usar la funcion Sleep()
//#include "TADColaEst/TADColaEstCirc.h" 	//Si se usa la implemtentacion estatica (TADColaEst.c|TADColaEstCirc.c)
#include "TADColaDin.h" 	//Si se usa la implemtentacion dinamica (TADColaDin.c)

//DEFINICION DE CONSTANTES
#define TIEMPO_BASE	200			//Tiempo base en ms
//#define TIEMPO_CLIENTE	1		//Tiempo base en ms * 1
//#define TIEMPO_ATENCION	3		//Tiempo base en ms * 3
#define POSICION_INICIAL_X 2
#define POSICION_INICIAL_Y 10


int main(void)
{
	unsigned int tiempo = 0;
	unsigned int cliente = 0;
	int tiempoAtencion;
    int tiempoLlegada;
	int i,j,cajeros,fila;
	int clientesAtendidos = 0;
    int filasVacias = 0;
	int *numClientes;
	char nombre[25];
	elemento e;
	//Inicializar la funcion rand
	srand(time(NULL));
	
	printf("INTRODUZCA EL NOMBRE DEL SUPERMERCADO: ");
    scanf("%s",&nombre);

    printf("Introduzca el numero de cajeros que van a atender el dia de hoy:\n ");
    scanf("%d",&cajeros);
    
	if(cajeros<0 || cajeros>10)
	{
		printf("ERROR: SOLO SE ADMITEN DE 1 A 10 CAJEROS.");
		exit(1);
	}


	printf("Introduzca el tiempo de atencion de las cajas en segundos: ");
    scanf("%d", &tiempoAtencion);

    printf("Introduzca el tiempo de llegada de los clientes en segundos: ");
    scanf("%d", &tiempoLlegada);
	system("cls");

	//Crear colas
	cola cajera[cajeros];
	
	// Antes de inicializar las colas, asignar memoria para el puntero numClientes
	numClientes = (int *)malloc(cajeros * sizeof(int));
	if (numClientes == NULL) {
    printf("Error: No se pudo asignar memoria.\n");
    exit(1);
	}
	
	BorrarPantalla();
	printf("\t\t\tBIENVENIDO AL SUPERMERCADO %s.",nombre);
	//Inicializar las colas
	for(i=0;i<cajeros;i++){
		Initialize(&cajera[i]);
		numClientes[i] = 0;
		DibujaCaja(i,i+1);
	}
	MoverCursor(10, 10);

	//Ciclo infinito
	while (clientesAtendidos < 100 || filasVacias > 0)
	{
		filasVacias=cajeros+1;
		Sleep(250);		//Esperar el tiempo base
		tiempo++;		//Incrementar el contador de tiempo
		
		//Si el tiempo es multiplo del de llegada de los clientes
		if (tiempo % (tiempoLlegada * 1000/ 200) == 0)
		{
			e.n = cliente;			//Dar el numero que identifica al cliente
			cliente++;				//Incrementar el numero de clientes
			fila=rand()%cajeros;	//Escoger la fila para formarse aleatoriamente	
			while (fila < 0 || fila >= cajeros) {
    		fila = rand() % cajeros;
			}				
			Queue(&cajera[fila], e);//Formarse en la fila seleccionada
			if (!Empty(&cajera[fila])) {
    			filasVacias--;
				}
			numClientes[fila]++; //Incrementar el numero de clientes en la cola correspondiente.
			MoverCursor(55, 16);
		//Imprimimos la llegada de un nuevo cliente.
			printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tLlego el cliente: %d a la cola de la caja %d\n", e.n,fila+1);
			printf("\n\t\t\t\t\t\t\t\tClientes Atendidos: %d",clientesAtendidos);
			printf("\nFilas vacias:  %d",filasVacias);
		}
		 

// Obtener el numero maximo de elementos en todas las colas
int maxClientes = 0;
for (i = 0; i < cajeros; i++) {
    int numElementos = Size(&cajera[i]);
    if (numElementos > maxClientes) {
        maxClientes = numElementos;
    }
}
	   
for (i = 0; i < cajeros; i++) {
    int numElementos = Size(&cajera[i]);
    for (j = 0; j < numElementos; j++) {
        e = Element(&cajera[i], j + 1);
        MoverCursor(POSICION_INICIAL_X + i * 9, POSICION_INICIAL_Y + j);
        printf("%d", e.n);  // Imprimir el numero con una longitud de 2 caracteres
    }
    // Limpiar los espacios restantes en la columna
    for (j = numElementos; j < maxClientes; j++) {
        MoverCursor(POSICION_INICIAL_X + i * 9, POSICION_INICIAL_Y + j);
        printf("    ");  // Imprimir dos espacios para asegurar que se borre cualquier numero anterior
    }
}


		//Si el tiempo es multiplo del tiempo de atencion
		if (tiempo % (tiempoAtencion * 1000 / 200) == 0)
{
	  
    for (i = 0; i < cajeros; i++)
    {
        if (!Empty(&cajera[i]))
        {
            e = Dequeue(&cajera[i]);
			if (Empty(&cajera[i])) {
    			filasVacias++;
			}
        MoverCursor(55, 19);
		printf("\n\n\n\n\t\t\t\t\t\t\t\tAtendi a: %d en caja %d", e.n, i+1);                   
		clientesAtendidos++;
		AnimacionClienteAtendido();
		

		// Mover los elementos restantes en la cola una posicion hacia arriba
            for (j = 1; j <= Size(&cajera[i]); j++)
            {
                elemento aux = Element(&cajera[i], j);
                MoverCursor(POSICION_INICIAL_X + i * 9, POSICION_INICIAL_Y + j - 1);
                printf("%d", aux.n);
            }
            // Limpiar la ultima posicion en la columna
            MoverCursor(POSICION_INICIAL_X + i * 9, POSICION_INICIAL_Y + Size(&cajera[i]));
            printf("    ");
		}
        else
        {
            //printf("\n\n\nNo hay alguien por atender en caja %d", i+1);
        }
    }
}

	}
    printf("\n\nEl supermercado ha cerrado. Se atendieron 100 clientes y no hay nadie formado en las filas.\n");
	free(numClientes);
	return 0;
}
