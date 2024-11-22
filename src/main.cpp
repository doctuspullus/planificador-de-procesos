#include <iostream>
using namespace std;

void evaluate() {
  int seleccion = 0, tipo = 0;
  bool data = 1;
  while (data) {
    cout << "Seleccionar un archivo: \n1. enrique.txt \n2. jonathan.txt \n3. jose.txt \n4. manfred.txt" << endl;
    cin >> seleccion;
    if (seleccion > 0 && seleccion <= 4) {
      data = 0;
    } else {
      cerr << "Seleccion de archivo fuera de rango, por favor intente de nuevo\n" << endl;
    }
  }
  data++;
  while (data) {
    cout << "Seleccionar el tipo de procesamiento: \n1. Round Robin \n2. Priority" << endl;
    cin >> tipo;
    if (tipo == 1 || tipo == 2) {
      data = 0;
    } else {
      cerr << "Seleccion de tipo fuera de rango, por favor intente de nuevo\n" << endl;
    }
    
  }
}

void runProgram() {
  evaluate();
}

int main() {
  runProgram();
  return 0;
}