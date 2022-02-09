#include "clavevalor.h"
#include <iostream>
#include <fstream>
using namespace std;

void insert(tIndicePalabras & l) {
	l.pares = new tArrayPares[l.dim];
	l.cont = 0;
}

void elimin(tIndicePalabras & l) {
	delete[l.dim] l.pares;
	l.cont = 0;
	l.dim = 0;
}

void redimensionar(tIndicePalabras & L) {
	tIndicePalabras B;
	
	B.dim = (L.dim * 3) / 2 + 1;
	insert(B);
	for (int i = 0; i < L.dim; i++) {
		B.pares[i] = L.pares[i];
		}
	B.cont = L.cont;

	for (int i = B.cont; i < B.dim; i++) {						//Inicializa tabla
		B.pares[i].valor.tam = 0;
		B.pares[i].valor.dim = 2;
		insert(B.pares[i].valor);
	}
	elimin(L);
	L.dim = B.dim;
	insert(L);
	L.cont = B.cont;
	for (int j = 0; j < L.dim; j++) {
		L.pares[j] = B.pares[j];
	}
	for (int i = B.cont; i < L.dim; i++) {						//Inicializa tabla
		L.pares[i].valor.tam = 0;
		L.pares[i].valor.dim = 2;
		insert(L.pares[i].valor);
	}
	elimin(B);
	
}

bool buscar(const tIndicePalabras & l, const  string & s) {	
	bool enc = false;
	int i = 0;

	i = buscar(l, s, 0, l.cont - 1);
	if (i != -1) {
	enc = true;
	}
	else {
	enc = false;
	}
	return enc;
	
}

int buscar(const tIndicePalabras lista, const string buscado, int ini, int fin) {
	int pos = -1;
	if (ini <= fin) {
		int mitad = (ini + fin) / 2;
		if (buscado == lista.pares[mitad].clave) {
			pos = mitad;
		}
		else if (buscado < lista.pares[mitad].clave) {
			pos = buscar(lista, buscado, ini, mitad - 1);
		}
		else {
			pos = buscar(lista, buscado, mitad + 1, fin);
		}
	}
	return pos;
}

int getPosicion(const tIndicePalabras & l, const string & s) {					
	int pos1 = 0;
	bool enc = false;
	
	while (enc != true && pos1 < l.cont) {
		if (l.pares[pos1].clave == s) {
			enc = true;
		}
		else {
			pos1++;
		}
	}
	if (enc == false) {
		pos1 = -1;
	}
	return pos1;
}

void insertar(tIndicePalabras & idx, const string & palabra, const string & nombreArchivo) {
		int pos = 0;

		if (idx.cont != idx.dim) {
			while ((pos < idx.cont) && (idx.pares[pos].clave < palabra)) {
				pos++;
			}

			if (idx.pares[pos].clave == palabra) {

				insertar(idx.pares[pos].valor, nombreArchivo);
			}
			else {
				for (int j = idx.cont; j > pos; j--) {
					idx.pares[j] = idx.pares[j - 1];
				}
				insert(idx.pares[pos].valor);
				idx.pares[pos].valor.tam = 0;
				idx.pares[pos].clave = palabra;
				insertar(idx.pares[pos].valor, nombreArchivo);
				idx.cont++;
			}
		}
		else {
			redimensionar(idx);
			insertar(idx, palabra, nombreArchivo);
		}
}

