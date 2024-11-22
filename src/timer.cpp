#include <timer.h>

Timer::Timer(double newIORequisite) : IORequisite(newIORequisite) {}

void Timer::start() {
	IOStartTime = clock::now();
}

bool Timer::checkTime() {
	timePoint now = clock::now();
	double elapsed = chrono::duration<double>(now - IOStartTime).count();
	return IORequisite - elapsed <= 0 ? true : false;
}