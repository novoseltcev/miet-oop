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
void data_base<T>::load(const string& filename) {
	ifstream fp(filename);
	if (!fp.is_open()) {
		system("color 74");
		cout << "File opening error: " << filename << endl << endl;
		system("color 71");
	}
	else { fp >> *this; }
}

template <typename T>
void data_base<T>::load(const string& filename, ifstream& fp) {
	try { fp >> *this; }
	catch (...) {
		system("color 74");
		cout << "File opening error: " << filename << endl << endl;
		system("color 71");
	}
}

void data_base<supplier>::save(const string& filename) {
	ofstream fp(filename, ios_base::in | ios_base::trunc);
	if (!fp.is_open()) {
		system("color 74");
		cout << "File opening error: " << filename << endl << endl;
		system("color 71");
	}
	else {
		fp << db_.size() << "\n";
		for (const auto& obj : db_) {
			fp << obj;
		}
	}
}

void data_base<seller>::save(const string& filename) {
	ofstream fp(filename, ios_base::in | ios_base::trunc);
	if (!fp.is_open()) {
		system("color 74");
		cout << "File opening error: " << filename << endl << endl;
		system("color 71");
	}
	else {
		fp << db_.size() << "\n";
		for (const auto& obj : db_) {
			fp << obj;
		}
	}
}


template <typename T>
void data_base<T>::table_line() {
	static_assert(is_same<T, supplier>::value or is_same<T, seller>::value, "undefinded for this data type");
	string var = "";
	if constexpr (is_same<T, seller>::value) {
		var = "-------";
	}
	cout << "-------------------------|-------------------------|------------------" + var +
		"|----------------------|--------------|" << endl;
}

template <typename T>
void data_base<T>::table_head() {
	static_assert(is_same<T, supplier>::value or is_same<T, seller>::value, "undefinded for this data type");
	string separator_txt, main_txt;
	T::table_name(separator_txt, main_txt);

	cout << separator_txt << endl;
	cout << main_txt << endl;
	cout << separator_txt << endl;
	table_line();
}

template <typename T>
double data_base<T>::table_body() {
	static_assert(is_same<T, supplier>::value or is_same<T, seller>::value, "undefinded for this data type");
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
	static_assert(is_same<T, supplier>::value or is_same<T, seller>::value, "undefinded for this data type");
	const auto length = typeid(T) == typeid(supplier) ? 85 : typeid(T) == typeid(seller) ? 79 : 0;
	const string table_end_text = typeid(T) == typeid(supplier)
		? "Total debt: "
		: typeid(T) == typeid(seller)
		? "The overall balance of the sales: "
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
	static_assert(is_same<T, supplier>::value or is_same<T, seller>::value, "undefinded for this data type");
	if (!is_empty()) {
		table_head();
		table_end(table_body());
	}
	else {
		cout.width(63);
		const string var = typeid(T).name() == typeid(supplier).name()
			? "suppliers."
			: typeid(T).name() == typeid(supplier).name()
			? "sellers."
			: "the current data type";
		cout << "The Database does not contain information about"
			<< var << endl;
	}
}


template <typename T>
int data_base<T>::size() { return static_cast<int>(db_.size()); }

template <typename T>
bool data_base<T>::is_empty() { return db_.empty(); }

template <typename T>
void data_base<T>::push_front(const T& obj) { db_.push_front(obj); }

template <typename T>
void data_base<T>::insert(const int pos, const T& obj) {
	auto j = db_.begin();
	for (auto i = 0; i < pos; i++, ++j){}
	db_.insert(j, obj);
}

template <typename T>
void data_base<T>::push_back(const T& obj) { db_.push_back(obj); }

template<typename T>
void data_base<T>::pop_front() { db_.pop_front(); }

template <typename T>
list<T> data_base<T>::get() { return db_; }



bool data_base<supplier>::set_debtor(const date& val_data) {
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
	cout << "Note: 1-raw material supplier, 2-equipment supplier" << endl;
	cout << "Enter the supplier type: ";
	while (true) {
		try {
			is_int(cin, &val_type, 1, 2);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Input error: " << e.what() << endl;
			system("color 71");
			cout << "Try again: ";
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
	cout << "Enter the supplier's company: ";
	while (true) {
		try {
			is_correct_string(cin, v_company, 24);
			break;
		}
		catch (exception_input& e) {
			system("color 74");
			cout << "Input error: " << e.what() << endl;
			system("color 71");
			cout << "Try again: ";
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
bool data_base<T>::filter_by_data(data_base<T>& val_data_base, date& val_data, bool f(T&, date&)) {
	static_assert(is_same<T, supplier>::value or is_same<T, seller>::value, "undefinded for this data type");
	for (auto& i : val_data_base.db_) {
		if (f(i, val_data)) { push_back(i); }
	}
	return (is_empty()) ? true : false;
}

template <typename T>
void data_base<T>::sort(bool comparator(T&, T&)) {
	db_.sort(comparator);
	table();
}


data_base<supplier>& operator>>(ifstream& lhs, data_base<supplier>& rhs) {
	supplier n_obj;
	auto* buff = new char[3];
	lhs.getline(buff, 3);

	const auto val_count = strcmp(buff, "") == 0 ? 0 : stoi(buff);
	for (auto i = 0; i < val_count; i++) {
		lhs >> n_obj;
		rhs.push_back(n_obj);
	}
	delete[] buff;
	return rhs;
}

data_base<seller>& operator>>(ifstream& lhs, data_base<seller>& rhs) {
	seller n_obj;
	auto* buff = new char[4];
	lhs.getline(buff, 4);

	const auto val_count = strcmp(buff, "") == 0 ? 0 : stoi(buff);
	for (auto i = 0; i < val_count; i++) {
		lhs >> n_obj;
		rhs.push_back(n_obj);
	}
	delete[] buff;
	return rhs;
}