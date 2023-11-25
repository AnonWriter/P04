#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // En cuanto a esta libreria, tendras que cambiarla por windows.h para utilizar el sleep de windows y no usleep para mi

#include "../libs/simulaciones.h"
#include "../libs/ej/TADColaDin.h"

void Simulacion_2(char *arg1){
	// Recibir argumentos
	int c_proc = atoi(arg1);

	for (int i = 0; i < c_proc; i++){
		// Pedir los datos del proceso i
	}

	// Crear las colas
	cola Listos;
	cola Terminados;

	Initialize(&Listos);
	Initialize(&Terminados);



}

