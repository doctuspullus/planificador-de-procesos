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
  bool success = true;
  ifstream archivo;
  archivo.open(filename, ios::in | ios::binary);

  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo" << endl;
    success = false;
    return success;
  } else {
    string linea;
    char delimitador = ' ';
    while (getline(archivo, linea)) {  
      stringstream stream(linea);
      string instrucciones;
      getline(stream, instrucciones);

      string encontrar1 = "proceso";
      string encontrar2 = "fin proceso";
      size_t pos1 = instrucciones.find(encontrar1);
      size_t pos2 = instrucciones.find(encontrar2);
      Process nuevoProceso;

      // si llega al final del proceso
      if (pos2 != string::npos) {
        // introduce el proceso a la lista
        processes->insertHead(nuevoProceso);
      // si llega al encabezado
      } else if (pos1 != string::npos) {
        stringstream stream1(linea);
        string proceso, nombrePrograma, numPrioridad;
        getline(stream1, proceso, delimitador);
        getline(stream1, nombrePrograma, delimitador);
        getline(stream1, numPrioridad, delimitador);

        int priority = stoi(numPrioridad);
        // Pasar nombrePrograma, int numPrioridad
				Process* temp = new Process(nombrePrograma, priority);
        nuevoProceso = *temp;
				delete temp;
        processes->insertHead(nuevoProceso);
      // instrucciones del proceso
      } else {
        // introducir instrucción a la lista del proceso correspondiente
        nuevoProceso.addInstruction(instrucciones);
      }
    }
  }
  archivo.close();
  return success;
}

SinglyLinkedList<Process>* FileParser::getProcesses() {
  return processes;
}