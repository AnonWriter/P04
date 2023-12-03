#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#include "../libs/simulaciones.h"

void Simulacion_3(char *arg1){
	WINDOW *win;

	// Inicializacion del srandr
	srand(time(NULL));

	// Obtener datos de entrada
	// validar entrada

	int n_cajas = atoi(arg1); // 0 < n < 11, n e N
	if (n_cajas < 1 || n_cajas > 10){
		printf("Número inválido de cajas, debe ingresar un número de 1 a 10.\n ");
	}

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

	IniciarNcurses(win);
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_BLACK);

	// Mostrar cajas
	attron(COLOR_PAIR(1));
	for(int k = 0; k < n_cajas; k++){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 5; j++){
				move(1 + i + k*4, 1 + j);
				printw(" ");
			}
		}
	}
	attroff(COLOR_PAIR(1));

	refresh();

	int c_cont = 0;
	int us_cont = 0;
	int p_cont = 0;

	// Abre el banco
	while(TRUE){
		// dormir tiempo base
		usleep(TIEMPO_BASE);
		t++;

		// cliente aleatorio y es formado de acuerdo a su prioridad
		elegir_caja = rand() % n_cajas; // numero aleatorio del 0 al 9

		if (t % t_clientes == 0){
			cajas[elegir_caja].c_cont++;
			attron(COLOR_PAIR(2));
			for (int i = 0; i < 1; i++){
				for (int j = 0; j < 3; j++){
					move(1 + i + elegir_caja*4, 7 + j + cajas[elegir_caja].c_cont * 4);
					printw("C");
				}
			}
			attroff(COLOR_PAIR(2));
			Queue(&cajas[elegir_caja].clientes, cliente_actual);
		}

		if (t % t_usuarios == 0){
			cajas[elegir_caja].u_cont++;
			attron(COLOR_PAIR(3));
			for (int i = 0; i < 1; i++){
				for (int j = 0; j < 3; j++){
					move(2 + i + elegir_caja*4, 7 + j + cajas[elegir_caja].u_cont * 4);
					printw("U");
				}
			}
			attroff(COLOR_PAIR(3));
			Queue(&cajas[elegir_caja].usuarios, cliente_actual);
		}

		if (t % t_preferentes == 0){
			cajas[elegir_caja].p_cont++;
			attron(COLOR_PAIR(4));
			for (int i = 0; i < 1; i++){
				for (int j = 0; j < 3; j++){
					move(3 + i + elegir_caja*4, 7 + j + cajas[elegir_caja].p_cont * 4);
					printw("P");
				}
			}
			attroff(COLOR_PAIR(4));
			Queue(&cajas[elegir_caja].preferentes, cliente_actual);
		}

		

		for (int i = 0; i < n_cajas; i++){
			if (t % cajas[i].tiempo_de_atencion == 0){
				Atencion(&cajas[i], i);
			}
		}

		

		//
		refresh();
	}

	Salir();
}

/*
void IniciarNcurses(WINDOW *win){
	win = initscr();
	clear();
	refresh();
	//noecho();
	cbreak();
}
*/

/*
void Salir(){
	endwin();
	exit(0);
}
*/

void Abrir_Caja(Caja *caj, unsigned int t){
	Initialize(&caj->clientes);
	Initialize(&caj->usuarios);
	Initialize(&caj->preferentes);

	caj->tiempo_de_atencion = t;
	caj->cont_u = 0;
	caj->c_cont = 0;
	caj->u_cont = 0;
	caj->p_cont = 0;
}

void Atencion(Caja *caj, int al){
	if (!Empty(&caj->preferentes) && caj->cont_u < 5){
		attron(COLOR_PAIR(4));
		move(2 + al * 4, 2);
		printw("PPP");
		attroff(COLOR_PAIR(4));
		for (int i = 0; i < 1; i++){
			for (int j = 0; j < 3; j++){
				move(3 + i + al*4, 7 + j + caj->p_cont * 4);
				printw(" ");
			}
		}
		caj->p_cont--;
		Dequeue(&caj->preferentes);
		caj->cont_u++;
	}

	else if (!Empty(&caj->clientes) && caj->cont_u < 5){
		attron(COLOR_PAIR(2));
		move(2 + al * 4, 2);
		printw("CCC");
		attroff(COLOR_PAIR(2));
		for (int i = 0; i < 1; i++){
			for (int j = 0; j < 3; j++){
				move(1 + i + al*4, 7 + j + caj->c_cont * 4);
				printw(" ");
			}
		}
		caj->c_cont--;
		Dequeue(&caj->clientes);
		caj->cont_u++;
	}

	else if (!Empty(&caj->usuarios)){
		attron(COLOR_PAIR(3));
		move(2 + al * 4, 2);
		printw("UUU");
		attroff(COLOR_PAIR(3));
		for (int i = 0; i < 1; i++){
			for (int j = 0; j < 3; j++){
				move(2 + i + al*4, 7 + j + caj->u_cont * 4);
				printw(" ");
			}
		}
		caj->u_cont--;
		Dequeue(&caj->usuarios);
		caj->cont_u = 0;
	}


}
