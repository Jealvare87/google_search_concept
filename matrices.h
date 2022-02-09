#ifndef matrices_h
#define matrices_h
#include "listacadenas.h"

/*-------------------------------------------*/

const int MAX_DIM = 50;

typedef tListaCadenas tTotales;

typedef struct {
	int tam;
	double data[MAX_DIM];
} tVector;

typedef struct {
	int tam;
	double data[MAX_DIM][MAX_DIM];
} tMatriz;

/*-------------------------------------------*/

tMatriz matrizConstante(double x, int n);
//Crea una matriz de n * n, en la que todos los valores iniciales son x.

tVector operator*(const tMatriz & m, const tVector & v);
//Multiplica una matriz por un vector.

tMatriz operator*(double x, const tMatriz & m);
//Obtiene la matriz que se obtiene multiplicando cada elemento de m por x.

tMatriz operator+(const tMatriz & m1, const tMatriz & m2);
//Suma dos matrices.

tMatriz desdeEnlacesAMatriz(const tMatriz & L);
//Devuelve la matriz M obtenida de L como en la introducción de la sección 4.

tVector normaliza(const tVector & v);
//Devuelve un vector proporcional a v con la primera componente igual a 1.0.

tVector vectorPropio(const tMatriz & M);
//M es una matriz tal que todas sus columnas suman 1, devuelve un vector v con la primera componente igual a 1 tal que M ∙ v ≃ v.

int contarunos(const tMatriz & L, const int l);
//Cuenta cuantos unos hay en una columna.

bool bien(const tVector & w, const tVector & s);
//Si el cociente de los componentes de los vectores está entre 0.99999 y 1.00001 devuelve un true.

#endif // !matrices_h