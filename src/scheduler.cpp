#include <scheduler.h>
#include <iostream>

Scheduler::Scheduler() : currentProcess(nullptr) {
	readyQueue = new SinglyLinkedList<Process>();
	blockedQueue = new SinglyLinkedList<Process>();
	finishedProcesses = new SinglyLinkedList<Process>();
	ioTimer = new Timer(15);
}

Scheduler::~Scheduler() {
	cout << "Scheduler" << endl;
	delete readyQueue;
	delete blockedQueue;
	delete finishedProcesses;
	delete ioTimer;
}

void Scheduler::run() {
	while (hasUnfinishedProcesses()) {
		checkBlockedProcesses();
		executeQuantum();
		schedule();
		displayStatus();
	}
}

void Scheduler::addProcess(Process* newProcess) {
	readyQueue->insertTail(*newProcess);
}

void Scheduler::removeProcess(Process* process) {
	switch(process->getState()) {
		case ProcessState::READY:
			readyQueue->deleteByValue(*process);
			break;
		case ProcessState::BLOCKED:
			blockedQueue->deleteByValue(*process);
			break;
		case ProcessState::FINISHED:
			finishedProcesses->deleteByValue(*process);
			break;
		default:
			break;
	}
}

void Scheduler::schedule() {
	currentProcess = selectNextProcess();
	
	if (currentProcess) {
		currentProcess->setState(ProcessState::RUNNING_ACTIVE);
	}
}

void Scheduler::executeQuantum() {
	if (!currentProcess) {
		schedule();
		return;
	}

	switch(currentProcess->getState()) {
		case ProcessState::FINISHED:
			moveToFinished(currentProcess);
			break;
		case ProcessState::BLOCKED:
			moveToBlocked(currentProcess);
			break;
		case ProcessState::RUNNING_PREEMPTED:
			moveToReady(currentProcess);
			break;
		default:
			break;
	}

	checkBlockedProcesses();
}

void Scheduler::preemptCurrentProcess() {
	if (currentProcess) {
		currentProcess->setState(ProcessState::RUNNING_PREEMPTED);
		moveToReady(currentProcess);
	}
}

void Scheduler::checkBlockedProcesses() {
	if (blockedQueue->getHead()) {
		if (ioTimer->getStartTime().time_since_epoch() == steadyClock::duration::zero()) {
			ioTimer->start();
		}
		if (ioTimer->checkTime()) {
			Process process = blockedQueue->getTail()->getData();
			moveToReady(&process);
			clearTimer();
		}
	}
}

void Scheduler::handleProcessStateChange(Process* process, ProcessState newState) {
	process->setState(newState);
	
	switch(newState) {
		case ProcessState::READY:
			moveToReady(process);
			break;
		case ProcessState::BLOCKED:
			moveToBlocked(process);
			break;
		case ProcessState::FINISHED:
			moveToFinished(process);
			break;
		default:
			break;
	}
}

void Scheduler::moveToReady(Process* process) {
	removeProcess(process);
	
	process->setState(ProcessState::READY);
	readyQueue->insertTail(*process);
}

void Scheduler::moveToBlocked(Process* process) {
	removeProcess(process);
	
	process->setState(ProcessState::BLOCKED);
	blockedQueue->insertTail(*process);
}

void Scheduler::moveToFinished(Process* process) {
	removeProcess(process);
	
	process->setState(ProcessState::FINISHED);
	finishedProcesses->insertTail(*process);
}

bool Scheduler::hasUnfinishedProcesses() const {
	return readyQueue->getHead() != nullptr || blockedQueue->getHead() != nullptr;
}

void Scheduler::clearTimer() {
	Timer* old = ioTimer;
	ioTimer = new Timer(15);
	delete old;
}

void Scheduler::displayStatus() const {
	cout << "Ready Queue Size: " << readyQueue->getSize() << endl;
	cout << "Blocked Queue Size: " << blockedQueue->getSize() << endl;
	cout << "Finished Processes Size: " << finishedProcesses->getSize() << endl;
}

RoundRobin::RoundRobin() : Scheduler(), quantumSlice(5) {
	preemptedQueue = new SinglyLinkedList<Process>();
}

RoundRobin::~RoundRobin() {
	delete preemptedQueue;
	Scheduler::~Scheduler();
}

Process* RoundRobin::selectNextProcess() {
	if (readyQueue->getHead() == nullptr) {
		return nullptr;
	}

	Process process = readyQueue->getHead()->getData();
	readyQueue->deleteByValue(process);
	process.setQuantum(quantumSlice);
	Process* p1 = &process;
	return p1;
}

Priority::Priority() : Scheduler() {
	priorityQueue = new BinarySearchTree<Process>();
}

Priority::~Priority() {
	delete priorityQueue;
	Scheduler::~Scheduler();
}

Process* Priority::selectNextProcess() {
	if (priorityQueue->getRoot() == nullptr) {
		return nullptr;
	}

	Process process = priorityQueue->getMax()->getData();
	priorityQueue->remove(process);
	Process* p1 = &process;
	return p1;
}

void Priority::calculateInitialPriority(Process& process) {
	int priority = 0;
	SinglyLinkedListNode<string>* current = process.getInstructions()->getHead();
	while (current) {
		if (current->getData() == "e/s") {
			priority = max(0, priority - 1);
		} else {
			priority = min(10, priority + 1);
		}
		current = current->getNext();
	}
	process.setPriority(priority);
}

void Priority::moveToBlocked(Process* process) {
	Scheduler::moveToBlocked(process);
}

void Priority::addProcess(Process* newProcess) {
	calculateInitialPriority(*newProcess);
	priorityQueue->insert(*newProcess);
}

void Priority::adjustProcessPriority(Process& process, int newPriority) {
	priorityQueue->remove(process);
	
	int temp = process.getPriority();
	SinglyLinkedListNode<string>* current = process.getInstructions()->getAt(process.getInstructionIndex());
	while (current) {
		if (current->getData() == "e/s") {
			temp = max(0, temp -1);
		} else {
			temp = min(10, temp +1);
		} 
		current = current->getNext();
	}
	process.setPriority(temp);
	
	priorityQueue->insert(process);
}