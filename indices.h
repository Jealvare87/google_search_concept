#ifndef indices_h
#define indices_h

#include <string>
#include "clavevalor.h"
#include "matrices.h"

/*-------------------------------------------*/

typedef tListaCadenas tVisitado;
typedef tListaCadenas tNoVisitado;

typedef struct {
	tVector vector;
	tListaCadenas archivos;
	int cont;
}tRelevancia;

/*-------------------------------------------*/

void crearTabla(tIndicePalabras & tabla, const std::string & archivoInicial, tNoVisitado & novisitado, tVisitado &visitado, tTotales & totales, int & cont, tMatriz & L);
//A partir de archivoInicial, rellena la tabla tabla, tras haberla inicializado(a vacía).

void inicializa(tIndicePalabras & tabla, tVisitado & visitado, tNoVisitado & novisitado, tListaCadenas & tTotales, tMatriz & matrix);
//Inicializa la tabla y tambien inicializa los visitados.

void estaRepe(tNoVisitado & novisitado, const tVisitado & visitado);
//Si está repetido en ambas listas, borra la que está en no visitado.

void quitarPunt(std::string & aux);
//Quita signos de puntacion.

void enlazar(tNoVisitado & novisitado, std::string & aux, tTotales & totales, tMatriz & L);
//Quita los signos de los enlaces.

bool estaTotal(const std::string palabra, const tTotales totales);
//Si está en totales sale true;

int getPosicionT(tTotales & totales, const std::string palabra);
//Encuentra la posicion si está en totales.

void meterL(tMatriz & L, const int cont, const std::string & aux, tTotales & totales);
//Crea la matriz L a partir de los enlaces.

void aborrarTodo(tIndicePalabras & tabla, tListaCadenas & L, tVisitado & visitado, tNoVisitado & novisitado);
//Borra cada lista de cadenas de punteros.

void ordenar(tRelevancia & r);
//Ordena la estructura por el metodo de la burbuja.

void imprimirM(const tListaCadenas & l, tTotales & totales, tVector & v, tRelevancia & rele);
//Imprime por pantalla de forma ordenada, según la palabra introducida.

#endif // ! indices_h

