#include <iostream>
#include <singlyLinkedList.hxx>

using namespace std;

/// @brief Enum para cambiar facilmente entre los distintos estados del proceso
enum class ProcessState {
  READY,
  RUNNING_ACTIVE,
  RUNNING_PREEMPTED,
  BLOCKED,
  FINISHED
};

/// @brief Sobrecarga del operador << para enviar un ProcessState a un stream de salida de manera que se pueda imprimir.
/// @param os El stream de salida al que se envia el ProcessState.
/// @param state El ProcessState que se envia.
/// @return El stream de salida.
ostream& operator<<(ostream& os, const ProcessState& state);

/// @brief Clase que representa un proceso.
/// Contiene: 1. nombre del proceso, 2. prioridad del proceso, 3. las instrucciones del proceso, 4. el estado del proceso,
/// 5. el indice de la instruccion en ejecucion, 6. el quantum que le queda al proceso, y 7. una bandera que indica si aun debe terminar una instruccion de E/S
class Process {
  private:
    string name;
    int priority;                     
    SinglyLinkedList<string>* instructions;
    ProcessState state;
    int instructionIndex;
    float remainingQuantum;          
    bool IOPending;
    
  public:
  /// @brief Constructor de Process.
  Process();
  /// @brief Constructor parametrizado de Process.
  /// @param newName El nombre del nuevo proceso.
  /// @param newPriority La prioridad del nuevo proceso.
  Process(const string newName, int newPriority);
  /// @brief Destructor de Process.
  ~Process();
  
  /// @brief Getter del nombre del proceso.
  /// @return El nombre del proceso.
  const string getName() const;
  /// @brief Getter de la prioridad del proceso.
  /// @return La prioridad del proceso.
  int getPriority() const;
  /// @brief Getter del estado del proceso.
  /// @return El estado del proceso.
  ProcessState getState() const;
  /// @brief Setter del estado del proceso.
  /// @param newState El nuevo estado al que pasa el proceso.
  void setState(ProcessState newState);

  /// @brief Añade una nueva instruccion al proceso.
  /// @param instruction La nueva instruccion que se va a añadir.
  void addInstruction(const string instruction);
  /// @brief Simula la ejecucion de la siguiente instruccion en la lista.
  /// @return True si logra ejecutarla; false si el proceso se corta (quantum insuficiente) o se bloquea (E/S).
  bool executeNextInstruction();
  /// @brief Revisa si quedan instrucciones en el proceso.
  /// @return True si sí; false si no.
  bool hasMoreInstrucions() const;
  /// @brief Reinicia la ejecucion del proceso al principio.
  void resetExecution();

  /// @brief Revisa si el proceso esta bloqueado (en E/S).
  /// @return True si sí; false si no.
  bool isInIO() const;
  /// @brief Bloquea el proceso para simular que esta en E/S.
  void startIO();
  /// @brief Desbloquea el proceso para simular que sale de E/S.
  void finishIO();
  
  /// @brief Sobrecarga del operador <. Realiza la comparacion mediante la prioridad del proceso.
  /// @param other El otro proceso con el que se compara.
  /// @return True si este tiene menor prioridad que el otro; false si no.
  bool operator<(const Process& other);
  /// @brief Sobrecarga del operador >. Realiza la comparacion mediante la prioridad del proceso.
  /// @param other El otro proceso con el que se compara.
  /// @return True si este tiene mayor prioridad que el otro; false si no.
  bool operator>(const Process& other);
  
  /// @brief Metodo multiplataforma para pausar el programa durante una cierta cantidad de segundos.
  /// @param seconds Los segundos por los que el programa debe de pausarse.
  void sleepInSeconds(int seconds);
};