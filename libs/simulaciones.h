#ifndef SIMULACIONES_H
#define SIMULACIONES_H

#define TIEMPO_BASE 1000 // 1 MILISEGUNDO
#define QUANTUM 1000 // MIL MILISEGUNDOS

#include "../libs/ej/TADColaDin.h"

/************************************************************************
*			SEGUNDA SIMULACION				*
************************************************************************/


// Funcion principal de la segunda simulacion
void Simulacion_2(char *arg1);

// Funciones de graficos
void ProcActual();
void ProcQueue();


/************************************************************************
*			TERCERA SIMULACION				*
************************************************************************/

typedef struct caja {
	cola clientes;
	cola usuarios;
	cola preferentes;
	unsigned int tiempo_de_atencion;
	unsigned int cont_u;
} Caja;

void Simulacion_3(char *arg1);
void Abrir_Caja(Caja *caj, unsigned int t);
void Atencion(Caja *caj);

#endif
