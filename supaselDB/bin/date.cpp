// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator
// ReSharper disable CppParameterMayBeConst

#define _CRT_SECURE_NO_WARNINGS
#include "date.h"
#include "exception_input.h"
using namespace std;


date::date():
	day_(1),
	month_(1),
	year_(1999) {}

date::date(const uint_fast16_t year, const uint_fast16_t month, const uint_fast16_t day):
	day_(day),
	month_(month),
	year_(year) {}

date::date(const int year, const int month, const int day) :
	day_(static_cast<uint_fast16_t>(day)),
	month_(static_cast<uint_fast16_t>(month)),
	year_(static_cast<uint_fast16_t>(year)) {}

date::date(const uint_fast16_t year, const string& month, const uint_fast16_t day):
	day_(day),
	month_(str_month_to_int16(month)),
	year_(year) {}

date::date(int year, const string& month, int day):
	day_(static_cast<uint_fast16_t>(day)),
	month_(str_month_to_int16(month)),
	year_(static_cast<uint_fast16_t>(year)) {}

date::date(uint_fast16_t year, const char* month, uint_fast16_t day):
	day_(day),
	month_(ch_month_to_int16(month)),
	year_(year) {}

date::date(int year, const char* month, int day) :
	day_(static_cast<uint_fast16_t>(day)),
	month_(ch_month_to_int16(month)),
	year_(static_cast<uint_fast16_t>(year)) {}

date::date(const date& val_data):
	day_(val_data.day_),
	month_(val_data.month_),
	year_(val_data.year_) {}


uint_fast16_t date::get_year() { return year_; }

uint_fast16_t date::get_month() { return month_; }

string* date::month_names() {
	return new string[12]
	{
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};
}

char* date::month_to_ch() {
	auto* name = new char[strlen(month_to_str().c_str()) + 1];
	return strcpy(name, month_to_str().c_str());
}

string date::month_to_str() { return month_names()[month_ - 1]; }

uint_fast16_t date::get_day() { return day_; }

date date::get_date() { return date(year_, month_, day_); }


uint_fast16_t date::str_month_to_int16(const string& month) {
	for (uint_fast16_t i = 0; i < 12; i++) { if (month == month_names()[i]) { return i + 1; } }
	return 0;
}

uint_fast16_t date::ch_month_to_int16(const char* month) {
	auto* names = month_names();
	for (uint_fast16_t i = 0; i < 12; i++) {
		if (strcmp(month, names[i].c_str()) == 0) { return i + 1; }
	}
	free(names);
	return 0;
}


date& date::operator=(const date& right) {
	year_ = right.year_;
	month_ = right.month_;
	day_ = right.day_;
	return *this;
}

ostream& operator<<(ostream& lhs, const date& rhs) {
	lhs << "  ";
	lhs.width(19);
	lhs << to_string(rhs.day_) + " " + to_string(rhs.month_) + " " + to_string(rhs.year_);
	lhs << " |";
	return lhs;
}

date& operator>>(istream& lhs, date& v_date) {
	int v_day, v_month, v_year;
	cout << "Enter the date ( day.month.year ): ";
	while (true) {
		try {
			is_date(lhs, &v_year, &v_month, &v_day);
			v_date = date(v_year, v_month, v_day);
			return v_date;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Input error: " << e.what() << endl;
			system("color 71");
			cout << "Try again: ";
		}
	}
}

bool operator==(const date& lhs, const date& rhs) {
	return lhs.year_ == rhs.year_
		&& lhs.month_ == rhs.month_
		&& lhs.day_ == rhs.day_;
}

bool operator!=(const date& lhs, const date& rhs) { return !(lhs == rhs); }

bool operator<(const date& lhs, const date& rhs) {
	return lhs.year_ < rhs.year_
		||
		lhs.month_ < rhs.month_ &&
		lhs.year_ == rhs.year_
		||
		lhs.day_ < rhs.day_ &&
		lhs.month_ == rhs.month_ &&
		lhs.year_ == rhs.year_;
}

bool operator<=(const date& lhs, const date& rhs) { return lhs < rhs || lhs == rhs; }

bool operator>(const date& lhs, const date& rhs) { return !(lhs <= rhs); }

bool operator>=(const date& lhs, const date& rhs) { return lhs > rhs || lhs == rhs; }
