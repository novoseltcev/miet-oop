// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator
// ReSharper disable CppParameterMayBeConst

#define _CRT_SECURE_NO_WARNINGS
#include "date.h"
using namespace std;


date::date():
	day_(1),
	month_(1),
	year_(1999) {}

date::date(uint_fast16_t year, uint_fast16_t month, uint_fast16_t day):
	day_(day),
	month_(month),
	year_(year) {}

date::date(int year, int month, int day) :
	day_(static_cast<uint_fast16_t>(day)),
	month_(static_cast<uint_fast16_t>(month)),
	year_(static_cast<uint_fast16_t>(year)) {}

date::date(uint_fast16_t year, std::string& month, uint_fast16_t day):
	day_(day),
	month_(str_month_to_int16(month)),
	year_(year) {}

date::date(int year, std::string& month, int day) :
	day_(static_cast<uint_fast16_t>(day)),
	month_(str_month_to_int16(month)),
	year_(static_cast<uint_fast16_t>(year)) {}

date::date(uint_fast16_t year, char* month, uint_fast16_t day) :
	day_(day),
	month_(ch_month_to_int16(month)),
	year_(year) {}

date::date(int year, char* month, int day) :
	day_(static_cast<uint_fast16_t>(day)),
	month_(ch_month_to_int16(month)),
	year_(static_cast<uint_fast16_t>(year)) {}

date::date(const date& val_data):
	day_(val_data.day_),
	month_(val_data.month_),
	year_(val_data.year_) {}

uint_fast16_t date::get_year() { return year_; }

uint_fast16_t date::get_month() { return month_; }

string* ::date::month_names()
{
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

char* date::month_to_ch()
{
	auto* name = new char[strlen(month_to_str().c_str()) + 1];
	return strcpy(name, month_to_str().c_str());
}

string date::month_to_str(){ return month_names()[month_-1]; }

uint_fast16_t date::get_day() { return day_; }

::date date::get_data()
{
	return *new ::date(year_, month_, day_);
}

uint_fast16_t date::str_month_to_int16(string& month)
{
	for (uint_fast16_t i = 0; i < 12; i++)
	{
		if (month == month_names()[i]) { return i + 1; }
	}
	return 0;
}

uint_fast16_t date::ch_month_to_int16(char* month)
{
	string* names = month_names();
	for (uint_fast16_t i = 0; i < 12; i++)
	{
		if (strcmp(month, names[i].c_str()) == 0) { return i+1; }
	}
	return 0;
}

::date& date::operator=(date& right)
{
	year_ = right.get_year();
	month_ = right.get_month();
	day_ = right.get_day();
	return *this;
}

ostream& operator<<(ostream& lhs, ::date& rhs)
{
	lhs << "  ";
	lhs.width(19);
	lhs << to_string(rhs.get_day()) + " " + rhs.month_to_str() + " " + to_string(rhs.get_year());
	lhs << " |" << endl;
	return lhs;
}

::date& operator>>(istream& lhs , ::date&v_data)
{
	int v_day;
	int v_month;
	int v_year;
	lhs.clear();
	lhs.ignore(cin.rdbuf()->in_avail());
	cout << "Введите дату ( день.месяц.год ): ";
	scanf_s("%d.%d.%d", &v_day, &v_month, &v_year);
	while (v_day < 1 || v_day > 31 || v_month < 1 || v_month > 12 || v_year < 0)
	{
		lhs.clear();
		lhs.ignore(cin.rdbuf()->in_avail());
		system("color 74");
		cout << "{Ошибка. Попытка присвоить дате неккоректные значения.}" << endl;
		system("color 71");
		cout << "\nПовторите ввод: ";
		scanf_s("%d.%d.%d", &v_day, &v_month, &v_year);
	}
	v_data.year_ = v_year;
	v_data.month_ = v_month;
	v_data.day_ = v_day;
	return v_data;
}

bool operator==(::date& lhs, ::date& rhs)
{
	return lhs.get_year() == rhs.get_year()
		&& lhs.get_month() == rhs.get_month()
		&& lhs.get_day() == rhs.get_day();
}

bool operator!=(::date& lhs, ::date& rhs)
{
	return !(lhs == rhs);
}

bool operator<(::date& lhs, ::date& rhs)
{
	return lhs.get_year() < rhs.get_year()
		||
		lhs.get_month() < rhs.get_month() &&
		lhs.get_year() == rhs.get_year()
		||
		lhs.get_day() < rhs.get_day() &&
		lhs.get_month() == rhs.get_month() &&
		lhs.get_year() == rhs.get_year();
}

bool operator<=(::date& lhs, ::date& rhs)
{
	return lhs < rhs || lhs == rhs;
}

bool operator>(::date& lhs, ::date& rhs)
{
	return !(lhs <= rhs);
}

bool operator>=(::date& lhs, ::date& rhs)
{ 
	return lhs > rhs || lhs == rhs;
}


