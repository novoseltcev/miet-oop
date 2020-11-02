#include "data_base.h"
#include <list>
using namespace std;

//Локализация для продавца
/*template <typename T>
data_base<T> search(data_base<T>& val_data_base)
{
	data_base<T> copied_data_base;
	val_data_base.get();
	string val_company;
	cout << "Введите фирму поставщика: ";
	input_string(val_company, 24);
	for (auto i : val_data_base.get())
	{
		if (i.get_company() == val_company) { copied_data_base.push_back(i); }
	}
	return copied_data_base;
}*/

//функционльное програмирование
template <typename T>
void data_base<T>::load(const string& filename)
{
	ifstream fp(filename);
	if (!fp.is_open())
	{
		system("color 74");
		cout << "{Ошибка открытия файла " << filename << " }"
			<< endl << endl;
		system("color 71");
	}
	else
	{
		auto* buff2 = new char[100];
		fp.getline(buff2, 100);

		const auto val_count = stoi(buff2);
		if (val_count == 0) { fp.close(); }
		else
		{
			const auto is_supplier = typeid(T) == typeid(supplier);
			const auto is_seller = typeid(T) == typeid(seller);
			if (is_supplier)
			{
				supplier_impl n_obj;
				for (auto i = 1; i <= val_count; i++)
				{
					fp >> n_obj;
					T t_obj = n_obj.get();
					push_back(t_obj);
				}
			}
			else
			{
				if (is_seller)
				{
					//seller_impl n_obj;
					for (auto i = 1; i <= val_count; i++)
					{
						//fp >> n_obj;
						//T t_obj = n_obj.get();
						//push_back(t_obj);
					}
				}
				else
				{
					auto out_str = new string[3]
					{
						"список эл-ов типа ",
						typeid(T).name(),
						" не поддерживается классом"
					};
					throw new exception((out_str[0] + out_str[1] + out_str[2]).c_str());
				}
			}
			fp.close();
		}
	}
}

template <typename T>
void data_base<T>::table_line()
{
	cout <<
		"-------------------------|-------------------------|------------------|--------------|----------------------|"
		<< endl;
}

template <typename T>
void data_base<T>::table_head()
{
	string separator_txt, main_txt;
	T::table_name(separator_txt, main_txt);

	cout << separator_txt
		<< endl;
	cout << main_txt
		<< endl;
	cout << separator_txt
		<< endl;
	table_line();
}

template <typename T>
double data_base<T>::table_body()
{
	double sum = 0;
	for (T& obj : db_)
	{
		cout << obj;
		sum += obj.get_balance();
		table_line();
	}
	return sum;
}

//изменение ширины для продавцов
template <typename T>
void data_base<T>::table_end(double sum)
{
	const string table_end_text = (typeid(T) == typeid(supplier)) ? "Общая задолженность:" : "Общее сальдо продаж";
	cout << table_end_text;
	cout.setf(ios::right | ios::fixed);
	cout.precision(2);
	cout.width(83);
	cout << sum << "  " << endl;
	cout.unsetf(ios::right | ios::fixed);
	cout << "Кол-во товаров в базе: ";
	cout.width(83);
	cout.setf(ios::left);
	cout << db_.size();
	cout << "  " << endl;
	cout.unsetf(ios::left);
}

//переделать стартовый алгоритм
template <typename T>
data_base<T>::data_base(const string& filename)
{
	/*if (typeid(T).name() != typeid(supplier).name() 
		&& typeid(T).name() != typeid(seller).name())
	{
		throw new domain_error("функция не адаптирована для списка данного значения");
	};
	db_ = new list<T>();*/
	ifstream fp(filename, ios_base::out);
	auto start_count = -1;
	if (!fp.is_open())
	{
		cout << "Введите кол-во записей: ";
		input_int_with_border(&start_count, 1, 10);
		cout << endl;
		for (auto i = 1; i <= start_count; i++)
		{
			system("cls");
			cout << "Введите кол-во записей: " << start_count << endl;
			cout << i << " из " << start_count << endl;
			//cin >> *this;
		}
	}
	else
	{
		load(filename);
		fp.close();
	}
}

template<typename T>
data_base<T>::data_base(const data_base<T>& obj):
	db_(obj.db_) {}

template <typename T>
data_base<T>::~data_base() { db_.clear(); }

//функционльное програмирование
template <typename T>
void data_base<T>::save(const string& filename)
{
	ofstream fp(filename, ios_base::in | ios_base::trunc);
	if (!fp.is_open())
	{
		system("color 74");
		cout << "{Ошибка открытия файла " << filename << " }"
			<< endl << endl;
		system("color 71");
	} 
	else
	{
		const auto is_supplier = typeid(T) == typeid(supplier);
		const auto is_seller = typeid(T) == typeid(seller);
		fp << db_.size() << "\n";
		if (is_supplier)
		{
			//supplier_impl n_obj;
			for (auto obj : db_)
			{
				supplier_impl t_obj(obj);
				fp << t_obj;
			}
		}
		else
		{
			if (is_seller)
			{
				//seller_impl n_obj();
				/*for (auto obj : db_)
				{
					fp << n_obj;
				}*/
			}
			else
			{
				auto out_str = new string[3]
				{
					"список эл-ов типа ",
					typeid(T).name(),
					" не поддерживается классом"
				};
				throw new exception((out_str[0] + out_str[1] + out_str[2]).c_str());
			}
		}
		
	}
}

template <typename T>
void data_base<T>::table()
{
	if (is_empty())
	{
		cout.width(63);
		const string var = (typeid(T).name() == typeid(supplier).name())
			? "поставщиках."
			: "продавцах.";
		cout << "В Базе отсутствует информация о "
			<< var << endl;
	}
	else
	{
		table_head();
		table_end(table_body());
	}
}

template <typename T>
bool data_base<T>::is_empty() { return db_.empty(); }

template <typename T>
void data_base<T>::push_back(T& obj) { db_.push_back(obj); }

template <typename T>
list<T> data_base<T>::get() { return db_; }

bool data_base<supplier>::filter_by_type(data_base<supplier>& val_data_base)
{
	auto val_type = -1;
	cout << "Примечание: 1 - поставщик сырья, 2 - поставщик оборудования" << endl;
	cout << "Введите тип поставщика: ";
	input_int_with_border(&val_type, 1, 2);
	for (auto& i : val_data_base.db_)
	{
		if (i.get_type() == val_type) push_back(i);
	}
	return (is_empty()) ? true : false;
}

template <typename T>
bool data_base<T>::filter_by_data(data_base<T>& val_data_base, class date& val_data, const string& flag)
{
	/*if (flag == ">")
	{
		for (T& i : val_data_base.db_)
		{
			if (i > val_data) { push_back(i); }
		}
	}
	if (flag == ">=")
	{
		for (T& i : val_data_base.db_)
		{
			if (i >= val_data) { push_back(i); }
		}
	}
	if (flag == "==")
	{
		for (T& i : val_data_base.db_)
		{
			if (i == val_data) { push_back(i); }
		}
	}*/
	/*if (flag == "<")
	{
		for (T& i : val_data_base.get())
		{
			if (i < val_data) { push_back(i); }
		}
	}*/
	/*if (flag == "<=")
	{
		for (T& i : val_data_base.db_)
		{
			if (i <= val_data) { push_back(i); }
		}
	}*/
	return (is_empty()) ? true : false;
}

template<typename T>
bool data_base<T>::set_debtor(class date& val_data)
{
	if (typeid(T).name() == typeid(supplier).name())
	{
		for (auto& obj : db_)
		{
			if (obj.get_date() < val_data) { !obj; }
		}
		return (is_empty()) ? true : false;
	}
	else throw new domain_error("НЕ ПОДДЕРЖИВАЕТСЯ!!!");
}

bool data_base<supplier>::search_debtor(data_base<supplier>& val_data_base)
{
	for (auto& obj : val_data_base.db_)
	{
		if (obj.get_debtor()) { push_back(obj); }
	}
	return (is_empty()) ? true : false;
}

template <typename T>
void data_base<T>::sort(const string& key)
{
	if (key == "balance") db_.sort(sort_by_balance<T>);
	table();
}



template data_base<supplier>;
//template data_base<seller>;