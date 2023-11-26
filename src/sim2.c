#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // En cuanto a esta libreria, tendras que cambiarla por windows.h para utilizar el sleep de windows y no usleep para mi

#include "../libs/simulaciones.h"

void Simulacion_2(char *arg1){
	// Recibir argumentos
	int c_proc = atoi(arg1);

	// Crear las colas
	cola Listos;
	cola Terminados;

	Initialize(&Listos);
	Initialize(&Terminados);


	elemento aux;

	// Pedir los datos del proceso i
	for (int i = 0; i < c_proc; i++){
		printf("Nombre proc %d: ", i + 1);
		fgets(aux.p.nombre, sizeof(aux.p.nombre), stdin);

		printf("Actividad: ");
		fgets(aux.p.actividad, sizeof(aux.p.actividad), stdin);

		printf("ID: ");
		fgets(aux.p.id, sizeof(aux.p.id), stdin);

		printf("Tiempo solicitado: ");
		scanf("%d", &aux.p.tiempo);

		aux.p.tiempo_real = 0;

		//Limpiar el buffer o algo porque hace cosas raras si no esta esto
		while (getchar() != '\n');

		Queue(&Listos, aux);
	}

	//parte de atencion
	elemento actual_proc;
	while(!Empty(&Listos)){
		actual_proc = Dequeue(&Listos);

		printf("-------------------------------------------------------------------\n");
		printf("%s", actual_proc.p.nombre);
		printf("%s", actual_proc.p.actividad);
		printf("%s\n", actual_proc.p.id);
		printf("Tiempo de ejecucion: %d\n", actual_proc.p.tiempo);
		printf("Tiempo total: %d\n", actual_proc.p.tiempo_real);
		printf("-------------------------------------------------------------------");
		printf("\n");

		usleep(TIEMPO_BASE * QUANTUM);

		actual_proc.p.tiempo_real += 1;
		actual_proc.p.tiempo -= 1;

		if(actual_proc.p.tiempo == 0){
			Queue(&Terminados, actual_proc);
		}
		else{
			actual_proc.p.tiempo_real += Size(&Listos);
			Queue(&Listos, actual_proc);
		}


	}

	while(!Empty(&Terminados)){
		actual_proc = Dequeue(&Terminados);
		printf("Proc: %s", actual_proc.p.nombre);
		printf("Tiempo total: %d\n", actual_proc.p.tiempo_real);
	}

}

