#pragma once

#include <iostream>
#include <scheduler.h>

class UI {
	private:
		string filename;
		Scheduler* scheduler;

	public: 
		UI();
		~UI();

		string getFilename();
		Scheduler* getScheduler();
	  //run:
	  void run();
	  
	  //input: nombrefile
	  void askForFileName();
	  //input:roundrobin or priority
	  void askForScheduler();
	  //output: GUI
	  static void presentState(Process* currentProcess);
		static void clearCLI();
};