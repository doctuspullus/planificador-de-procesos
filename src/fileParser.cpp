#include <fileParser.h>
#include <process.h>
#include <singlyLinkedList.hxx>
#include <fstream>
#include <iostream>
using namespace std;

FileParser::FileParser() : filename("null"){
  processes = new SinglyLinkedList<string>();
  if (!processes) {
    throw runtime_error("Failed to allocate memory for process");
  }
}

FileParser::FileParser(const char* inputFile) : filename(inputFile){
  ifstream archivo;
  processes = new SinglyLinkedList<strings>();
  if (!processes) {
    throw runtime_error("Failed to allocate memory for process");
  }
}

FileParser::~FileParser() {
  delete processes;
}

bool FileParser::parseFile() {
  bool success = 1;
  ifstream archivo;
  archivo.open(ARCHIVO1, ios::in | ios::binary);
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo" << endl;
    success = 0;
    return success;
  } else {
    string linea;
    char delimitador = ' ';
    while (!archivo.eof()) {  
      getline(archivo, linea);
      stringstream stream(linea);
      string instrucciones;
      getline(stream, instrucciones);
      string encontrar1 = "proceso";
      string encontrar2 = "fin proceso";
      int pos1 = instrucciones.find(encontrar1);
      int pos2 = instrucciones.find(encontrar2);
      Process nuevoProceso;
      // si llega al final del proceso
      if (pos2 != string::npos) {
        // introducir la última instrucción "fin proceso"
        processes->insertHead();
      // si llega al encabezado
      } else if (pos1 != string::npos) {
        stringstream stream1(linea);
        string proceso, nombrePrograma, numPrioridad;
        getline(stream1, proceso, delimitador);
        getline(stream1, nombrePrograma, delimitador);
        getline(stream1, numPrioridad, delimitador);
        int priority = stoi(numPrioridad);
        // Pasar nombrePrograma, int numPrioridad
        nuevoProceso = new Process(nombrePrograma, priority);
        processes->insertHead(nuevoProceso);
      // instrucciones del proceso
      } else {
        // introducir instrucción a la lista del proceso correspondiente
        processes->insertTail(instrucciones);
      }
    }
  }
  archivo.close();
  return success;
}

SinglyLinkedList<Process>* FileParser::getProcesses() {
  return processes;
}