#include "listacadenas.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void insert(tListaCadenas & L) {
	  L.lista = new tLista [L.dim];
	  L.tam = 0;
}

void elimin(tListaCadenas & L) {
	delete [L.dim] L.lista;
	L.tam = NULL;
	L.dim = NULL;
}

void redimensionar(tListaCadenas & L) {
	tListaCadenas B;

	B.dim = (L.dim * 3) / 2 + 1;
	insert(B);
	for (int i = 0; i < L.dim; i++) {
			B.lista[i] = L.lista[i];		
	}
	B.tam = L.tam;
	elimin(L);
	L.dim = B.dim;
	insert(L);
	L.tam = B.tam;
	for (int j = 0; j < L.dim; j++) {
		L.lista[j] = B.lista[j];
	}

	elimin(B);
}

void insertar(tListaCadenas & l, const string & s) {
	if (l.tam != l.dim) {
		if (!buscar(l, s)) {						//Si no se ha encontrado otro enlace igual, entonces rellena la lista.
			l.lista[l.tam] = s;
			l.tam++;
		}
	}
	else {
		redimensionar(l);
		insertar(l,s);
	}
}

bool buscar(const tListaCadenas & l, const string & s) {
	bool encontrado = false;
	int i = 0;

	while ((i < l.tam) && (encontrado == false)) {
		if (s == l.lista[i]) {
			encontrado = true;
		}
		else {
			i++;
		}
	}

	return encontrado;
}

void imprimir(const tListaCadenas & l) {

	cout << endl;
	for (int i = 0; i < l.tam; i++) {
		cout << endl;
		cout << "Encontrado en el archivo: " << setw(10) << l.lista[i] << " ";
	}
	cout << endl;
}

