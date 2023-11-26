/*
Libreria: Cabecera del TAD COLA DINAMICA
Autor original: Edgardo Adrian Franco Martinez
Autor que lo implementa: Juarez Jimenez Mariam

Descripcion: TAD COLA. Estructura de datos en la que se cumple:
Los elementos se insertan en un extremo (el posterior) y
la supresiones tienen lugar en el otro extremo (frente).

Observaciones: Hablamosde una estructura de datos dinamica cuando
se le asigna memoria a medida que es necesitada,
durante la ejecucion del programa.

Compilacion: gcc -c TADColaDin.c
*/

//Librerias
#include "TADColaDin.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
//Definicion de funciones

/*
void Initialize(cola *c);
Descripcion: Inicializar cola (Iniciar una cola para su uso)
Recibe: cola *c (Referencia a la cola "c" a operar)
Devuelve:
Observaciones: El usuario a creado una cola y c tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
void Initialize(cola * c)
{
	c->num_elem=0;
	c->frente=NULL;
	c->final=NULL;
	

	return;
}

/*
void Queue(cola * c, elemento e);
Descripcion: Recibe una cola y agrega un elemento al final de ella.
Recibe: cola *c (Referencia a la cola "c" a operar) elemento e (Elemento a encolar)
Devuelve:
Observaciones: El usuario a creado una cola y ha sido inicializada y c tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
void Queue(cola * c, elemento e)
{
	nodo* aux;
	aux= malloc(sizeof(nodo));
	if (aux==NULL){
		printf("ERROR: Queue (c,e) desbordamiento de cola");
		exit(1);
	}
	aux->e = e;
	aux->siguiente = NULL;
	if (c->num_elem > 0)
		c->final->siguiente = aux;
	c->final = aux;
	c->num_elem++;
	if (c->num_elem == 1)
		c->frente = c->final;
	return;
}

/*
elemento Dequeue(cola * c);
Descripcion: Recibe una cola y devuelve el elemento que se encuentra al
frente de esta, quitandolo de la cola.
Recibe: cola *c (Referencia a la cola "c" a operar)
Devuelve: elemento (Elemento desencolado)
Observaciones: El usuario a creado e inicializado una cola, ademas la cola tiene
elementos, si no es asi se genera un error y se termina el programa. (Subdesboramiento de Cola)
*/
elemento Dequeue(cola * c)
{
	nodo *aux;
	elemento e;//Elemento a retornar 
	if(c->num_elem==0)
	{
		printf("ERROR: Dequeue (c) subdesbordamiento de cola");
		exit(1);
	}
	else 
	{
		e=c->frente->e;
		aux=c->frente;
		c->frente=c->frente->siguiente;
		free(aux);
		c->num_elem--;
		if(c->num_elem==0)
			c->final=NULL;
	}

	//Retornar al elemento
	return e;
}

/*
boolean Empty(cola * c);
Descripcion: Recibe una cola y TRUE si la cola esta vacia y FALSE en caso contrario
Recibe: cola *c (Referencia a la cola "c" a verificar)
Devuelve: boolean TRUE O FALSE
Observaciones: El usuario a creado una cola y la cola fue correctamente inicializada
*/
boolean Empty(cola * c)
{
	
	return (c->num_elem==0)?TRUE:FALSE;
}

/*
elemento Front(cola * c);
Descripcion: Recibe una cola y devuelve el elemento que se encuentra al frente de esta.
Recibe: cola *c (Referencia a la cola "c")
Devuelve: elemento del frente de la cola
Observaciones: El usuario a creado una cola,la cola fue correctamente inicializada, esta
tiene elementos de lo contrario devolvera ERROR. *No se modifica el TAD
*/
elemento Front(cola * c)
{
	elemento e;
	
	e=c->frente->e;
	
	return e;
}

/*
elemento Final(cola * c);
Descripcion: Recibe una cola y devuelve el elemento que se encuentra al final de esta.
Recibe: cola *c (Referencia a la cola "c")
Devuelve: elemento del final de la cola
Observaciones: El usuario a creado una cola,la cola fue correctamente inicializada, esta
tiene elementos de lo contrario devolvera ERROR. *No se modifica el TAD
*/
elemento Final(cola * c)
{
	elemento e;	
	e=c->final->e;
	return e;
}

/*
int Size(cola * c);
Descripcion: Recibe una cola y devuelve el numero de elemento que se encuentran en esta.
Recibe: cola *c (Referencia a la cola "c")
Devuelve: int (TamaÃ±o de la cola)
Observaciones: El usuario a creado una cola,la cola fue correctamente inicializada, esta
*No se modifica el TAD
*/
int Size(cola * c)
{
	int r;
	r=c->num_elem;	
	return r;
}

/*
void Element(cola * c, int i);
Descripcion: Recibe una cola y un numero de elemento de 1 al tamaÃ±o de la cola y retorna el elemento de esa posicion.
Devuelve: elemento en la posicion i de la cola
Observaciones: El numero i debera estar entre 1 y el tamaÃ±o de la cola, si esta es vacia o mas pequeÃ±a se provoca un error.
*/
elemento Element(cola * c, int i)
{
	elemento r;
	nodo *aux;
	int j;
	
	if(i>c->num_elem || i<=0)
	{
		printf("ERROR: Element(c,i) i se encuentra fuera del rango");
		exit(1);
	}
	aux = c->frente;

	for(j=1;j<i;j++)
	{
		aux = aux->siguiente;
	}
	r = aux->e;

	return r;
}

/*
void Destroy(cola * c);
Descripcion: Recibe una cola y la libera completamente.
Recibe: cola *c (Referencia a la cola "c" a operar)
Devuelve:
Observaciones: La cola se destruye y se inicializa.
*/
void Destroy(cola * c)
{
	nodo *aux;
	
	aux = c->frente;
	while (aux!=NULL)
	{
		c->frente = aux->siguiente;
		free(aux);
		aux = c->frente;
	}
	c->num_elem = 0;
	c->frente = NULL;
	c->final = NULL;
	
	return;
}
void DibujaCaja(int num, int cliente)
{
	int columna,fila,i;
	//Recorrer cada columna
	for(columna=num+(num*8),i=0;i<ANCHO;columna++,i++)
	{
		//Recorrer cada fila 
		for(fila=1;fila<ALTO;fila++)
		{
			//Mover el cursor, dibujar un * y esperar TIEMPO_BASE milisegundos
			MoverCursor(columna,fila);
			printf("*");
			//EsperarMiliSeg(TIEMPO_BASE);
		};
	};
	
	MoverCursor(num+(num*8)+1,2);
	
	printf("A:0%d",cliente);
}



void MoverCursor( int x, int y ) 
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y }; 
	SetConsoleCursorPosition( hStdout, position );
	return;
};

//Funcion para esperar un tiempo en milisegundos, simulacion de la funcion delay() que se tenia en borland 3.0 en la libreria conio.h
void EsperarMiliSeg(int t)
{
	Sleep(t);
	return;
}

//Funcion para borrar la pantalla de la consola, simulacion de la funcion clrscr() que se tenia en borland 3.0 en la libreria conio.h
void BorrarPantalla(void)
{
	system("cls");
	return;
}
void AnimacionClienteAtendido() {
	MoverCursor(64,22);
    printf("Clientes atendidos!\n");
    Sleep(1000); // Pausa la ejecucion por 1 segundo (1000 milisegundos)
    MoverCursor(64,22);
    printf("En espera...        \n");
}
