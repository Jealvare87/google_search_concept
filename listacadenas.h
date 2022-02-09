#ifndef listacadenas_h
#define listacadenas_h

#include <string>

/*-------------------------------------------*/

const int N = 50;

typedef std::string tLista;

typedef struct {
	tLista *lista;
	int tam;
	int dim;
}tListaCadenas;

/*-------------------------------------------*/

void insert(tListaCadenas & L);
//Reserva memoria del puntero segun la dimension.

void elimin(tListaCadenas & L);
//Elimina los punteros reservados en memoria.

void redimensionar(tListaCadenas & L);
//Redimensiona la lista de cadenas ayudandose con otro lista de cadenas generado.

void insertar(tListaCadenas & l, const std::string & s);
//Inserta un elemento al final de la lista.

bool buscar(const tListaCadenas & l, const std::string & s);
//Devuelve true si la cadena está en la lista, y false si no.

void imprimir(const tListaCadenas & l);
//Imprime los elementos de la lista.

#endif // !listacadenas_h