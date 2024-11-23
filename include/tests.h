#pragma once
#include <iostream>
#include <process.h>

// Color Terminal Output Library
// MIT Licensed Library

// There are 6 colors:
//
// blue
// green
// cyan
// red
// magenta
// yellow

// Usage:
// color("red", "Error occured", true);
//       color  text           newLine

void color(std::string color, std::string line, bool newLine = false);

/// @brief Clase madre abstracta Tests de la que heredan las demas clases hijas.
/// Contiene atributos para llevar la cuenta del numero de pruebas realizadas y el numero de pruebas pasadas.
/// Contiene metodos para imprimir los resultados de una prueba, asi como un resumen al final de todo.
/// Contiene un constructor que inicializa sus atributos a 0.
/// Contiene un metodo abstracto runAllTests que debe de ser implementado en sus clases hijas segun las necesidades de cada una.
class Tests {
  protected:
    int testsRun;
    int testsPassed;

    void printTestResult(bool passed, const std::string& testName);
    void printTestSummary();
  
  public:
    Tests();
    /// @brief Metodo abstracto por implementar en las clases hijas.
    virtual void runAllTests() = 0; 
};

/// @brief Clase ProcessTests hija de Tests.
class ProcessTests : public Tests {
  public:
    void runAllTests() override;
    
    void testConstructor();
    void testStateTransitions();
    void testInstructions();
    void testIOOperations();
    void testPriorityComparisons();
    void testQuantumManagement();
};