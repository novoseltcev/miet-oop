// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator

#include "person.h"
#include "exception_input.h"
using namespace std;

person::person():
	surname_("Новосельцев"),
	name_("Станислав"),
	middle_name_("Андреевич") {}

person::person(string& val_surname, string& val_name, string& val_middle_name):
	surname_(val_surname),
	name_(val_name),
	middle_name_(val_middle_name) {}

person::person(const person& obj):
	surname_(obj.surname_),
	name_(obj.name_),
	middle_name_(obj.middle_name_) {}

person::~person() noexcept = default;

string person::get_surname() { return surname_; }

string person::get_name() { return name_; }

string person::get_middle_name() { return middle_name_; }

person& person::operator=(const person& right) {
	surname_ = right.surname_;
	name_ = right.name_;
	middle_name_ = right.middle_name_;
	return *this;
}

ostream& operator<<(ostream& lhs, const person& rhs) {
	lhs << " ";
	lhs.width(24);
	lhs.setf(ios::left);
	lhs << rhs.surname_;
	lhs << "| ";

	lhs.width(24);
	lhs.setf(ios::left);
	lhs << rhs.name_;
	lhs << "| ";

	lhs.width(24);
	lhs.setf(ios::left);
	lhs << rhs.middle_name_;
	lhs << "|";
	return lhs;
}

person& operator>>(istream& lhs, person& rhs) {
	string v_surname, v_name, v_middle_name;
	cout << "Enter the Surname: ";
	while (true) {
		try {
			is_name(lhs, v_surname, 24);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Ошибка ввода: " << e.what() << endl;
			system("color 71");
			cout << "Повторите ввод: ";
		}
	}

	cout << "Enter the Name: ";
	while (true) {
		try {
			is_name(lhs, v_name, 24);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Ошибка ввода: " << e.what() << endl;
			system("color 71");
			cout << "Повторите ввод: ";
		}
	}

	cout << "Enter the Patronomyc: ";
	while (true) {
		try {
			is_name(lhs, v_middle_name, 24);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Ошибка ввода: " << e.what() << endl;
			system("color 71");
			cout << "Повторите ввод: ";
		}
	}

	rhs.surname_ = v_surname;
	rhs.name_ = v_name;
	rhs.middle_name_ = v_middle_name;

	return rhs;
}

bool operator==(const person& lhs, const person& rhs) {
	return lhs.surname_ == rhs.surname_
		&& lhs.name_ == rhs.name_
		&& lhs.middle_name_ == rhs.middle_name_;
}

bool operator!=(const person& lhs, const person& rhs) { return !(lhs == rhs); }
