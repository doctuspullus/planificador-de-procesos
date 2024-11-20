#include <tests.h>

#ifdef _WIN32
#include <windows.h>
    void color(std::string color, std::string line, bool newLine) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int col = 7;
        if (color == "blue") col = 1;
        else if (color == "green") col = 2;
        else if (color == "cyan") col = 3;
        else if (color == "red") col = 4;
        else if (color == "magenta") col = 5;
        else if (color == "yellow") col = 6;
        SetConsoleTextAttribute(hConsole, col);
        std::cout << line;
        if (newLine) {
            std::cout << std::endl;
        }
        SetConsoleTextAttribute(hConsole, 7);
    }
#else
    void color(std::string color, std::string line, bool newLine) {
        std::string col = "\033[0m";
        if (color == "blue") col = "\033[0;34m";
        else if (color == "green") col = "\033[0;32m";
        else if (color == "cyan") col = "\033[0;36m";
        else if (color == "red") col = "\033[0;31m";
        else if (color == "magenta") col = "\033[0;35m";
        else if (color == "yellow") col = "\033[0;33m";
        std::cout << col << line << "\033[0m";
        if (newLine) {
            std::cout << std::endl;
        }
    }
#endif

Tests::Tests() : testsRun(0), testsPassed(0) {}

void Tests::printTestResult(bool passed, const string& testName) {
    testsRun++;
    if (passed) {
        testsPassed++;
        color("green", "✓ " + testName, true);
    } else {
        color("red", "✗ " + testName, true);
    }
}

void Tests::printTestSummary() {
    cout << "\nTest Summary:\n";
    color("cyan", "Total tests: " + to_string(testsRun), true);
    if (testsPassed == testsRun) {
        color("green", "All tests passed!", true);
    } else {
        color("red", "Failed tests: " + to_string(testsRun - testsPassed), true);
        color("green", "Passed tests: " + to_string(testsPassed), true);
    }
}

void ProcessTests::runAllTests() {
    color("cyan", "\n=== Process Class Tests ===\n", true);

    testConstructor();
    testStateTransitions();
    testInstructions();
    testIOOperations();
    testPriorityComparisons();
    testQuantumManagement();

    printTestSummary();
}

void ProcessTests::testConstructor() {
    color("yellow", "\nConstructor Tests:", true);

    // Constructor predeterminado
    Process p1;
    printTestResult(p1.getName() == "null", "Default name should be 'null'");
    printTestResult(p1.getPriority() == 0, "Default priority should be 0");
    printTestResult(p1.getState() == ProcessState::READY, "Default state should be READY");
    
    // Constructor parametrizado
    Process p2("test", 5);
    printTestResult(p2.getName() == "test", "Custom name should be set");
    printTestResult(p2.getPriority() == 5, "Custom priority should be set");
    printTestResult(p2.getState() == ProcessState::READY, "Initial state should be READY");
}


void ProcessTests::testStateTransitions() {
    color("yellow", "\nState Transition Tests:", true);
    
    Process p("test", 1);
    
    p.setState(ProcessState::RUNNING_ACTIVE);
    printTestResult(p.getState() == ProcessState::RUNNING_ACTIVE, "Should transition to RUNNING_ACTIVE");
    
    p.setState(ProcessState::BLOCKED);
    printTestResult(p.getState() == ProcessState::BLOCKED, "Should transition to BLOCKED");
    
    p.setState(ProcessState::RUNNING_PREEMPTED);
    printTestResult(p.getState() == ProcessState::RUNNING_PREEMPTED, "Should transition to RUNNING_PREEMPTED");
    
    p.setState(ProcessState::FINISHED);
    printTestResult(p.getState() == ProcessState::FINISHED, "Should transition to FINISHED");
}

void ProcessTests::testInstructions() {
    color("yellow", "\nInstruction Tests:", true);
    
    Process p("test", 1);
    printTestResult(!p.executeNextInstruction(), "Empty process should not execute");

    p.addInstruction("i1");
    p.addInstruction("i2");
    
    printTestResult(p.hasMoreInstrucions() == true, "Should have instructions");
    printTestResult(p.executeNextInstruction() == true, "Should execute normal instruction");
    printTestResult(p.hasMoreInstrucions() == true, "Should still have instructions after executing one");
    
    p.resetExecution();
    printTestResult(p.hasMoreInstrucions() == true, "Should have instructions after reset");
}

void ProcessTests::testIOOperations() {
    color("yellow", "\nIO Operation Tests:", true);
    
    // Prueba 1: E/S exitosa con suficiente quantum
    Process p("test", 1);
    p.addInstruction("e/s");
    
    printTestResult(p.isInIO() == false, "Should not be in IO initially");
    
    p.executeNextInstruction();  
    printTestResult(p.isInIO() == true, "Should be in IO after IO instruction");
    printTestResult(p.getState() == ProcessState::BLOCKED, "Should be BLOCKED during IO");
    printTestResult(abs(p.getQuantum() - (5 - 1.5)) < 0.001, "Should consume 1.5 quantum units per IO");
    
    // Prueba 2: E/S fallida por falta de quantum
    Process p2("test2", 1);
    p2.addInstruction("e/s");
    p2.setQuantum(1);
    
    p2.executeNextInstruction();
    printTestResult(p2.isInIO() == false, "Should not enter IO with insufficient quantum");
    printTestResult(p2.getState() == ProcessState::RUNNING_PREEMPTED, "Should be in RUNNING_PREEMPTED state due to insufficent quantum for IO");
    
    // Prueba 3: Finalizacion de E/S
    Process p3("test3", 1);
    p3.addInstruction("e/s");
    p3.addInstruction("e/s");
    
    p3.executeNextInstruction();
    float quantumBeforeFinish = p3.getQuantum();
    p3.executeNextInstruction();
    
    printTestResult(p3.isInIO() == false, "Should not be in IO after finishing");
    printTestResult(p3.getState() == ProcessState::READY, "Should be in READY state after IO completion");
    printTestResult(abs(p3.getQuantum() - (quantumBeforeFinish - 1.5)) < 0.001, "Should consume 1.5 quantum units for IO finish");
    
    // Prueba 4: multiples instrucciones
    Process p4("test4", 1);
    p4.addInstruction("i1");
    p4.addInstruction("e/s");
    p4.addInstruction("e/s");
    p4.addInstruction("i1");

    printTestResult(p4.executeNextInstruction() == true, "Should execute normal instruction before IO");
    printTestResult(p4.executeNextInstruction() == false, "Should return false when starting IO");
    printTestResult(p4.executeNextInstruction() == true, "Should return true when ending IO");
    printTestResult(p4.getState() == ProcessState::READY, "Should return to READY state after ending IO");
    printTestResult(abs(p4.getQuantum() - 1) < 0.001, "Should have expected quantum after full sequence");
    printTestResult(p4.executeNextInstruction() == true, "Should execute last instruction");
    printTestResult(p4.getState() == ProcessState::FINISHED, "Should be in FINISHED state after last instruction");
    printTestResult(p4.executeNextInstruction() == false && p4.getState() == ProcessState::FINISHED, "Should not try to execute another instruction, and should not try to modify state, after last instruction");
}

void ProcessTests::testPriorityComparisons() {
    color("yellow", "\nPriority Comparison Tests:", true);
    
    Process p1("test1", 1);
    Process p2("test2", 2);
    
    printTestResult(p1 < p2, "Lower priority process should be less than higher priority");
    printTestResult(p2 > p1, "Higher priority process should be greater than lower priority");
}

void ProcessTests::testQuantumManagement() {
    color("yellow", "\nQuantum Management Tests:", true);
    
    Process p("test", 1);
    p.addInstruction("i1");
    p.addInstruction("i1");
    p.addInstruction("i1");
    p.setQuantum(2);
    
    bool firstExecution = p.executeNextInstruction();
    printTestResult(firstExecution == true, "Should execute first instruction");
    
    bool secondExecution = p.executeNextInstruction();
    printTestResult(secondExecution == true, "Should execute second instruction");
    
    bool thirdExecution = p.executeNextInstruction();
    printTestResult(thirdExecution == false, "Should not execute with quantum depleted");
    
    printTestResult(p.getState() == ProcessState::RUNNING_PREEMPTED, "Should be in RUNNING_PREEMPTED state when quantum is depleted");

    printTestResult(p.hasMoreInstrucions() == true, "Should have more instructions after not executing all");
}