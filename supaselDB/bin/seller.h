// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator
// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
#pragma once
#include "common.h"
#include "person.h"


class seller : public common
{
protected:
	class person person_{};

public:

	seller();

	seller(person&, double, date&);

	seller(const seller& obj);

	~seller() noexcept override;


	std::string get_surname();

	std::string get_name();

	std::string get_middle_name();

	person get_person();


	static void table_name(std::string&, std::string&);

	seller& operator=(seller&);

	friend bool operator==(seller&, seller&);

	friend std::ostream& operator<<(std::ostream&, seller&);

	friend seller& operator>>(std::istream&, seller&);
};

class seller_impl final : public seller
{
public:
	seller_impl();

	explicit seller_impl(seller& obj);


	seller& get();


	friend std::ostream& operator<<(std::ostream&, seller_impl&);

	friend seller_impl& operator>>(std::istream&, seller_impl&);
};
