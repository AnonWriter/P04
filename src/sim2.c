#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // En cuanto a esta libreria, tendras que cambiarla por windows.h para utilizar el sleep de windows y no usleep para mi
#include <ncurses.h>

#include "../libs/simulaciones.h"

void Simulacion_2(char *arg1){
	// Iniciar Ncurses
	WINDOW *win;
	IniciarNcurses(win);
	start_color();

	// Recibir argumentos
	int c_proc = atoi(arg1);

	// Crear las colas
	cola Listos;
	cola Terminados;

	Initialize(&Listos);
	Initialize(&Terminados);

	elemento aux;

	// Pedir los datos del proceso i
	Recibir_Datos(&Listos, c_proc);
	/*
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
	*/

	clear();

	getch();

	//parte de atencion
	/*
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
	*/

	Salir();

}

void IniciarNcurses(WINDOW *win){
	win = initscr();
	clear();
	refresh();
	//noecho();
	cbreak();
}

void Salir(){
	endwin();
	exit(0);
}

void Recibir_Datos(cola *Listos, int c_proc){
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);
	bkgd(COLOR_PAIR(2));

	elemento aux;

	//
	
	attron(COLOR_PAIR(1));
	for (int i = 0; i < 10; i++){
		move(5 + i,5);
		printw(" ");
		move(5 + i,84);
		printw(" ");
	}
	for (int i = 0; i < 80; i++){
		move(4, 5 + i);
		printw(" ");
		move(15,5 + i);
		printw(" ");
		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(4));
		move(5, 5 + i);
		printw(" ");
		attroff(COLOR_PAIR(4));
		attron(COLOR_PAIR(1));
	}
	attroff(COLOR_PAIR(1));

	move(2, 10);
	printw("Obtencion de datos de cada proceso: ");

	for (int i = 0; i < c_proc; i++){
		// limpiar
		for (int j = 0; j < 78; j++){
			for (int k = 0; k < 8; k++){
				move(6 + k, 6 + j);
				printw(" ");
			}
		}

		attron(COLOR_PAIR(3));
		move(4,8);
		printw("Proceso %d", i + 1);

		attroff(COLOR_PAIR(3));
		move(7,10);
		printw("Nombre: ");
		move(9,10);
		printw("Actividad: ");
		move(11,10);
		printw("ID: ");
		move(13,10);
		printw("Tiempo solicitado: ");

		attron(COLOR_PAIR(3));

		move(7,18);
		getnstr(aux.p.nombre, 15);

		move(9,21);
		getnstr(aux.p.actividad, 61);

		move(11,14);
		getnstr(aux.p.id, 10);

		move(13,29);
		scanw("%d", &aux.p.tiempo);

		attroff(COLOR_PAIR(3));

		refresh();

		Queue(Listos, aux);
	}

}
