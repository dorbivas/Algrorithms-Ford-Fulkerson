#pragma once
#include <string>
#include <iostream>
using namespace std;

class ProgramException : exception {
    string s_invalidInput;
public:
    bool isConnected = true;
    ProgramException() : s_invalidInput("invalid input"), exception("invalid input") { ; }
    const char* what() const override { return s_invalidInput.c_str(); }
};

