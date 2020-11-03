// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator

#include "seller.h"
using namespace std;


seller::seller():
	common(),
	person_(*new person()) {}


seller::seller(person& val_person, double val_balance, ::date& val_data) :
	common(val_balance, val_data),
	person_(val_person) {}


seller::seller(const seller& obj):
	common(obj),
	person_(obj.person_) {}


string seller::get_surname() { return person_.get_surname(); }

string seller::get_name() { return person_.get_name(); }

string seller::get_middle_name() { return person_.get_middle_name(); }

person seller::get_person()
{
	return *new person(person_);
}

void seller::table_name(std::string& separator_txt, std::string& main_txt)
{
	separator_txt = "                         |                         |                         |                      |              |";
	main_txt = "  Фамилия                |  Имя                    |  Отчество               |     Дата продажи     | Сальдо       |";
}

seller& seller::operator= (seller& right)
{
	date__ = right.date__;
	balance__ = right.balance__;
	person_ = right.person_;
	return *this;
}

bool operator==(seller& lhs, seller& rhs)
{
	return lhs.person_ == rhs.person_
		&& abs(lhs.get_balance() - rhs.get_balance()) < .01
		&& lhs.date__ == rhs.date__;
}

ostream& operator<<(ostream & lhs, seller & rhs)
{
	lhs << rhs.person_;
	
	lhs << rhs.date__;

	lhs.setf(ios::right | ios::fixed);
	lhs.width(12);
	lhs.precision(2);
	lhs << rhs.get_balance();
	lhs.unsetf(ios::right | ios::fixed);
	lhs << "  |" << endl;
	
	return lhs;
}

seller& operator>>(istream& lhs, seller& rhs)
{
	person v_person{};
	double v_balance;
	::date v_data{};
	lhs >> v_person;
	cout << "Введите сальдо: ";
	input_double(&v_balance);
	lhs >> v_data;
	rhs.person_ = v_person;
	rhs.balance__ = v_balance;
	rhs.date__ = v_data;
	return rhs;
}

ostream& operator<<(ostream& lhs, seller_impl& rhs)
{
	lhs << rhs.get_surname();
	lhs << ";";
	lhs << rhs.get_name();
	lhs << ";";
	lhs << rhs.get_middle_name();
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

seller_impl& operator>>(istream& lhs, seller_impl& rhs)
{
	auto* buff = new char[100];
	lhs.getline(buff, 100);
	auto list_buff = seller::split(buff, ";");
	auto v_surname = list_buff[0];
	auto v_name = list_buff[1];
	auto v_middle_name = list_buff[2];
	const auto v_balance = stod(list_buff[3]);
	const auto v_day = stoi(list_buff[4]);
	const auto v_month = stoi(list_buff[5]);
	const auto v_year = stoi(list_buff[6]);
	rhs.person_ = *new person(v_surname, v_name, v_middle_name);
	rhs.balance__ = v_balance;
	rhs.balance__ = v_balance;
	rhs.date__ = *new ::date(v_year, v_month, v_day);
	return rhs;
}

seller& seller_impl::get()
{
	return *new seller(person_, get_balance(), *new ::date(get_date()));
}

