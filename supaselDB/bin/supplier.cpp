// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator

#include "supplier.h"
#include<fstream>
#include <vector>
#include "exception_input.h"
using namespace std;


supplier::supplier():
	common(),
	company_(""),
	address_(""),
	type_(1) {}


supplier::supplier(string& val_company, string& val_address, const int val_type, const double val_balance, const date& val_data):
	common(val_balance, val_data),
	company_(val_company),
	address_(val_address),
	type_(static_cast<uint_fast16_t>(val_type)) {}


supplier::supplier(const supplier& obj)
	: common(obj),
	  company_(obj.company_),
	  address_(obj.address_),
	  type_(obj.type_) {}

supplier::~supplier() noexcept = default;


bool supplier::get_debtor() { return debtor_; }

string supplier::get_company() { return company_; }

void supplier::set_company(const string& val_company) { company_ = val_company; }

string supplier::get_address() { return address_; }

void supplier::set_address(const string& val_address) { address_ = val_address; }

int supplier::get_type() { return type_; }


void supplier::table_name(std::string& separator_txt, std::string& main_txt) {
	separator_txt =
		"                         |                         |                  |                      |              |";
	main_txt =
		"  Название фирмы         |  Юридический адресс     |  Тип поставщика  |     Дата поставки    |  Сальдо      |";
}


supplier& supplier::operator!() {
	debtor_ = true;
	return *this;
}

supplier& supplier::operator=(const supplier& right) {
	company_ = right.company_;
	address_ = right.address_;
	date__ = right.date__;
	type_ = right.type_;
	balance__ = right.balance__;
	return *this;
}

bool operator==(const supplier& lhs, const supplier& rhs) {
	return lhs.company_ == rhs.company_ && lhs.address_ == rhs.address_
		&& lhs.type_ == rhs.type_ && abs(lhs.balance__ - rhs.balance__) < .01
		&& lhs.date__ == rhs.date__;
}

ostream& operator<<(ostream& lhs, const supplier& rhs) {
	lhs << " ";
	lhs.width(24);
	lhs.setf(ios::left);
	lhs << rhs.company_
	    << "| ";

	lhs.width(24);
	lhs << rhs.address_
	    << "| ";

	lhs.unsetf(ios::left);
	lhs.setf(ios::right);
	lhs.width(16);
	if (rhs.type_ == 1) lhs << "Cырьё";
	if (rhs.type_ == 2) lhs << "Оборудование";
	lhs << " |";

	lhs << rhs.date__;

	lhs.setf(ios::right | ios::fixed);
	lhs.width(12);
	lhs.precision(2);
	lhs << rhs.balance__;
	lhs.unsetf(ios::right | ios::fixed);
	lhs << "  |" << endl;

	return lhs;
}

supplier& operator>>(istream& lhs, supplier& rhs) {
	string v_company{};
	string v_address{};
	int v_type;
	double v_balance;
	date v_data{};

	cout << "Enter the company name: ";
	while (true) {
		try {
			is_correct_string(lhs, v_company, 24);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Ошибка ввода: " << e.what() << endl;
			system("color 71");
			cout << "Повторите ввод: ";
		}
	}
	cout << "Enter legal address: ";
	while (true) {
		try {
			is_correct_string(lhs, v_address, 24);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Ошибка ввода: " << e.what() << endl;
			system("color 71");
			cout << "Повторите ввод: ";
		}
	}
	cout << "Enter the company type: ";
	while (true) {
		try {
			is_int(lhs, &v_type, 1, 2);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Input error: " << e.what() << endl;
			system("color 71");
			cout << "Try again: ";
		}
	}
	cout << "Enter the balance: ";
	while (true) {
		try {
			is_double(lhs, &v_balance);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Ошибка ввода: " << e.what() << endl;
			system("color 71");
			cout << "Повторите ввод: ";
		}
	}
	lhs >> v_data;

	rhs.company_ = v_company;
	rhs.address_ = v_address;
	rhs.type_ = static_cast<uint16_t>(v_type);
	rhs.balance__ = v_balance;
	rhs.date__ = v_data;

	return rhs;
}


ofstream& operator<<(ofstream& lhs, const supplier& rhs) {
	auto t_date = rhs.date__;
	lhs << rhs.company_
		<< ";"
		<< rhs.address_
		<< ";"
		<< rhs.type_
		<< ";"
		<< rhs.balance__
		<< ";"
	    << t_date.get_day()
	    << ";"
	    << t_date.get_month()
	    << ";"
	    << t_date.get_year()
	    << ";\n";
	return lhs;
}

supplier& operator>>(ifstream& lhs, supplier& rhs) {
	auto* buff = new char[80];
	lhs.getline(buff, 80);
	auto list_buff = supplier::split(buff, ";");
	rhs.company_ = list_buff[0];
	rhs.address_ = list_buff[1];
	rhs.type_ = static_cast<uint_fast8_t>(stoi(list_buff[2]));
	rhs.balance__ = stod(list_buff[3]);
	rhs.date__ = date(stoi(list_buff[4]), stoi(list_buff[5]), stoi(list_buff[6]));
	delete[] buff;
	return rhs;
}


ostream& operator<<(std::ostream& lhs, supplier_impl& rhs) {
	lhs << rhs.get_company();
	lhs << ";";
	lhs << rhs.get_address();
	lhs << ";";
	lhs << rhs.get_type();
	lhs << ";";
	lhs << rhs.get_balance();
	lhs << ";";
	lhs << rhs.get_day();
	lhs << ";";
	lhs << rhs.get_month();
	lhs << ";";
	lhs << rhs.get_year();
	lhs << ";\n";
	return lhs;
}

supplier_impl::supplier_impl(): supplier() {}

supplier_impl::supplier_impl(const supplier& obj): supplier(obj) {}

supplier supplier_impl::get() { return supplier(company_, address_, get_type(), get_balance(), get_date()); }
