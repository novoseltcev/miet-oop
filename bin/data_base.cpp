#include "data_base.h"
#include <list>
using namespace std;

data_base<supplier> search(data_base<supplier>& val_data_base)
{
	data_base<supplier> copied_data_base;
	auto cur_db = val_data_base.get();
	
	string v_company;
	cout << "Введите фирму поставщика: ";
	input_string(v_company, 24);
	for (auto sup_obj : cur_db) {
		auto cur_company = sup_obj.get_company();
			if (cur_company == v_company) { copied_data_base.push_back(sup_obj); }
	}
	return copied_data_base;
}

data_base<seller> search(data_base<seller>& val_data_base)
{
	data_base<seller> copied_data_base;
	auto cur_db = val_data_base.get();
	
	person v_person;
	cin >> v_person;
	for (auto sel_obj : cur_db) {
		auto per_obj = sel_obj.get_person();
		if (per_obj == v_person) { copied_data_base.push_back(sel_obj); }
	}
	return copied_data_base;
}

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
		fp >> *this;
	}
}

template <typename T>
void data_base<T>::table_line() { cout <<"-------------------------|-------------------------|------------------|--------------|----------------------|"<< endl; }

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

template <typename T>
void data_base<T>::table_end(double sum)
{
	const string table_end_text = typeid(T) == typeid(supplier) ? "Общая задолженность:" : typeid(T) == typeid(supplier) ? "Общее сальдо продаж" : "";
	const auto length = typeid(T) == typeid(supplier) ? 83 : typeid(T) == typeid(supplier) ? 92 : 0 ;
	cout << table_end_text;
	cout.setf(ios::right | ios::fixed);
	cout.precision(2);
	cout.width(length);
	cout << sum << "  " << endl;
	cout.unsetf(ios::right | ios::fixed);
	cout << "Кол-во товаров в базе: ";
	cout.width(length);
	cout.setf(ios::left);
	cout << db_.size();
	cout << "  " << endl;
	cout.unsetf(ios::left);
}

//переделать стартовый алгоритм
template <typename T>
data_base<T>::data_base(const string& filename)
{
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
			auto t_obj = *new T();
			cin >> t_obj;
			push_back(t_obj);
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
		const string var = typeid(T).name() == typeid(supplier).name()
			? "поставщиках."
			: typeid(T).name() == typeid(supplier).name() ? "продавцах." : "текущем типе данных";
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


bool data_base<supplier>::filter_by_data(data_base<supplier>& val_data_base, ::date& val_data, const string& flag)
{
	if (flag == ">")
	{
		for (auto& i : val_data_base.db_)
		{
			if (i.get_date() > val_data) { push_back(i); }
		}
	}
	if (flag == ">=")
	{
		for (auto& i : val_data_base.db_)
		{
			if (i.get_date() >= val_data) { push_back(i); }
		}
	}
	if (flag == "==")
	{
		for (auto& i : val_data_base.db_)
		{
			if (i.get_date() == val_data) { push_back(i); }
		}
	}
	if (flag == "<")
	{
		for (auto& i : val_data_base.get())
		{
			if (i.get_date() < val_data) { push_back(i); }
		}
	}
	if (flag == "<=")
	{
		for (auto& i : val_data_base.db_)
		{
			if (i.get_date() <= val_data) { push_back(i); }
		}
	}
	return (is_empty()) ? true : false;
}

bool data_base<supplier>::set_debtor(class date& val_data)
{
	for (auto& obj : db_) {
		if (obj.get_date() < val_data) { !obj; }
	}
	return (is_empty()) ? true : false;
}

bool data_base<supplier>::search_debtor(data_base<supplier>& val_data_base)
{
	for (auto& obj : val_data_base.db_) {
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

data_base<supplier>& operator>>(istream& lhs, data_base<supplier>& rhs)
{
	supplier_impl n_obj{};
	auto* buff = new char[100];
	lhs.getline(buff, 100);

	const auto val_count = strcmp(buff, "")==0 ? 0 : stoi(buff);
	for (auto i = 0; i < val_count; i++)
	{
		lhs >> n_obj;
		/*auto v_company = n_obj.get_company();
		auto v_address = n_obj.get_address();
		auto v_type = n_obj.get_type();
		auto v_balance = n_obj.get_balance();
		auto v_date = n_obj.get_date();
		supplier t_obj(v_company, v_address, v_type, v_balance, v_date);*/
		auto t_obj(n_obj.get());
		rhs.push_back(t_obj);
	}
	return rhs;
}

data_base<seller>& operator>>(istream& lhs, data_base<seller>& rhs)
{
	seller_impl n_obj{};
	auto* buff = new char[100];
	lhs.getline(buff, 100);

	const auto val_count = strcmp(buff, "") == 0 ? 0 : stoi(buff);
	for (auto i = 0; i < val_count; i++)
	{
		lhs >> n_obj;
		/*auto v_person = n_obj.get_person();
		auto v_balance = n_obj.get_balance();
		auto v_date = n_obj.get_date();
		auto t_obj(*new seller(v_person, v_balance, v_date));*/

		auto t_obj(n_obj.get());
		rhs.push_back(t_obj);
	}
	return rhs;
}



template data_base<supplier>;
//template data_base<seller>;