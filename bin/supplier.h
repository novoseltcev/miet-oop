// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator

#pragma once
#include "common.h"
#include <vector>
#include "seller.h"


class supplier: public common
{protected:
	bool debtor_{false};
	std::string company_{};
	std::string address_{};
	uint_fast16_t type_;

public:

	supplier();

	supplier(std::string&, std::string&, int, double, ::date&);

	supplier(const supplier& obj);

	~supplier() override = default;

	bool get_debtor();

	std::string get_company();
	void set_company(std::string&);

	std::string get_address();
	void set_address(std::string&);

	int get_type();

	static void table_name(std::string&, std::string&); //override;

	supplier& operator!();

	supplier& operator=(supplier&);
	
	friend bool operator==(supplier&, supplier&);

	friend std::ostream& operator<<(std::ostream&, supplier&);

	friend supplier& operator>>(std::istream&, supplier&);
	
};

class supplier_impl final : protected supplier
{
public:
	supplier_impl():
		supplier(){}

	supplier_impl(supplier& obj):
		supplier(obj) {}
	
	friend std::ostream& operator<<(std::ostream&, supplier_impl&);

	friend supplier_impl& operator>>(std::istream&, supplier_impl&);

	supplier& get();
};