#include <iostream>
#include <singlyLinkedList.hxx>

using namespace std;

enum class ProcessState {
  READY,
  RUNNING_ACTIVE,
  RUNNING_PREEMPTED,
  BLOCKED,
  FINISHED
};

ostream& operator<<(ostream& os, const ProcessState& state);

class Process {
  private:
    string name;
    int priority;                     // prioridad del proceso (0-10)
    SinglyLinkedList<string>* instructions;
    ProcessState state;
    int instructionIndex;
    float remainingQuantum;             // tiempo restante en quantum
    bool IOPending;
    
  public:
  // constructor y destructor
  Process();
  Process(const string newName, int newPriority);
  ~Process();
  
  // getters y setters
  const string getName() const;
  int getPriority() const;
  ProcessState getState() const;
  void setState(ProcessState newState);

  // manejo de procesos
  void addInstruction(const string instruction);
  bool executeNextInstruction();
  bool hasMoreInstrucions() const;
  void resetExecution();

  // IO
  bool isInIO() const;
  void startIO();
  void finishIO();
  
  // sobrecarga
  bool operator<(const Process& other);
  bool operator>(const Process& other);
};