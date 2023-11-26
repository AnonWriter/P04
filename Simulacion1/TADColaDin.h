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
*/

//Definiciones de constantes
#define TRUE	1
#define FALSE	0
#define ALTO 8			//Se piensa en un pantalla de 24 filas x 79 columnas
#define ANCHO 6
#define ESPACIO_ENTRE_CAJAS 2

//Definicion de tipos de dato

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;

//Definir un elemento (Se modela con una estructura "elemento")
typedef struct elemento
{
	//Variables de la estructura "elemento" (El usuario puede modificar)
	int n;
	int id;
	//***
	//***
	//***
} elemento;

//Definir la estructura de un nodo dinamico
typedef struct nodo
{
	elemento e;
	struct nodo *siguiente;
}nodo;

//Definir una cola 
typedef struct cola
{
	int num_elem;
	nodo *frente;
	nodo *final;
} cola;

//Declaracion de funciones
void Initialize(cola * c);			//Inicializar cola (Initialize): Recibe una cola y la inicializa para su trabajo normal.
void Queue(cola * c, elemento e);	//Encolar (Queue): Recibe una cola y agrega un elemento al final de ella. 
elemento Dequeue(cola * c);			//Desencolar (Dequeue): Recibe una cola y remueve el elemento del frente retornandolo.
boolean Empty(cola * c);			//Es vaciaa (Empty): Recibe la cola y devuelve verdadero si esta esta vacia.
elemento Front(cola * c);			//Frente (Front): Recibe una cola y retorna el elemento del frente.	
elemento Final(cola * c);			//Final (Final): Recibe una cola y retorna el elemento del final.
elemento Element(cola *c, int i); 	// Recibe una cola y un nÃƒÂºmero de elemento de 1 al tamaÃ±o de la cola y retorna el elemento de esa posicion.
int Size(cola *c);					//TamaÃƒÂ±o (Size): Retorna el tamaÃƒÂ±o de la cola 	
elemento Element(cola * c, int i);	//Recibe una cola y un nÃƒÂºmero de elemento de 1 al tamaÃ±o de la cola y retorna el elemento de esa posicion
void Destroy(cola * c);				//Eliminar cola (Destroy): Recibe una cola y la libera completamente.
void DibujaCaja(int num, int cliente);
void MoverCursor( int x, int y ); 	//Funcion para mover el cursor de escritura de pantalla, simulacion de la funcion gotoxy() que se tenia en borland 3.0 en la libreria conio.h

void EsperarMiliSeg(int t);			//Funcion para esperar un tiempo en milisegundos, simulacion de la funcion delay() que se tenia en borland 3.0 en la libreria conio.h

void BorrarPantalla(void);			//Funcion para borrar la pantalla de la consola, simulacion de la funcion clrscr() que se tenia en borland 3.0 en la libreria conio.h
void AnimacionClienteAtendido();
