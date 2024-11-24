#include <timer.h>
#include <iostream>
#include <chrono>

Timer::Timer(double newIORequisite) : IORequisite(newIORequisite) {}

void Timer::start() {
	IOStartTime = steadyClock::now();
}

bool Timer::checkTime() {
	timePoint now = steadyClock::now();
	double elapsed = chrono::duration<double>(now - IOStartTime).count();
	return IORequisite - elapsed <= 0 ? true : false;
}

timePoint Timer::getStartTime() {
	return IOStartTime; 
}