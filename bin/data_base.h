#pragma once
#include<list>
#include <fstream>
#include "supplier.h"
#include "seller.h"


template<typename T>
bool sort_by_balance(T& obj_1, T& obj_2) { return (obj_1.get_balance() > obj_2.get_balance()); }


template<typename T>
class data_base
{
	void load(const std::string&);

	static void table_line();

	static void table_head();

	double table_body();

	void table_end(double);

	
	std::list<T> db_{};

public:
	data_base() {}

	data_base(const std::string&);
	
	data_base(const data_base<T>&);

	~data_base();

	void save(const std::string&);
	
	void table();

	bool is_empty();
	
	void push_back(T&);

	std::list<T> get();

	friend data_base search(data_base&);

	bool filter_by_data(data_base&, ::date&, const std::string&);
	
	bool set_debtor(::date&);
	
	bool search_debtor(data_base&);

	void sort(const std::string&);

	bool filter_by_type(data_base&);

	friend data_base<T>& operator>>(std::istream&, data_base<T>&);
};
