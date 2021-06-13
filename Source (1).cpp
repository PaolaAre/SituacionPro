#include <iostream>
#include <string>
#include "Header.h"

using namespace std;


int main() {
	Manager manager;
	manager.option = 0;
	bool loop = true;
	while (loop) {
		cout << endl << "1. Cargar archivo de datos.\n";
		cout << "2. Mostrar los videos en general con una cierta calificacion o de un cierto genero.\n";
		cout << "3. Mostrar los episodios de una determinada serie con una calificacion determinada.\n";
		cout << "4. Mostrar las peliculas con cierta calificacion.\n";
		cout << "5. Calificar un video.\n";
		cout << "0. Salir.\n";
		cout << "Opcion: ";
		cin >> manager.option;
		switch (manager.option) {
		case 0:
			loop = false;
			break;
		case 1:
			manager.option1();
			break;
		case 2:
			manager.option2();
			break;
		case 3:
			manager.option3();
			break;
		case 4:
			manager.option4();
			break;
		case 5:
			manager.option5();
			break;

		}
	}
}