// ReSharper disable CppClangTidyMiscUnconventionalAssignOperator

#pragma once
#include <string>
#include <vector>
#include "date.h"
#include"check_input.h"


class common
{
protected:
	double balance__{};
	class date date__{};
	
public:
	
	common();

	common(double, ::date&);

	common(const common& obj);

	virtual ~common() = default;
	
	int get_year();

	int get_month();
	
	std::string month_to_string();

	int get_day();
	
	double get_balance();

	::date& get_date();

	static void /*virtual*/ table_name(std::string&, std::string&);
	
	common& operator= (common&);

	friend bool operator==(common&, common&);

	friend bool operator!=(common&, common&);

	template<typename T>
	friend bool operator==(T&, date&);

	template<typename T>
	friend bool operator!=(T&, date&);

	template<typename T>
	friend bool operator< (T&, ::date&);

	template<typename T>
	friend bool operator<=(T&, date&);

	template<typename T>
	friend bool operator>(T&, date&);

	template<typename T>
	friend bool operator>=(T&, date&);

	static std::vector<std::string> split(const std::string&, const std::string&);
	
};