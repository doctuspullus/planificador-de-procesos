#pragma once

#include <singlyLinkedList.hxx>
#include <binarySearchTree.hxx>
#include <process.h>

class Scheduler {
  protected:
    SinglyLinkedList<Process>* readyQueue;      
    SinglyLinkedList<Process>* blockedQueue;     
    SinglyLinkedList<Process>* finishedProcesses;
    
    Process* currentProcess;            

    virtual Process* selectNextProcess() = 0;
    void preemptCurrentProcess();
    void checkBlockedProcesses();

  public:
    Scheduler();
    ~Scheduler();

    void addProcess(Process* newProcess);
    void removeProcess(Process* process);

    void schedule();
    void executeQuantum();
    void handleProcessStateChange(Process* process, ProcessState newState);

    void moveToReady(Process* process);
    void moveToBlocked(Process* process);
    void moveToFinished(Process* process);

    bool hasUnfinishedProcesses() const;
    void displayStatus() const;
};

class RoundRobin : public Scheduler {
	private:
    SinglyLinkedList<Process>* preemptedQueue;     
		float quantumSlice;
		
	protected:
		Process* selectNextProcess() override;
	
	public:
		RoundRobin();
};

class Priority : public Scheduler {
	private:
		BinarySearchTree<Process>* priorityQueue;

	protected:
		Process* selectNextProcess() override;
	
	public:
		Priority();
		void adjustProcessPriority(Process& process);
};