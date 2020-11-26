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
	date__(date()) {}

common::common(const double val_balance, const date& val_data):
	balance__(val_balance),
	date__(val_data) {}

common::common(const common& obj):
	balance__(obj.balance__),
	date__(obj.date__) {}

common::~common() noexcept = default;;


int common::get_year() { return date__.get_year(); }

int common::get_day() { return date__.get_day(); }

string common::month_to_string() { return date__.month_to_str(); }

int common::get_month() { return date__.get_month(); }

double common::get_balance() { return balance__; }

date common::get_date() { return date__; }


void common::table_name(string& separator_txt, string& main_txt) {
	separator_txt = "";
	main_txt = "";
}


common& common::operator=(const common& right) {
	balance__ = right.balance__;
	date__ = right.date__;
	return *this;
}

bool operator==(const common& lhs, const common& rhs) {
	return abs(lhs.balance__ - rhs.balance__) < .01
		&& lhs.date__ == rhs.date__;
}

bool operator!=(const common& lhs, const common& rhs) { return !(lhs == rhs); }