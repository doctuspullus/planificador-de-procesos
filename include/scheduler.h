#pragma once

#include <singlyLinkedList.hxx>
#include <binarySearchTree.hxx>
#include <process.h>
#include <timer.h>

class Scheduler {
  protected:
    SinglyLinkedList<Process>* readyQueue;      
    SinglyLinkedList<Process>* blockedQueue;     
    SinglyLinkedList<Process>* finishedProcesses;
    
    Process* currentProcess;            
		Timer* ioTimer;

    virtual void selectNextProcess() = 0;
    void preemptCurrentProcess();
    void checkBlockedProcesses();

  public:
    Scheduler();
    virtual ~Scheduler();
		
		void run();

    virtual void addProcess(Process* newProcess);
    void removeProcess(Process* process);

    void schedule();
    void executeQuantum();
    void handleProcessStateChange(Process* process, ProcessState newState);

    void moveToReady(Process* process);
    void moveToBlocked(Process* process);
    void moveToFinished(Process* process);

    bool hasUnfinishedProcesses() const;
		void clearTimer();
    void displayStatus() const;
};

class RoundRobin : public Scheduler {
	private:
    SinglyLinkedList<Process>* preemptedQueue;     
		float quantumSlice;
		
	protected:
		void selectNextProcess() override;
	
	public:
		RoundRobin();
		~RoundRobin() override;
};

class Priority : public Scheduler {
	private:
		BinarySearchTree<Process>* priorityQueue;

	protected:
		void selectNextProcess() override;
	
	public:
		Priority();
		~Priority() override;
		
		void calculateInitialPriority(Process& process);
		void moveToBlocked(Process* process);
		void addProcess(Process* newProcess) override;
		void adjustProcessPriority(Process& process, int newPriority);
};