#include <iostream>
#include <scheduler.h>
#include <ui.h>

using namespace std;

UI::UI() : filename(""), scheduler(nullptr) {}

UI::~UI() {
	delete scheduler;
}

string UI::getFilename() {
	return filename;
}

Scheduler* UI::getScheduler() {
	return scheduler;
}

void UI::askForFileName() {
	int option;
	//cout << "Almacene el archivo a leer en ./database/ y inserte el nombre del archivo a procesar" << endl;
	while (true) {
		cout << "Elija el archivo a utilizar: [1: enrique.txt], [2: jonathan.txt], [3: jose.txt], [4: manfred.txt]" << endl;
		cin >> option;
		if (option==1) {
			filename = "database/enrique.txt";
			break;
		} else if (option == 2){
			filename = "database/jonathan.txt";
			break;
		} else if (option == 3){
			filename = "database/jose.txt";
			break;
		} else if (option == 4){
			filename = "database/manfred.txt";
			break;
		} else {
			cout << "Opción inválida, inténtelo de nuevo." << endl;
		}
	}
}

void UI::askForScheduler() {
	int option;
	while (true) {
		cout << "Elija el algoritmo de planificación a utilizar: [1: Round Robin], [2: Planificación por prioridad]" << endl; cin >> option;
		if (option==1) {
			scheduler = new RoundRobin();
			break;
		} else if (option == 2){
			scheduler = new Priority();
			break;
		} else {
			cout << "Opción inválida, inténtelo de nuevo." << endl;
		}
	}
}

//esto va antes de "schedule();" (line81 scheduler.cpp)
void UI::presentState(Scheduler* localScheduler) {
	cout << "Proceso: " << localScheduler->getCurrent()->getName()
		 << ", Prioridad: " << localScheduler->getCurrent()->getPriority() 
		 << ", Estado: " << localScheduler->getCurrent()->getState()
		 << ", Quantum Restante: " << localScheduler->getCurrent()->getQuantum() 
		 << "." << endl;
}

void UI::run() {
	askForFileName();
	askForScheduler();
}