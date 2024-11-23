#pragma once

#include <iostream>
#include <scheduler.h>
#include <ui.h>


using namespace std;

void UI::askForFileName() {
	int option;
	string fileName
	//cout << "Almacene el archivo a leer en ./database/ y inserte el nombre del archivo a procesar" << endl;
	cout << "Elija el archivo a utilizar: [1: enrique.txt], [2: jonathan.txt], [3: jose.txt], [4: manfred.txt]" << endl;
	cin >> option;
	if (option==1) {
		fileName = "enrique.txt"
	} else if (option == 2){
		fileName = "jonathan.txt"
	} else if (option == 3){
		fileName = "jose.txt"
	} else if (option == 4){
		fileName = "manfred.txt"
	} else {
		cout << "Invalid Option, try again." << endl;
		askForFileName(); //Lo ultimo del metodo, no debería haber problemas de recursividad
	}


void UI::askForScheduler() {
	int option;
	cout << "Elija el Scheduler a utilizar: [2: ForPriority], [2: RoundRobin]" << endl;
	cin >> option;
	if (option==1) {
		RoundRobin* scheduler = new RoundRobin();
	} else if (option == 2){
		Priority* scheduler = new Priority();
	} else {
		cout << "Invalid Option, try again." << endl;
		askForScheduler(); //Lo ultimo del metodo, no debería haber problemas de recursividad
	}


//esto va antes de "schedule();" (line81 scheduler.cpp)
void UI::presentState() {
	
	cout << "Proceso: " << scheduler.getName() 
		 << ", Prioridad: " << scheduler.getPriority 
		 << ", Estado: " << scheduler.getState() 
		 << ", Quantum Restante: " << scheduler.getQuantum 
		 << "." << endl;


void UI::run() {
	askForFileName()
	askForScheduler();
}