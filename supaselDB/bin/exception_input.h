// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
#pragma once
#include <stdexcept>
#include<string>

/**
 * тип исключения, соотвтествующий нарушению ввода с клавиатуры 
 */
class exception_input final : public std::exception
{
	std::runtime_error msg_;

public:
	explicit exception_input(const char* str);

	explicit exception_input(char* str);

	explicit exception_input(std::string& str);

	~exception_input() override;

	exception_input& operator=(const exception_input& e);

	virtual const char* what() const noexcept override;
};
