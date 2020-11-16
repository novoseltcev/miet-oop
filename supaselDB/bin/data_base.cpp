// ReSharper disable CppClangTidyClangDiagnosticMissingDeclarations
#include "data_base.h"
#include <fstream>
#include <list>
#include "exception_input.h"
#include "supplier.h"
using namespace std;


template data_base<supplier>;
template data_base<seller>;


template <typename T>
data_base<T>::data_base() = default;

template <typename T>
data_base<T>::data_base(const string& filename) {
	ifstream fp(filename, ios_base::out);
	if (fp.is_open()) {
		load(filename, fp);
		fp.close();
	}
}

template <typename T>
data_base<T>::data_base(const data_base<T>& obj):
	db_(obj.db_) {}

template <typename T>
data_base<T>::~data_base() noexcept { db_.clear(); }


template <typename T>
void data_base<T>::table_line() {
	const string var = typeid(T).name() == typeid(supplier).name() ? ""	: "-------";
	cout << "-------------------------|-------------------------|------------------" + var +
		"|----------------------|--------------|" << endl;
}

template <typename T>
void data_base<T>::table_head() {
	string separator_txt, main_txt;
	T::table_name(separator_txt, main_txt);

	cout << separator_txt << endl;
	cout << main_txt << endl;
	cout << separator_txt << endl;
	table_line();
}

template <typename T>
double data_base<T>::table_body() {
	double sum = 0;
	for (T& obj : db_) {
		cout << obj;
		sum += obj.get_balance();
		table_line();
	}
	return sum;
}

template <typename T>
void data_base<T>::table_end(const double sum) {
	const auto length = typeid(T) == typeid(supplier) ? 86 : typeid(T) == typeid(seller) ? 93 : 0;
	const string table_end_text = typeid(T) == typeid(supplier)
									? "Общая задолженность:"
		                            : typeid(T) == typeid(seller)
										? "Общее сальдо продаж:"
										: "UNKNOWN";
	cout << table_end_text;
	cout.setf(ios::right | ios::fixed);
	cout.precision(2);
	cout.width(length);
	cout << sum << "  |" << endl;
	cout.unsetf(ios::right | ios::fixed);
	cout << "Кол-во товаров в базе: ";
	cout.width(length);
	cout.setf(ios::left);
	cout.width(abs(length - (typeid(T) == typeid(supplier) or typeid(T) == typeid(seller) ? 3 : 0)));
	cout << db_.size();
	cout << "  |" << endl;
	cout.unsetf(ios::left);
}

template <typename T>
void data_base<T>::table() {
	if (!is_empty()) {
		table_head();
		table_end(table_body());
	}
	else {
		cout.width(63);
		const string var = typeid(T).name() == typeid(supplier).name()
			? "поставщиках."
			: typeid(T).name() == typeid(supplier).name()
			? "продавцах."
			: "текущем типе данных";
		cout << "В Базе отсутствует информация о "
			<< var << endl;
	}
}


template <typename T>
void data_base<T>::load(const string& filename) {
	ifstream fp(filename);
	if (!fp.is_open()) {
		system("color 74");
		cout << "Ошибка открытия файла " << filename << endl << endl;
		system("color 71");
	}
	else { fp >> *this; }
}

template <typename T>
void data_base<T>::load(const string& filename, ifstream& fp) {
	try { fp >> *this; }
	catch (...) {
		system("color 74");
		cout << "Ошибка открытия файла " << filename << endl << endl;
		system("color 71");
	}
}

void data_base<supplier>::save(const string& filename) {
	ofstream fp(filename, ios_base::in | ios_base::trunc);
	if (!fp.is_open()) {
		system("color 74");
		cout << "Ошибка открытия файла " << filename << endl << endl;
		system("color 71");
	}
	else {
		fp << db_.size() << "\n";
		for (auto& obj : db_) {
			supplier_impl n_obj(obj);
			fp << n_obj;
		}
	}
}

void data_base<seller>::save(const string& filename) {
	ofstream fp(filename, ios_base::in | ios_base::trunc);
	if (!fp.is_open()) {
		system("color 74");
		cout << "Ошибка открытия файла " << filename << endl << endl;
		system("color 71");
		cout << "Повторите ввод: ";
	}
	else {
		fp << db_.size() << "\n";
		for (auto& obj : db_) {
			seller_impl n_obj(obj);
			fp << n_obj;
		}
	}
}


template <typename T>
bool data_base<T>::is_empty() { return db_.empty(); }

template <typename T>
void data_base<T>::push_back(T& obj) { db_.push_back(obj); }

template <typename T>
list<T> data_base<T>::get() { return db_; }


bool data_base<supplier>::set_debtor(class date& val_data) {
	for (auto& obj : db_) {
		if (obj.get_date() < val_data) { !obj; }
	}
	return (is_empty()) ? true : false;
}

bool data_base<supplier>::search_debtor(data_base<supplier>& val_data_base) {
	for (auto& obj : val_data_base.db_) {
		if (obj.get_debtor()) { push_back(obj); }
	}
	return (is_empty()) ? true : false;
}

bool data_base<supplier>::filter_by_type(data_base<supplier>& val_data_base) {
	auto val_type = -1;
	cout << "Примечание: 1 - поставщик сырья, 2 - поставщик оборудования" << endl;
	cout << "Введите тип поставщика: ";
	while (true) {
		try {
			is_int(cin, &val_type, 1, 2);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Ошибка ввода: " << e.what() << endl;
			system("color 71");
		}
	}
	for (auto& i : val_data_base.db_) {
		if (i.get_type() == val_type) { push_back(i); }
	}
	return (is_empty()) ? true : false;
}

data_base<supplier> search(data_base<supplier>& val_data_base) {
	data_base<supplier> copied_data_base;
	string v_company;
	auto cur_db = val_data_base.get();
	cout << "Введите фирму поставщика: ";
	while (true) {
		try {
			is_correct_string(cin, v_company, 24);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Ошибка ввода: " << e.what() << endl;
			system("color 71");
		}
	}
	for (auto sup_obj : cur_db) {
		if (sup_obj.get_company() == v_company) { copied_data_base.push_back(sup_obj); }
	}
	return copied_data_base;
}

data_base<seller> search(data_base<seller>& val_data_base) {
	data_base<seller> copied_data_base;
	person v_person;
	auto cur_db = val_data_base.get();
	cin >> v_person;
	for (auto sel_obj : cur_db) {
		auto per_obj = sel_obj.get_person();
		if (per_obj == v_person) { copied_data_base.push_back(sel_obj); }
	}
	return copied_data_base;
}


template <typename T>
bool data_base<T>::filter_by_data(data_base<T>& val_data_base, date& val_data, bool func(T&, date&)) {
	for (auto& i : val_data_base.db_) {
		if (func(i, val_data)) { push_back(i); }
	}
	return (is_empty()) ? true : false;
}

template <typename T>
void data_base<T>::sort(bool comparator(T&, T&)) {
	db_.sort(comparator);
	table();
}


data_base<supplier>& operator>>(istream& lhs, data_base<supplier>& rhs) {
	supplier_impl n_obj{};
	auto* buff = new char[3];
	lhs.getline(buff, 3);

	const auto val_count = strcmp(buff, "") == 0 ? 0 : stoi(buff);
	for (auto i = 0; i < val_count; i++) {
		lhs >> n_obj;
		auto t_obj(n_obj.get());
		rhs.push_back(t_obj);
	}
	return rhs;
}

data_base<seller>& operator>>(istream& lhs, data_base<seller>& rhs) {
	seller_impl n_obj{};
	auto* buff = new char[4];
	lhs.getline(buff, 4);

	const auto val_count = strcmp(buff, "") == 0 ? 0 : stoi(buff);
	for (auto i = 0; i < val_count; i++) {
		lhs >> n_obj;
		auto t_obj(n_obj.get());
		rhs.push_back(t_obj);
	}
	return rhs;
}