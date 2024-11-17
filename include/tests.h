#pragma once
#include <iostream>
#include <process.h>

// Color Terminal Output Library
// MIT Licensed Library

// There are 6 colors:
//
// blue
// green
// cyan
// red
// magenta
// yellow

// Usage:
// color("red", "Error occured", true);
//       color  text           newLine

void color(std::string color, std::string line, bool newLine = false);

class ProcessTests {
  private:
    int testsRun;
    int testsPassed;

    void printTestResult(bool passed, const std::string& testName);
    void printTestSummary();
    
  public:
    ProcessTests();
    
    void runAllTests();
    void testConstructor();
    void testStateTransitions();
    void testInstructions();
    void testIOOperations();
    void testPriorityComparisons();
    void testQuantumManagement();
};