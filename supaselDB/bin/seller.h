// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator
// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
#pragma once
#include "common.h"
#include "person.h"


class seller : public common
{
protected:
	class person person_;

public:

	seller();

	seller(const person&, double, const date&);

	seller(const seller& obj);

	~seller() noexcept override;


	std::string get_surname();

	std::string get_name();

	std::string get_middle_name();

	person get_person();


	static void table_name(std::string&, std::string&);

	seller& operator=(const seller&);

	friend bool operator==(const seller&, const seller&);

	friend std::ostream& operator<<(std::ostream&, const seller&);

	friend seller& operator>>(std::istream&, seller&);

	friend std::ofstream& operator<<(std::ofstream&, const seller&);
	
	friend seller& operator>>(std::ifstream&, seller&);
};