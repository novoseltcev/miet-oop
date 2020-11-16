#pragma once
#include<string>
using namespace std;

class exception_input : public exception {
	string error_message;

public:
	exception_input(const char* str):
		exception(str) {}

	exception_input(char* str):
		exception(str) {}

	exception_input(string& str):
		exception(str.c_str()) {}

	exception_input(exception& e):
		exception(e) {}

	~exception_input() = default;
};