#pragma once

#include <iostream>

class UI {
	public: 
	  //run:
	  void run();
	  
	  //input: nombrefile
	  void askForFileName();
	  //input:roundrobin or priority
	  void askForScheduler();
	  //output: GUI
	  void presentState();
	
}