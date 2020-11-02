//#define _CRT_SECURE_NO_WARNINGS
// ReSharper disable CppClangTidyReadabilityNonConstParameter
#include"check_input.h"
using namespace std;

void input_double(double* val_balance)
{
	cin >> *val_balance;
	while (cin.fail() || cin.rdbuf()->in_avail() != sizeof*val_balance / sizeof(double))
	{
		system("color 74");
		cout << "{Ошибка.} Повторите ввод:";
		system("color 71");
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> *val_balance;
	}
}

bool name_fail(string& string)
{
	auto flag = false;
	auto n_string = 0;
	for (char sz_string : string)
	{
		n_string = static_cast<int>(sz_string);
		if (!flag)
		{
			flag = true;
			if (!(n_string == -88 || n_string == -72 ||
				-64 <= n_string && n_string <= -1 ||
				65 <= n_string && n_string <= 90 ||
				97 <= n_string && n_string <= 122))
			{
				system("color 74");
				cout << "{Ошибка. Название не может начинаться со специальных знаков и чисел.}" << endl;
				system("color 71");
				return true;
			}
		}
		if (!(n_string == -88 || n_string == -72 ||
			-64 <= n_string && n_string <= -1 ||
			n_string == 32 || n_string == 34 ||
			n_string == 45 || n_string == 46 ||
			48 <= n_string && n_string <= 57 ||
			65 <= n_string && n_string <= 90 ||
			97 <= n_string && n_string <= 122))
		{
			system("color 74");
			cout << "{Ошибка. Недопустимо использование спец. символов, кроме \"-\" и \".\"}" << endl;
			system("color 71");
			return true;
		}
	}
	return false;
}


void input_string(string& string, int string_size)
{
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, string);
	while (name_fail(string) || static_cast<int>(string.length()) > string_size)
	{
		if (static_cast<int>(string.length()) > string_size)
		{
			system("color 74");
			cout << "{Ошибка. Допустимая длина - 21 символ.}" << endl;
			system("color 71");
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Повторите ввод: ";
		getline(cin, string);
	}
}

void input_int_with_border(int* value, const int down_border = INT16_MIN, const int up_border = INT16_MAX)
{
	cin >> *value;
	while (cin.fail() ||
		cin.rdbuf()->in_avail() != sizeof*value / sizeof(int) ||
		*value < down_border || *value > up_border)
	{
		system("color 74");
		cout << "{Ошибка.} Повторите ввод: ";
		system("color 71");
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> *value;
	}
}
