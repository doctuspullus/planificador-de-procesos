#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define ARCHIVO1 "./database/enrique.txt"

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
        cout << "Entre a proceso" << endl;
      } else {
        cout << "Entre a instrucciones" << endl;
      }
    }
  }
  archivo.close();

  return 0;

}