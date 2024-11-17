#include <string>
#include <process.h>
#ifdef _WINDOWS32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

ostream& operator<<(ostream& os, const ProcessState& state) {
  switch (state) {
    case ProcessState::READY:
      os << "READY";
      break;
    case ProcessState::RUNNING_ACTIVE: 
      os << "RUNNING_ACTIVE"; 
      break;
    case ProcessState::RUNNING_PREEMPTED: 
      os << "RUNNING_PREEMPTED"; 
      break;
    case ProcessState::BLOCKED: 
      os << "BLOCKED"; 
      break;
    case ProcessState::FINISHED: 
      os << "FINISHED"; 
      break;
    default: 
      os << "UNKNOWN"; 
      break;
  }
  return os;
}

Process::Process() 
  : name("null"), priority(0), 
    instructionIndex(0), remainingQuantum(0), IOPending(false) {
  instructions = new SinglyLinkedList<string>();
  state = ProcessState::READY;
}

Process::Process(const string newName, int newPriority) 
  : name(newName), priority(newPriority),
    instructionIndex(0), remainingQuantum(0), IOPending(false) {
  instructions = new SinglyLinkedList<string>();
  state = ProcessState::READY;
}

Process::~Process() {
  delete instructions;
}

const string Process::getName() const {
  return name;
}

int Process::getPriority() const {
  return priority;
}

ProcessState Process::getState() const {
  return state;
}

void Process::setState(ProcessState newState) {
  state = newState;
}

void Process::addInstruction(const string instruction) {
  instructions->insertTail(instruction);
}

bool Process::executeNextInstruction() {
  if (this->hasMoreInstrucions()) {
    string currentInstruction = instructions->getAt(instructionIndex)->getData();
    if (currentInstruction == "io") {
      startIO();
      instructionIndex++;
      return false;
    }
    sleepInSeconds(1);
    remainingQuantum--;
    instructionIndex++;
    return true;
  }
  return false;
}

bool Process::hasMoreInstrucions() const {
  return instructionIndex < instructions->getSize();
}
void Process::resetExecution() {
  instructionIndex = 0;
  remainingQuantum = 0;
  IOPending = false;
  state = ProcessState::READY;
}

bool Process::isInIO() const {
  return IOPending;
}

void Process::startIO() {
  IOPending = true;
  state = ProcessState::BLOCKED;
}

void Process::finishIO() {
  IOPending = false;
  state = ProcessState::READY;
}

bool Process::operator<(const Process& other) {
  return this->priority < other.priority;
}

bool Process::operator>(const Process& other) {
  return this->priority > other.priority;
}

void Process::sleepInSeconds(int seconds) {
#ifdef _WINDOWS32
  Sleep(seconds * 1000);
#else
  sleep(seconds);
#endif
}