// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator

#include "seller.h"
#include<fstream>
#include "exception_input.h"
using namespace std;


seller::seller():
	common() {}


seller::seller(const person& val_person, const double val_balance, const date& val_data) :
	common(val_balance, val_data),
	person_(val_person) {}


seller::seller(const seller& obj):
	common(obj),
	person_(obj.person_) {}


seller::~seller() noexcept = default;


string seller::get_surname() { return person_.get_surname(); }

string seller::get_name() { return person_.get_name(); }

string seller::get_middle_name() { return person_.get_middle_name(); }

person seller::get_person() { return person(person_); }


void seller::table_name(string& separator_txt, string& main_txt) {
	separator_txt =
		"                         |                         |                         |                      |              |";
	main_txt =
		"  Фамилия                |  Имя                    |  Отчество               |     Дата продажи     | Сальдо       |";
}


seller& seller::operator=(const seller& right) {
	date__ = right.date__;
	balance__ = right.balance__;
	person_ = right.person_;
	return *this;
}

bool operator==(const seller& lhs, const seller& rhs) {
	return lhs.person_ == rhs.person_
		&& abs(lhs.balance__ - rhs.balance__) < .01
		&& lhs.date__ == rhs.date__;
}

ostream& operator<<(ostream& lhs, const seller& rhs) {
	lhs << rhs.person_;

	lhs << rhs.date__;

	lhs.setf(ios::right | ios::fixed);
	lhs.width(12);
	lhs.precision(2);
	lhs << rhs.balance__;
	lhs.unsetf(ios::right | ios::fixed);
	lhs << "  |" << endl;

	return lhs;
}

seller& operator>>(istream& lhs, seller& rhs) {
	person v_person{};
	double v_balance;
	date v_data{};

	lhs >> v_person;
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

	rhs.person_ = v_person;
	rhs.balance__ = v_balance;
	rhs.date__ = v_data;
	return rhs;
}

ofstream& operator<<(ofstream& lhs, const seller& rhs) {
	auto t_person = rhs.person_;
	auto t_date = rhs.date__;
	lhs << t_person.get_surname()
		<< ";"
		<< t_person.get_name()
	    << ";"
	    << t_person.get_middle_name()
	    << ";"
	    << t_date.get_day()
	    << ";"
	    << t_date.get_month()
	    << ";"
	    << t_date.get_year()
	    << ";"
	    << rhs.balance__
	    << ";\n";
	return lhs;
}

seller& operator>>(ifstream& lhs, seller& rhs) {
	auto* buff = new char[80];
	lhs.getline(buff, 80);
	auto list_buff = seller::split(buff, ";");

	person t_person(list_buff[0], list_buff[1], list_buff[2]);
	rhs.person_ = person(list_buff[0], list_buff[1], list_buff[2]);
	rhs.date__ = date(stoi(list_buff[5]), stoi(list_buff[4]), stoi(list_buff[3]));
	rhs.balance__ = stod(list_buff[6]);
	delete[] buff;
	return rhs;
}
