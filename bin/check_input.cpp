//#define _CRT_SECURE_NO_WARNINGS
// ReSharper disable CppClangTidyReadabilityNonConstParameter
#include"check_input.h"
using namespace std;


void is_int(istream& lhs, int* value, const int down_border = INT16_MIN, const int up_border = INT16_MAX) {
	lhs.clear();
	lhs.ignore(cin.rdbuf()->in_avail());
	lhs >> *value;
	if (lhs.fail() or lhs.rdbuf()->in_avail() != sizeof(*value) / sizeof(int) or !(down_border <= *value <= up_border)
	) { throw exception_input("Введено некорректное значение"); }
}

void is_double(istream& lhs, double* val_balance) {
	lhs.clear();
	lhs.ignore(cin.rdbuf()->in_avail());
	lhs >> *val_balance;
	if (lhs.fail() or lhs.rdbuf()->in_avail() != sizeof(*val_balance) / sizeof(double)) {
		throw exception_input("Введено некорректное значение");
	}
}

void is_correct_string(istream& lhs, string& string, int size) {
	lhs.clear();
	lhs.ignore(cin.rdbuf()->in_avail());
	getline(lhs, string);
	auto c_str = string.c_str();
	auto string_size = static_cast<int>(string.length());
	auto flag = true;
	if (string_size > size or string_size == 0) {
		throw exception_input(*new std::string("Допустимая длина - " + to_string(size) + " символ."));
	}

	if (!(static_cast<int>(*c_str) == -88 or static_cast<int>(*c_str) == -72 or -64 <= static_cast<int>(*c_str) and
			static_cast<int>(*c_str) <= -1)
		and !isalpha(*c_str)) { throw exception_input("Название не может начинаться со специальных знаков и чисел"); }

	for (int i = 1; i < string.length(); i++) {
		auto el = *(c_str + i);
		auto int_el = static_cast<int>(el);
		if (!(int_el == -88 or int_el == -72 or -64 <= int_el <= -1)
			and !(int_el == 32 or int_el == 34 or
				int_el == 45 or int_el == 46 or
				48 <= int_el <= 57)
			and !isalpha(el)) {
			throw exception_input("Недопустимо использование спец. символов, кроме \"-\" и \".\"");
		}
	}
}

/// <summary>
/// Ввод и проверка строки имени собственного.
/// Условия: длина строки от 1 до size включитьельно,
///			 введены только латинские или только кириллические буквы.
/// </summary>
/// <param name="string">ref out</param>
/// <param name="size">максимальная длина вводимой строки</param>
void is_name(istream& lhs, string& string, int size) {
	lhs.clear();
	lhs.ignore(cin.rdbuf()->in_avail());
	getline(lhs, string);
	auto c_str = string.c_str();
	auto string_size = static_cast<int>(string.length());
	auto flag = true;
	if (string_size > size or string_size == 0) {
		throw exception_input(*new std::string("Допустимая длина - " + to_string(size) + " символ."));
	}
	for (int i = 0; i < string.length(); i++) {
		auto el = *(c_str + i);
		auto int_el = static_cast<int>(el);
		if (!(int_el == -88 or int_el == -72 or
			-64 <= int_el and int_el <= -1)) {
			if (!isalpha(el) or !flag)
				throw exception_input("Имя собственное может содержать только кирилические или только латинские буквы");
		}
		else { flag = false; }
	}
}

void is_date(istream& lhs, int* v_year, int* v_month, int* v_day) {
	lhs.clear();
	lhs.ignore(cin.rdbuf()->in_avail());
	scanf_s("%d.%d.%d", v_day, v_month, v_year);
	if (*v_day < 1 || *v_day > 31 || *v_month > 12 || *v_year < 0) {
		throw exception_input("Попытка присвоить дате неккоректные значения");
	}
}