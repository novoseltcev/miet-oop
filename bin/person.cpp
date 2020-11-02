// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator

#include "person.h"
using namespace std;

person::person():
	surname_("Новосельцев"),
	name_("Станислав"),
	middle_name_("Андреевич"){}

person::person(string& val_surname, string& val_name, string& val_middle_name):
	surname_(val_surname),
	name_(val_name),
	middle_name_(val_middle_name){}

person::person(const person& obj):
	surname_(obj.surname_),
	name_(obj.name_),
	middle_name_(obj.middle_name_) {}

string person::get_surname() { return surname_; }

string person::get_name() { return name_; }

string person::get_middle_name() { return middle_name_; }

person& person::operator=(person& right)
{
	surname_ = right.get_surname();
	name_ = right.get_name();
	middle_name_ = right.get_middle_name();
	return *this;
}

ostream& operator<<(ostream& lhs, person& rhs)
{
	lhs << "  ";
	lhs.width(72);
	lhs << rhs.get_surname() + " " + rhs.get_name() + " " + rhs.get_middle_name();
	lhs << " |" << endl;
	return lhs;
}

person& operator>>(istream& lhs, person& rhs)
{
	string v_surname, v_name, v_middle_name;
	cout << "Введите Фамилию: ";
	input_string(v_surname, 24);
	cout << "Введите Имя: ";
	input_string(v_name, 24);
	cout << "Введите Отчество: ";
	input_string(v_middle_name, 24);
	rhs.surname_ = v_surname;
	rhs.name_ = v_name;
	rhs.middle_name_ = v_middle_name;
	return rhs;
}

bool operator==(person& lhs, person& rhs)
{
	return lhs.get_surname() == rhs.get_surname()
		&& lhs.get_name() == rhs.get_name()
		&& lhs.get_middle_name() == rhs.get_middle_name();
}

bool operator!=(person& lhs, person& rhs)
{
	return !(lhs == rhs);
}