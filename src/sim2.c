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

	clear();
	refresh();

	//parte de atencion
	elemento actual_proc;
	while(!Empty(&Listos)){
		actual_proc = Dequeue(&Listos);

		//mostrar la cola de listos para ejecucion
		ProcActual(actual_proc);
		ProcListos(&Listos);
		ProcAnterior(actual_proc);

		actual_proc.p.tiempo_real += 1;
		actual_proc.p.tiempo -= 1;

		usleep(TIEMPO_BASE * QUANTUM);


		if(actual_proc.p.tiempo == 0){
			Queue(&Terminados, actual_proc);
			ProcTerminados(&Terminados);
		}
		else{
			actual_proc.p.tiempo_real += Size(&Listos);
			Queue(&Listos, actual_proc);
		}

		ProcActual(actual_proc);
		ProcListos(&Listos);
		ProcAnterior(actual_proc);
	}

	while(!Empty(&Terminados)){
		actual_proc = Dequeue(&Terminados);
	}
	
	getch();

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
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
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

		aux.p.tiempo_real = 0;

		attroff(COLOR_PAIR(3));

		refresh();

		Queue(Listos, aux);
	}

}

void ProcListos(cola *l){
	int lim = 5;
	if (Size(l) < 5) lim = Size(l);
	
	for (int k = 0; k < lim; k++){
		// limpiar
		for(int i = 0; i < 28; i++){
			for (int j = 0; j < 23; j++){
				move(16 + j, 6 + i);
				printw(" ");
			}
		}

		//dibujar las lineas
		/*
		attron(COLOR_PAIR(1));
		for(int i = 0; i < 30; i++){
			for(int j = 0; j < lim; j++){
				move(15 + j*5, 5 + i);
				printw(" ");
	
				move(20 + j*5, 5 + i);
				printw(" ");
			}
	
			refresh();

		}

		for(int i = 0; i < 5; i++){
			move(15 + i, 5);
			printw(" ");

			move(15 + i, 34);
			printw(" ");

			refresh();
		}
		attroff(COLOR_PAIR(1));
		*/



		// dibujar el nombre y el tiempo
		attron(COLOR_PAIR(5));
		move(16,12);
		printw(" Listos ");
		attroff(COLOR_PAIR(5));
		for(int i = 0; i < lim; i++){
			move(17 + i*5, 10);
			printw("%s", Element(l,i + 1).p.nombre);

			move(18 + i*5, 10);
			printw("%s", Element(l,i + 1).p.id);

			move(19 + i*5, 10);
			printw("tiempo = %d", Element(l,i + 1).p.tiempo);
		}

		refresh();
	}
}

void ProcActual(elemento p){
	// limpiar
	for (int j = 0; j < 78; j++){
		for (int k = 0; k < 8; k++){
			move(6 + k, 6 + j);
			printw(" ");
		}
	}

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
	attron(COLOR_PAIR(6));
	move(4,10);
	printw(" Ejecutando ");
	attroff(COLOR_PAIR(6));

	move(7,10);
	printw("%s", p.p.nombre);
	move(9,10);
	printw("%s", p.p.actividad);
	move(11,10);
	printw("ID: %s", p.p.id);
	move(12,10);
	printw("Tiempo restante: %d", p.p.tiempo);
	move(13,10);
	printw("Tiempo total: %d", p.p.tiempo_real);

	refresh();
}

void ProcTerminados(cola *t){
	int lim = Size(t);
	for(int k = 1; k <= lim; k++){
		attron(COLOR_PAIR(1));
		for(int i = 0; i < 17*k; i++){
			move(40, 160 - i);
			printw(" ");

			move(33, 160 - i);
			printw(" ");
		}
		for(int l = 0; l < 7; l++){
			move(40 - l, 160 - 17*k);
			printw(" ");
		}
		attroff(COLOR_PAIR(1));
		move(30, 120);
		printw("Cola de terminados (<----)");

		move(35, 162 - 17*k);
		printw("%s",  Element(t,k).p.nombre);
		move(36, 162 - 17*k);
		printw("%s", Element(t,k).p.id);
		move(38, 162 - 17*k);
		printw("t_total: %d", Element(t,k).p.tiempo_real);
		refresh();
	}
}

void ProcAnterior(elemento e){
	attron(COLOR_PAIR(1));
	for(int i = 0; i < 30; i++){
		move(7, 85 + i);
		printw(" ");

		move(16, 85 + i);
		printw(" ");
	}
	for(int i = 0; i < 10; i++){
		move(7 + i, 115);
		printw(" ");

		move(7 + i, 85);
		printw(" ");
	}
	attroff(COLOR_PAIR(1));

	move(6, 89);
	printw("Proceso anterior");

	move(9, 89);
	printw("%s", e.p.nombre);
	move(10, 89);
	printw("%s", e.p.id);
	move(11, 89);
	printw("%d", e.p.tiempo);

	refresh();
}
