#include"exception_input.h"


exception_input::exception_input(const char* str):
	msg_(str) {}


exception_input::exception_input(char* str):
	msg_(str) {}


exception_input::exception_input(std::string& str):
	msg_(str) {}


exception_input::~exception_input() = default;


const char* exception_input::what() const noexcept { return msg_.what(); }


exception_input& exception_input::operator=(const exception_input& e) {
	msg_ = e.msg_;
	return *this;
}
