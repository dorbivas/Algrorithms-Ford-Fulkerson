#pragma once
#include <string>
#include <iostream>
using namespace std;

class ProgramException : exception {
    string s_invalidInput;
public:
};

