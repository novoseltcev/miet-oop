// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator

#include "common.h"
using namespace std;


vector<string> common::split(const string& str, const string& delimiter) {
	vector<string> tokens;
	size_t prev = 0, pos;
	do {
		pos = str.find(delimiter, prev);
		if (pos == string::npos) pos = str.length();
		auto token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delimiter.length();
	}
	while (pos < str.length() && prev < str.length());
	return tokens;
}

common::common():
	balance__(0.),
	date__(*new date()) {}

common::common(double val_balance, date& val_data):
	balance__(val_balance),
	date__(val_data) {}

common::common(const common& obj):
	balance__(obj.balance__),
	date__(*new date(obj.date__)) {};


int common::get_year() { return date__.get_year(); }

int common::get_day() { return date__.get_day(); }

string common::month_to_string() { return date__.month_to_str(); }

int common::get_month() { return date__.get_month(); }

double common::get_balance() { return balance__; }

date& common::get_date() { return *new date(date__); }


void common::table_name(string& separator_txt, string& main_txt) {
	separator_txt = "";
	main_txt = "";
}


common& common::operator=(common& right) {
	balance__ = right.get_balance();
	date__ = right.date__;
	return *this;
}

bool operator==(common& lhs, common& rhs) {
	return abs(lhs.get_balance() - rhs.get_balance()) < .01
		&& lhs.date__ == rhs.date__;
}

bool operator!=(common& lhs, common& rhs) { return !(lhs == rhs); }
