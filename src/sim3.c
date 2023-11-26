#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../libs/simulaciones.h"

void Simulacion_3(char *arg1){
	// Inicializacion del srandr
	srand(time(NULL));

	// Obtener datos de entrada
	// validar entrada

	int n_cajas = atoi(arg1); // 0 < n < 11, n e N
	int t_atencion;
	int t_clientes;
	int t_usuarios;
	int t_preferentes;

	// Tiempo de atencion para /n_cajas/ cajeros.
	Caja *cajas = (Caja*)malloc(sizeof(Caja) * n_cajas);

	for (int i = 0; i < n_cajas; i++){
		scanf("%d", &t_atencion);
		Abrir_Caja(&cajas[i], t_atencion);
	}
	
	scanf("%d", &t_clientes);
	scanf("%d", &t_usuarios);
	scanf("%d", &t_preferentes);

	int elegir_caja;
	int t = 0;
	elemento cliente_actual;

	// Abre el banco
	while(TRUE){
		// dormir tiempo base
		usleep(TIEMPO_BASE);
		t++;

		// cliente aleatorio y es formado de acuerdo a su prioridad
		elegir_caja = rand() % 10; // numero aleatorio del 0 al 9

		if (t % t_clientes == 0)
			Queue(&cajas[elegir_caja].clientes, cliente_actual);

		else if (t % t_usuarios == 0){
			Queue(&cajas[elegir_caja].usuarios, cliente_actual);
		}

		else if (t % t_preferentes == 0)
			Queue(&cajas[elegir_caja].preferentes, cliente_actual);

		if (t % t_atencion == 0)
			for (int i = 0; i < n_cajas; i++){
				Atencion(&cajas[i]);
			}

		//
	}

}

void Abrir_Caja(Caja *caj, unsigned int t){
	Initialize(&caj->clientes);
	Initialize(&caj->usuarios);
	Initialize(&caj->preferentes);

	caj->tiempo_de_atencion = t;
	caj->cont_u = t;
}

void Atencion(Caja *caj){
	if (caj->cont_u > 5 && !Empty(&caj->usuarios)){
		Dequeue(&caj->usuarios);
	}

	else if (!Empty(&caj->preferentes)){
		Dequeue(&caj->preferentes);
		caj->cont_u++;
	}

	else if (!Empty(&caj->clientes)){
		Dequeue(&caj->clientes);
		caj->cont_u++;
	}
}
