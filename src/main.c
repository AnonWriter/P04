#include <stdio.h>
#include "../libs/ej/TADColaDin.h"
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
		// Atencion_A_Proceso();
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
		// Atencion_Al_Cliente
		// ...
		// Funcines de cola
	// -> Estructuras:
		// ...
}
