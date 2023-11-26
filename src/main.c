#include <stdio.h>
#include "../libs/simulaciones.h"

int main(int argn, char *args[])
{
	// Primer simulacion
	// Necesario: (excluyendo los graficos por ahora)
	// -> Funciones
		// Atencion_Al_Cliente() : funcion para controlar la atencion de cada una de las cajas
		// ...
		// Funciones de cola


	// Segunda simulaicion
	// Necesario: (exluyendo los graficos por ahora)
	// -> Funciones
		// Atencion_Proceso();
		// ...
		// Funciones de cola
	// -> Estructuras:
		// struct proceso : una estructura que contenga toda la informacion necesaria de un proceso
			// ./ Nombre
			// ./ Descripcion
			// ./ Tiempo solicitado
			// ./ Tiempo real 
	Simulacion_2(args[1]);


	// Tercer simulacion
	// Necesario: (exluyendo los graficos por ahora)
	// -> Funciones
		// Prioridad();
		// Atencion();
		// ...
		// Funcines de cola
	// -> Estructuras:
		// struct caja : una estructura que contiene la cola correspondiente y el tiempo de atención
			// ./ Cola
			// ./ Tiempo de atencion
		// struct persona : una estructura que contiene la prioridad de una persona
			// ./ prioridad
		// ...
	//Simulacion_3(args[1]);
}
