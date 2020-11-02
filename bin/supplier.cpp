// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator

#include "supplier.h"
using namespace std;


supplier::supplier():
	common(),
	company_(""),
	address_(""),
	type_(1) {}


supplier::supplier(string& val_company, string& val_address, int val_type, double val_balance, ::date& val_data):
	common(val_balance, val_data),
	company_(val_company),
	address_(val_address),
	type_(static_cast<uint_fast16_t>(val_type)) {}


supplier::supplier(const supplier& obj)
	: common(obj),
	company_(obj.company_),
	address_(obj.address_),
	type_(obj.type_) {}


bool supplier::get_debtor() { return debtor_; }

string supplier::get_company() { return company_; }

void supplier::set_company(string& val_company) { company_ = val_company; }

string supplier::get_address() { return address_; }

void supplier::set_address(string& val_address) { address_ = val_address; }

int supplier::get_type() { return type_; }

void supplier::table_name(std::string&separator_txt, std::string&main_txt)
{
	separator_txt = "                         |                         |                  |              |                      |";
	main_txt = "  Название фирмы         |  Юридический адресс     |  Тип поставщика  |  Сальдо      |     Дата поставки    |";
}

supplier& supplier::operator!()
{
	debtor_ = true;
	return *this;
}

supplier& supplier::operator= (supplier& right)
{
	company_ = right.company_;
	address_ = right.address_;
	date__ = right.date__;
	type_ = right.type_;
	balance__ = right.balance__;
	return *this;
}

/*bool operator==(supplier& lhs, ::date& rhs)
{
	return lhs.get_date() == rhs;
}*/

bool operator==(supplier& lhs, supplier& rhs)
{
	return lhs.get_company() == rhs.get_company() && lhs.get_address() == rhs.get_address()
		&& lhs.get_type() == rhs.get_type() && abs(lhs.get_balance()-rhs.get_balance()) < .01 
		&& lhs.get_year() == rhs.get_year() && lhs.month_to_string() == rhs.month_to_string() && lhs.get_day() == rhs.get_day();
}

ostream& operator<<(ostream& lhs, supplier& rhs)
{
	lhs.width(25);
	lhs.setf(ios::left);
	lhs << rhs.get_company();
	lhs << "|";

	lhs.width(25);
	lhs << rhs.get_address();
	lhs << "|";

	lhs.unsetf(ios::left);
	lhs.setf(ios::right);
	lhs.width(16);
	if (rhs.get_type() == 1) lhs << "Cырьё";
	if (rhs.get_type() == 2) lhs << "Оборудование";
	lhs << "  |";

	lhs.setf(ios::fixed);
	lhs.width(12);
	lhs.precision(2);
	lhs << rhs.get_balance();
	lhs.unsetf(ios::right | ios::fixed);
	lhs << "  |";
	
	lhs << rhs.date__;
	return lhs;
}

supplier& operator>>(istream& lhs, supplier& rhs)
{
	string v_company{};
	string v_address{};
	int v_type;
	double v_balance;
	::date v_data{};
	cout << "Введите название фирмы: ";
	input_string(v_company, 24);
	cout << "Введите юрдический адресс: ";
	input_string(v_address, 24);
	cout << "Введите тип фирмы: ";
	input_int_with_border(&v_type, 1, 2);
	cout << "Введите сальдо: ";
	input_double(&v_balance);
	lhs >> v_data;
	rhs.company_ = v_company;
	rhs.address_ = v_address;
	rhs.type_ = static_cast<uint16_t>(v_type);
	rhs.balance__ = v_balance;
	rhs.date__ = v_data;
	return rhs;
}



ostream& operator<<(std::ostream& lhs, supplier_impl& rhs)
{
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

supplier_impl& operator>>(std::istream& lhs, supplier_impl& rhs)
{
	auto* buff = new char[100];
	lhs.getline(buff, 100);
	auto list_buff = supplier::split(buff, ";");
	const auto v_company = list_buff[0];
	const auto v_address = list_buff[1];
	const auto v_type = static_cast<uint_fast8_t>(stoi(list_buff[2]));
	const auto v_balance = stod(list_buff[3]);
	const auto v_day = stoi(list_buff[4]);
	const auto v_month = stoi(list_buff[5]);
	const auto v_year = stoi(list_buff[6]);
	rhs.company_ = v_company;
	rhs.address_ = v_address;
	rhs.type_ = v_type;
	rhs.balance__ = v_balance;
	rhs.date__ = *new ::date(v_year, v_month, v_day);
	return rhs;
}

supplier& supplier_impl::get()
{
	return *new supplier(company_, address_, get_type(), get_balance(), *new ::date(get_date()));
}
