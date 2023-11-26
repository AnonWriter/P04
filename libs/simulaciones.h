#ifndef SIMULACIONES_H
#define SIMULACIONES_H

#define TIEMPO_BASE 1000000
#define QUANTUM 1

typedef struct proceso{
	char nombre[50];
	char actividad[200];
	char id[20];
	unsigned int tiempo;
	unsigned int tiempo_real;
} Proceso;

// Funcion principal de la segunda simulacion
void Simulacion_2(char *arg1);

// Funciones de graficos
void ProcActual();
void ProcQueue();
Proceso CrearProceso();

#endif
