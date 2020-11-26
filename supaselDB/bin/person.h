// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator
// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
#pragma once
#include <string>
#include"check_input.h"


class person
{
	std::string surname_;
	std::string name_;
	std::string middle_name_;

public:
	person();

	person(std::string&, std::string&, std::string&);

	person(const person&);

	~person() noexcept;


	std::string get_surname();

	std::string get_name();

	std::string get_middle_name();


	person& operator=(const person&);

	friend std::ostream& operator<<(std::ostream&, const person&);

	friend person& operator>>(std::istream&, person&);

	friend bool operator==(const person&, const person&);

	friend bool operator!=(const person&, const person&);
};
