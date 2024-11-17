#pragma once
#include <iostream>

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

template <typename T>
bool assertEquals(T expectedValue, T actualValue, std::string testName);

#include <tests.tpp>