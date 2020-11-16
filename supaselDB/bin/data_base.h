// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
#pragma once
#include<list>
#include "seller.h"


template <typename T>
bool sort_by_balance(T& obj_1, T& obj_2) { return (obj_1.get_balance() > obj_2.get_balance()); }


template <typename T>
class data_base
{
	std::list<T> db_{};

public:
	data_base();

	explicit data_base(const std::string&);

	data_base(const data_base<T>&);

	~data_base() noexcept;


	std::list<T> get();

	void save(const std::string&);

	void load(const std::string&);

private:
	void load(const std::string&, std::ifstream&);

	static void table_line();

	static void table_head();

	double table_body();

	void table_end(double);

public:
	void table();

	int size();
	
	bool is_empty();

	void push_front(T&);

	void insert(int, T&);

	void push_back(T&);

	void pop_front();

	friend data_base search(data_base&);

	bool filter_by_type(data_base&);

	bool filter_by_data(data_base&, date&, bool f(T&, date&));

	void sort(bool comparator(T&, T&));


	bool set_debtor(date&);

	bool search_debtor(data_base&);


	friend data_base<T>& operator>>(std::istream&, data_base<T>&);
};
