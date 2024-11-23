#include <scheduler.h>
#include <ui.h>
#include <iostream>

Scheduler::Scheduler() : currentProcess(nullptr) {
	readyQueue = new SinglyLinkedList<Process>();
	blockedQueue = new SinglyLinkedList<Process>();
	finishedProcesses = new SinglyLinkedList<Process>();
	ioTimer = new Timer(15);
}

Scheduler::~Scheduler() {
	delete readyQueue;
	readyQueue = nullptr;
	delete blockedQueue;
	blockedQueue = nullptr;
	delete finishedProcesses;
	finishedProcesses = nullptr;
	delete currentProcess;
	currentProcess = nullptr;
	delete ioTimer;
	readyQueue = nullptr;
}

void Scheduler::run() {
	UI* ui = new UI();
	while (hasUnfinishedProcesses()) {
		checkBlockedProcesses();
		executeQuantum();
		ui->presentState(this);
		schedule();
		displayStatus();
	}
	delete ui;
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
	selectNextProcess();
	
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
		currentProcess = nullptr;
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
	
	if (process == currentProcess) {
		currentProcess = nullptr;
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
	cout << "Ready Processes: " << readyQueue->getSize() << endl;
	cout << "Blocked Processes: " << blockedQueue->getSize() << endl;
	cout << "Finished Processes: " << finishedProcesses->getSize() << endl;
}

Process* Scheduler::getCurrent() {
	return currentProcess;
}

RoundRobin::RoundRobin() : Scheduler(), quantumSlice(5) {
	preemptedQueue = new SinglyLinkedList<Process>();
}

RoundRobin::~RoundRobin() {
	delete preemptedQueue;
	preemptedQueue = nullptr;
	delete readyQueue;
	readyQueue = nullptr;
	delete blockedQueue;
	blockedQueue = nullptr;
	delete finishedProcesses;
	finishedProcesses = nullptr;
	delete currentProcess;
	currentProcess = nullptr;
	delete ioTimer;
	ioTimer = nullptr;
}

void RoundRobin::selectNextProcess() {
	if (currentProcess) {
		delete currentProcess;
		currentProcess = nullptr;
	}
	if (readyQueue->getHead() == nullptr) {
		return;
	}

	Process process = readyQueue->getHead()->getData();
	readyQueue->deleteByValue(process);
	process.setQuantum(quantumSlice);
	currentProcess = new Process(process);
}

Priority::Priority() : Scheduler() {
	priorityQueue = new BinarySearchTree<Process>();
}

Priority::~Priority() {
	delete priorityQueue;
	priorityQueue = nullptr;
	delete readyQueue;
	readyQueue = nullptr;
	delete blockedQueue;
	blockedQueue = nullptr;
	delete finishedProcesses;
	finishedProcesses = nullptr;
	delete currentProcess;
	currentProcess = nullptr;
	delete ioTimer;
	ioTimer = nullptr;
}

void Priority::selectNextProcess() {
	if (priorityQueue->getRoot() == nullptr) {
		delete currentProcess;
		currentProcess = nullptr;
		return;
	}

	Process process = priorityQueue->getMax()->getData();
	priorityQueue->remove(process);
	currentProcess = new Process(process);
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