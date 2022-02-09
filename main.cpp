#include <iostream>
#include <iomanip>
#include "indices.h"
#include "checkML.h"
using namespace std;


int main() {
	/*---DECLARACIÓN DE ARRAYS---*/
	tIndicePalabras tabla;
	tVisitado visitado;
	tNoVisitado novisitado;
	tMatriz L, M;
	tTotales totales;
	tVector v;
	tRelevancia rele;
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*---VARIABLES DEL MAIN---*/
	string nombre, bus;
	int cont = 0;

	/*-----MÓDULO 1-----*/

	/*---INICIO---*/
	cout << "Por favor, introduzca el nombre del fichero raiz" << endl;
	cout << "a partir del que se creara el indice : ";
	cin >> nombre;

	inicializa(tabla, visitado, novisitado, totales, L);
	
	
	novisitado.lista[novisitado.tam] = nombre;
	novisitado.tam++;

	totales.lista[totales.tam] = nombre;
	totales.tam++;
	L.data[0][0] = 0;

	/*---CREAR LA TABLA---*/

	while (novisitado.tam > 0) {							//Mientras haya un txt en no visitados se sigue creando la tabla
		
		crearTabla(tabla, nombre, novisitado, visitado, totales, cont, L);
		nombre = novisitado.lista[0];
		estaRepe(novisitado, visitado);						//Si está repetido en ambas listas, se borra de novisitados.
		
	}

	M = desdeEnlacesAMatriz(L);                             //Creamos la matriz M de la tabla.

	if (visitado.tam == cont) {
		cout << endl;
		cout << "Cargando...[CORRECTO]" << endl;
		cout << endl;
		cout << "Creando tablas...[CORRECTO]" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "La informacion ha sido cargada. Puede empezar a hacer busquedas." << endl;
		cout << endl;
		cout << "Introduzca una palabra (~fin~ para terminar):  ";
		
	/*-----MÓDULO 2-----*/

	/*---BUSCADOR DE INFORMACIÓN---*/

		do {
			cin >> bus;
			if (buscar(tabla, bus)) {
				int p = 0;
				p = getPosicion(tabla, bus);											//Para imprimirlo busca la posicion en donde se encuentra la palabra buscada.
				v = vectorPropio(M);
				imprimirM(tabla.pares[p].valor, totales, v, rele);						//Imprime por pantalla donde se encuentra la palabra.
				cout << endl;
				cout << "Introduzca una palabra (~fin~ para terminar):  ";
			}
			else if (bus == "fin") {
				cout << endl;
				cout << "Gracias por usar el buscador."  << endl;
				cout << endl;
			}
			else {
				cout << endl;
				cout << "Palabra no encontrada!" << endl;
				cout << "Vuelva a introducir otra palabra: ";
			}
		}while (bus != "fin");
	}

	/*---BORRADO DE MEMORIA---*/
	aborrarTodo(tabla, totales, visitado, novisitado);									//Libera la memoria de los punteros disponibles.
	system("pause");

	return 0;
}

