#include <fileParser.h>
#include <process.h>
#include <singlyLinkedList.hxx>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

FileParser::FileParser() : filename("null"){
  processes = new SinglyLinkedList<Process>();
  if (!processes) {
    throw runtime_error("Failed to allocate memory for process");
  }
}

FileParser::FileParser(const string inputFile) : filename(inputFile){
  ifstream archivo;
  processes = new SinglyLinkedList<Process>();
  if (!processes) {
    throw runtime_error("Failed to allocate memory for process");
  }
}

FileParser::~FileParser() {
  delete processes;
}

bool FileParser::parseFile(string filename) {
  ifstream archivo;
  archivo.open(filename, ios::in | ios::binary);

  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo" << endl;
    return false;
  } 

	string linea;
	char delimitador = ' ';
	Process* nuevoProceso = nullptr;

	while (getline(archivo, linea)) {  
		stringstream stream(linea);
		string instrucciones;
		getline(stream, instrucciones);

		string encontrar1 = "proceso";
		string encontrar2 = "fin proceso";
		size_t pos1 = instrucciones.find(encontrar1);
		size_t pos2 = instrucciones.find(encontrar2);

		// si llega al final del proceso
		if (pos2 != string::npos) {
			if (nuevoProceso) {
				processes->insertHead(*nuevoProceso);
				delete nuevoProceso;
				nuevoProceso = nullptr;
			}
		// si llega al encabezado
		} else if (pos1 != string::npos) {
			stringstream stream1(linea);
			string proceso, nombrePrograma, numPrioridad;
			getline(stream1, proceso, delimitador);
			getline(stream1, nombrePrograma, delimitador);
			getline(stream1, numPrioridad, delimitador);

			// Pasar nombrePrograma, int numPrioridad
			int priority = stoi(numPrioridad);
			nuevoProceso = new Process(nombrePrograma, priority);
		// instrucciones del proceso
		} else {
			// introducir instrucción a la lista del proceso correspondiente
			nuevoProceso->addInstruction(instrucciones);
		}
	}
	if (nuevoProceso) {
		delete nuevoProceso;	
	}

  archivo.close();
  return true;
}

SinglyLinkedList<Process>* FileParser::getProcesses() {
  return processes;
}