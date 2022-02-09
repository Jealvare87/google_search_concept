#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <ctype.h>
#include "indices.h"
#include <iomanip>
#include <windows.h>
using namespace std;

void crearTabla(tIndicePalabras & tabla, const string & archivoInicial, tNoVisitado & novisitado, tVisitado &visitado, tTotales & totales, int & cont, tMatriz & L) {

	ifstream archivo;
	string palabra;

	archivo.open(archivoInicial);						//Abre el archivo

	if (archivo.is_open()) {							//Si el archivo está abierto, entonces rellena la tabla.
			int j = tabla.cont;
			
			while (!archivo.eof()) {
				archivo >> palabra;
				transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);   //Convierte en minuscula la clave.
				
				if (palabra[0] == '<') {								//Si detecta un enlace lo guarda en no visitados.

					enlazar(novisitado, palabra, totales, L);
					meterL(L, cont, palabra, totales);
				}
				else {
					quitarPunt(palabra);								//Quita los signos de puntuacion antes de insertar.
					insertar(tabla, palabra, archivoInicial);
					
				}
				
			}
			L.tam = totales.tam;
			archivo.close();
			insertar(visitado, novisitado.lista[0]);
			
			for (int i = 0; i < novisitado.tam; i++) {					//Movemos el array sobreescribiendo el archivo visto.
				novisitado.lista[i] = novisitado.lista[i + 1];
				
			}
			novisitado.tam--;
			cont++;
	}

	else {
		
		novisitado.tam--;
	}

}

void inicializa(tIndicePalabras & tabla, tVisitado & visitado, tNoVisitado & novisitado, tListaCadenas & tTotales, tMatriz & matrix) {
	string nombre;

	tabla.dim = 2;
	insert(tabla);
	for (int i = 0; i < tabla.dim; i++) {						//Inicializa tabla
		tabla.pares[i].valor.tam = 0;
		tabla.pares[i].valor.dim = 15;
		insert(tabla.pares[i].valor);
		
	}
	tabla.cont = 0;

	visitado.dim = 2;
	novisitado.dim = 2;
	tTotales.dim = 2;

	insert(visitado);
	insert(novisitado);
	insert(tTotales);

	visitado.tam = 0;
	novisitado.tam = 0;
	tTotales.tam = 0;

	for (int k = 0; k < 50; k++) {
		for (int l = 0; l < 50; l++) {
			matrix.data[k][l] = 0.0;
		}
	}
	matrix.tam = 1;

}

void estaRepe(tNoVisitado & novisitado, const tVisitado & visitado) {

	for (int j = 0; j < visitado.tam; j++) {
		for (int i = 0; i < novisitado.tam; i++) {

			if (novisitado.lista[i] == visitado.lista[j]) {
				for (int p = i; p < novisitado.tam; p++) {					//Movemos el array sobreescribiendo el archivo repetido.
					novisitado.lista[p] = novisitado.lista[p + 1];
				}
				novisitado.tam--;
			}

		}
	}
}

void quitarPunt(string & aux) {
	unsigned int n = 0;
	string nombres;

	while ((aux[n] != '.') && (aux[n] != ',') && (n < aux.size())) {			//Quita signos de puntuacion antes de introducirlos
		nombres += aux[n];
		n++;
	}
	aux = nombres;
	nombres = "";
}

void enlazar(tNoVisitado & novisitado, string & aux, tTotales & totales, tMatriz & L) {
	int i = 1;
	string nombre;
	int cuent = 0;

	while (aux[i] != '>') {						//Con un auxiliar rehacemos el array de char para crear el string sin poner el ultimo signo no deseado.
		nombre += aux[i];
		i++;
	}
	aux = nombre;
	nombre = "";

	insertar(novisitado, aux);

	
	if (estaTotal(aux, totales) != true) {					//Si no lo ha encontrado en totales, lo mete en la lista y suma el contador.
		insertar(totales, aux);
	}
}

bool estaTotal(const string palabra, const tTotales totales) {
	bool encontrado = false;
	int i = 0;

	while ((encontrado == false) && (i < totales.tam)) {
		if (palabra == totales.lista[i]) {
			encontrado = true;
		}
		i++;
	}

	return encontrado;
}

int getPosicionT(tTotales & totales, const string palabra) {
	int pos1 = 0;
	bool enc = false;

	while (enc != true && pos1 < totales.tam) {
		if (totales.lista[pos1] == palabra) {
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

void meterL(tMatriz & L, const int cont, const string & aux, tTotales & totales) {
	int cuent = 0;
											//Si esta entonces metemos un uno
		cuent = getPosicionT(totales, aux);
		if (cuent != -1) {
			L.data[cuent][cont] = 1.0;
		}
}

void aborrarTodo(tIndicePalabras & tabla, tListaCadenas & L, tVisitado & visitado, tNoVisitado & novisitado) {
	
	for (int k = 0; k < tabla.dim; k++) {
		elimin(tabla.pares[k].valor);
	}
		elimin(tabla);
		elimin(L);
		elimin(visitado);
		elimin(novisitado);
}

void imprimirM(const tListaCadenas & l, tTotales & totales, tVector & v, tRelevancia & rele) {
	int i = 0;
	int pos = 0;
	bool encontrado = true;
	rele.cont = 0;
	rele.archivos.dim = 2;
	insert(rele.archivos);

	//Para ordenar la estructura.
	for (int g = 0; g < totales.tam; g++) {					//Copiamos el vector y la lista de totales a la estructura.
		if (rele.archivos.tam != rele.archivos.dim) {
			rele.archivos.lista[g] = totales.lista[g];
			rele.vector.data[g] = v.data[g];
			rele.cont++;
			rele.archivos.tam++;
		}
		else {
			redimensionar(rele.archivos);
			g--;
		}
	}
	rele.vector.tam = v.tam;
	rele.archivos.tam = totales.tam;

	ordenar(rele);											//Ordenamos mediante la estructura.

	cout << endl;											//Lo saca por pantalla.
	while (i < l.tam) {
		i = 0;
		for (int j = 0; j < rele.cont; j++) {
			encontrado = buscar(l, rele.archivos.lista[j]);
			if (encontrado == true) {
				cout << "Encontrado en " << setw(7) << rele.archivos.lista[j] << " (relevancia " << setprecision(2) << rele.vector.data[j] << ")" << endl;
				cout << endl;
				Sleep(300);										//Saca por pantalla con un retraso de tiempo pequeño.
				i++;
			}
		}
	}

		elimin(rele.archivos);
}

void ordenar(tRelevancia & r) {
	string nom = "";
	double j = 0.0;

	for (int i = 0; i < r.vector.tam - 1; i++) {			//Ordenamos la estructura por el método de la burbuja.
		for (int h = r.vector.tam - 1; h > i; h--) {
			if (r.vector.data[h] > r.vector.data[h - 1]) {
				nom = r.archivos.lista[h];
				j = r.vector.data[h];
				r.archivos.lista[h] = r.archivos.lista[h - 1];
				r.vector.data[h] = r.vector.data[h - 1];
				r.vector.data[h - 1] = j;
				r.archivos.lista[h - 1] = nom;
			}
		}
	}
}