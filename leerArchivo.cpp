#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define ARCHIVO1 "./enrique.txt"

int main() {
  ifstream archivo;
  archivo.open(ARCHIVO1, ios::in | ios::binary);
  if (!archivo.is_open()) {
    cout << "Error al abrir el archivo" << endl;
  } else {
    string linea;
    char delimitador = ' ';
    while (!archivo.eof()) {  
      getline(archivo, linea);
      stringstream stream(linea);
      string instrucciones;
      getline(stream, instrucciones);
      
      cout << instrucciones << endl;
      string encontrar1 = "proceso";
      string encontrar2 = "fin proceso";
      int pos1 = instrucciones.find(encontrar1);
      int pos2 = instrucciones.find(encontrar2);
      if (pos2 != string::npos) {
        // introducir la última instrucción "fin proceso"
        // la lista de procesos cambie al siguiente con un null
        cout << "Entre a fin proceso" << endl;
      } else if (pos1 != string::npos) {
        stringstream stream1(linea);
        string proceso, nombrePrograma, numPrioridad;
        getline(stream1, proceso, delimitador);
        getline(stream1, nombrePrograma, delimitador);
        getline(stream1, numPrioridad, delimitador);
        cout << proceso << endl;
        cout << nombrePrograma << endl;
        cout << numPrioridad << endl;

        // crear una nueva lista al proceso
        cout << "Entre a proceso" << endl;
      } else {
        // introducir instrucción a la lista del proceso correspondiente
        cout << "Entre a instruccion" << endl;
      }
    }
  }
  archivo.close();

  return 0;

}