#include "matrices.h"
#include <iostream>
#include <iomanip>
using namespace std;

tMatriz matrizConstante(double x, int n){
	tMatriz matrixc;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrixc.data[i][j] = 0.15 * x;
			}
		}

	return matrixc;
}

tVector operator*(const tMatriz & m, const tVector & v) {
	tVector x;
	double y = 0.0;
	
	for (int i = 0; i < m.tam; i++) {
		for (int j = 0; j < m.tam; j++) {
			y += v.data[j] * m.data[i][j];
		}
		x.data[i] = y;
		y = 0.0;
	}

	x.tam = v.tam;
	return x;
}

tMatriz operator*(double x, const tMatriz & m) {
	tMatriz MP;
	for (int i = 0; i < m.tam; i++) {
		for (int j = 0; j < m.tam; j++) {
			MP.data[i][j] = x * m.data[i][j];
		}
	}
	MP.tam = m.tam;

	return MP;
}

tMatriz operator+(const tMatriz & m1, const tMatriz & m2) {
	
	tMatriz m3;
	
	for (int i = 0; i < m1.tam; i++) {
		for (int j = 0; j < m1.tam; j++) {
			m3.data[i][j] = m1.data[i][j] + m2.data[i][j];
		}
	}

	return m3;
}

tMatriz desdeEnlacesAMatriz(const tMatriz & L) {

	double n = 0;
	double c = 0.85;
	double x = 0;
	double y = 0;

	tMatriz mh;													//(1 - c) * 1 / n
	tMatriz mk;													//c * M'
	
	y = (1.0 / L.tam);
	
	mh = matrizConstante(y, L.tam);			//Cn
	for (int i = 0; i < L.tam; i++) {							//M = (1-c) * 1 / n + c * M'
			for (int j = 0; j < L.tam; j++) {
				n = contarunos(L, j);
				if (n != 0) {
					
					if (L.data[i][j] != 0) {
						
						mk.data[i][j] = 1.0 / n;
					}
					else {
						mk.data[i][j] = 0.0;
					}		
				}
				else {
					mk.data[i][j] = 1.0 / L.tam;
				}
			}
	}
	mh.tam = L.tam;
	mk.tam = L.tam;
	mk = c * mk;
	
	mh = mh + mk;

	mh.tam = L.tam;

	return mh;
}

int contarunos(const tMatriz & L, const int l) {
	int uno = 0;
	
	for (int i = 0; i < L.tam; i++) {
		if (L.data[i][l] != 0) {
			uno++;
		}
	}

	return uno;
}

tVector normaliza(const tVector & v) {
	tVector vx;

	for (int i = 0; i < v.tam; i++) {
		vx.data[i] = v.data[i] / v.data[0];
	}

	vx.tam = v.tam;

	return vx;
}

tVector vectorPropio(const tMatriz & M) {
	tVector w;
	tVector s;
	tVector t;

	w.tam = M.tam;

	for (int i = 0; i < M.tam; i++) {
		w.data[i] = 1.0;
	}

	s = M * w;

	while (!bien(w, s)) {						//Hasta que la division de w entre s no esté entre 0.9999 y 1.0001, sigue modificándolo.
		w = s;
		s = M * w;
	}

	t = normaliza(s);
	t.tam = M.tam;
	return t;
}

bool bien(const tVector & w, const tVector & s) {
	bool ok = false;
	int i = 0;
	int j = 0;
	double num = 0.0;

	while (i < w.tam) {
		num = w.data[i] / s.data[i];
		if ((num > 0.9999999) && (num < 1.0000001)) {
			j++;
		}
		num = 0.0;
		i++;
	}
	if (j == w.tam) {
		ok = true;
	}
	return ok;
}
