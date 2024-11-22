#include <tests.h>
#include <scheduler.h>

int main() {
  //ProcessTests tests;
  //tests.runAllTests();
	RoundRobin scheduler;
	
	Process* process1 = new Process("P1", 1);
	process1->addInstruction("compute");
	process1->addInstruction("e/s");
	scheduler.addProcess(process1);

	Process* process2 = new Process("P2", 2);
	process2->addInstruction("compute");
	process2->addInstruction("compute");
	scheduler.addProcess(process2);

	scheduler.run();
  return 0;
}