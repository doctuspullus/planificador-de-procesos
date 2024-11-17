#include <tests.hxx>

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

template <typename T>
bool assertEquals(T expectedValue, T actualValue, std::string testName) {
    if (expectedValue == actualValue) {
        color("green", testName + " OK", true);
        return true;
    }
    color("red", testName + " ERROR: Mismatch", true);
    return false;
}