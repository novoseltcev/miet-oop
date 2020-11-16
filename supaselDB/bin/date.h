// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator
// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
#pragma once
#include <string>
#include"check_input.h"


class date
{
	uint_fast16_t day_{};
	uint_fast16_t month_{};
	uint_fast16_t year_{};


	static auto str_month_to_int16(std::string&) -> uint_fast16_t;

	static uint_fast16_t ch_month_to_int16(char* month);

	static inline std::string* month_names();

public:
	date();

	date(uint_fast16_t, uint_fast16_t, uint_fast16_t);

	date(int, int, int);

	date(uint_fast16_t, std::string&, uint_fast16_t);

	date(int, std::string&, int);

	date(uint_fast16_t year, char* month, uint_fast16_t day);

	date(int year, char* month, int day);

	date(const date&);

	~date() noexcept = default;

	uint_fast16_t get_year();

	uint_fast16_t get_month();

	char* month_to_ch();
	std::string month_to_str();

	uint_fast16_t get_day();

	date get_data();


	date& operator=(date&);

	friend std::ostream& operator<<(std::ostream&, date&);

	friend date& operator>>(std::istream&, date&);

	friend bool operator==(date&, date&);

	friend bool operator<(date&, date&);

	friend bool operator<=(date&, date&);

	friend bool operator>(date&, date&);

	friend bool operator>=(date&, date&);

	friend bool operator!=(date&, date&);
};
