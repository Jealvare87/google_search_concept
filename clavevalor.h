#ifndef clavevalor_h
#define clavevalor_h

#include "listacadenas.h"
#include <string>

/*-------------------------------------------*/

typedef struct {
	std::string clave;
	tListaCadenas valor;
}tRegistroIndicePalabras;

typedef tRegistroIndicePalabras tArrayPares;

typedef struct {
	int cont;
	int dim;
	tArrayPares* pares;
}tIndicePalabras;

/*-------------------------------------------*/

void insert(tIndicePalabras & l);
//Reserva espacios de memoria para un tipo Listacadenas para cada indice de palabras.

void elimin(tIndicePalabras & l);
//Borra la memoria reservada de la lista de cadenas en funcion del indice de palabras.

void redimensionar(tIndicePalabras & L);
//Redimensiona la lista de cadenas de clave y crea nuevos valores por cada clave creada.

bool buscar(const tIndicePalabras & l, const  std::string & s);
//Devuelve true si la palabra es una clave en la tabla, y false en caso contrario.

int buscar(const tIndicePalabras lista, const std::string buscado, int ini, int fin);
//Busqueda binaria dependiendo del inicio y el final introducido. En caso de no encontrarlo devuelve un -1.

int getPosicion(const tIndicePalabras & l, const std::string & s);
//Devuelve la posición del registro cuya clave es s, y ‐1 si no existe.

void insertar(tIndicePalabras & idx, const std::string & palabra, const std::string & nombreArchivo);
//Si palabra es ya una clave de la tabla, añade nombreArchivo a la lista de archivos correspondiente.
//Si no, crea un registro nuevo con esa información.

#endif // !clavevalor_h