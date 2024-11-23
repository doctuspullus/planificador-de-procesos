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
    instructionIndex(1), remainingQuantum(5), IOPending(false) {
  instructions = new SinglyLinkedList<string>();
  if (!instructions) {
    throw runtime_error("Failed to allocate memory for instructions list");
  }
  state = ProcessState::READY;
}

Process::Process(const string newName, int newPriority) 
  : name(newName), priority(newPriority),
    instructionIndex(1), remainingQuantum(5), IOPending(false) {
  instructions = new SinglyLinkedList<string>();
  if (!instructions) {
    throw runtime_error("Failed to allocate memory for instructions list");
  }
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

float Process::getQuantum() {
  return remainingQuantum;
}

void Process::setQuantum(float newQuantum) {
  remainingQuantum = newQuantum;
}

void Process::addInstruction(const string instruction) {
  instructions->insertTail(instruction);
}

bool Process::executeNextInstruction() {
  if (!instructions || state == ProcessState::FINISHED) {
    return false;
  }
  if (remainingQuantum <= 0) {
    state = ProcessState::RUNNING_PREEMPTED;
    return false;
  }
  if (this->hasMoreInstrucions()) {
    SinglyLinkedListNode<string>* node = instructions->getAt(instructionIndex);
    if (!node) {
      return false;
    }
    if (node->getData() == "e/s") {
      if (remainingQuantum > 1.5) {
        if (IOPending) {
          finishIO();
          return true;
        }
        startIO();
      } else {
        state = ProcessState::RUNNING_PREEMPTED;
      }
      return false;
    }
    sleepInSeconds(1);
    remainingQuantum--;
    instructionIndex++;
    if (instructionIndex > instructions->getSize()) {
      state = ProcessState::FINISHED;
    }
    return true;
  }
  return false;
}

bool Process::hasMoreInstrucions() const {
  return instructionIndex <= instructions->getSize();
}
void Process::resetExecution() {
  instructionIndex = 1;
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
  sleepInSeconds(1.5);
  remainingQuantum -= 1.5;
  instructionIndex++;
}

void Process::finishIO() {
  IOPending = false;
  state = ProcessState::READY;
  sleepInSeconds(1.5);
  remainingQuantum -= 1.5;
  instructionIndex++;
}

bool Process::operator<(const Process& other) {
  return this->priority < other.priority;
}

bool Process::operator>(const Process& other) {
  return this->priority > other.priority;
} 

void Process::sleepInSeconds(float seconds) {
#ifdef _WINDOWS32
  Sleep(seconds * 1000);
#else
  sleep(seconds);
#endif
}