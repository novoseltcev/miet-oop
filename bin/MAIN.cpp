#define _CRT_SECURE_NO_WARNINGS  // NOLINT(clang-diagnostic-reserved-id-macro)
#include"data_base.h"
#include"seller.h"
#include "supplier.h"
#include<Windows.h>

using namespace std;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title \"Suppliers\" and \"Sellers\"");
	system("color 71");
	int flag;

	/*{
		common *v_common;
		//cout << "Class common: " << v_common->get_year() << endl << endl;
		supplier spl;
		v_common = &spl;
		cout << "Class supplier like common: " << v_common->get_year() << endl << endl;
		
		seller td;
		v_common = &td;
		cout << "Class seller(overriden) like common: " << v_common->get_year() << endl << endl;

		auto v_supplier = *new supplier();
		cout << "Class supplier( not overrden): " << v_supplier.get_year() << endl << endl;
		
		auto v_seller = *new seller();
		cout << "Class seller(overriden): " << v_seller.get_year() << endl << endl;
	}*/
	
	
	data_base<supplier> supplier_data_base("data_supplier.txt");
	data_base<seller> seller_data_base("data_seller.txt");

	SUPPLIERS:
	
	while (true) {
		{
			cout << "|--------------------------------------------|" << endl;
			cout << "|  Меню управления базой данных поставщиков  |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Переключиться на продавцов  ............ 1 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Добавить поставщика в БД  .............. 2 |" << endl;
			cout << "| Распечатать БД поставщиков  ............ 3 |" << endl;
			cout << "| Поиск поставщика по названию фирмы  .... 4 |" << endl;
			cout << "| Фильтр по типу поставщика  ............. 5 |" << endl;
			cout << "| Фильтр по дате поставки ................ 6 |" << endl;
			cout << "| Сортировка по сальдо  .................. 7 |" << endl;
			cout << "| Проверка на вхождение объекта  ......... 8 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Распечатать БД должников ,  ............ 9 |" << endl;
			cout << "| Поиск должников  ...................... 10 |" << endl;
			cout << "| Выход из программы  ................... 11 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "           Введите номер функции: ";
			input_int_with_border(&flag, 1, 11);
			cout << endl << endl;
		}
		switch (flag) {
		case 1: {
				system("cls");
				goto SELLERS;
			}
		case 2: {
				system("cls");
				int start_count;
				cout << "Введите кол-во записей: ";
				input_int_with_border(&start_count, 1, 10);
				cout << endl;
				for (auto i = 1; i <= start_count; i++) {
					system("cls");
					cout << "Введите кол-во записей: " << start_count << endl;
					cout << i << " из " << start_count << endl;
					supplier cur_obj;
					cin >> cur_obj;
					supplier_data_base.push_back(cur_obj);
				}
				break;
			}
		case 3: {
				system("cls");
				if (supplier_data_base.is_empty()) {
					cout << "В БД отсутствуют записи." << endl << endl;
				}
				else {
					supplier_data_base.table();
				}
				break;
			}
		case 4: {
			system("cls");
			auto copied_data_base = search(supplier_data_base);
			if (!copied_data_base.is_empty()) copied_data_base.table();
			else cout << "Не найдено совпадений." << endl;
			break;
		}
		case 5: {
			system("cls");
			data_base<supplier> copied_data_base;
			if (!copied_data_base.filter_by_type(supplier_data_base)) copied_data_base.table();
			else cout << "Не найдено совпадений." << endl;
			break;
		}
		case 6: {
			system("cls");
			::date val_date;
			cin >> val_date;
			int t_flag;
			{
				cout << endl;
				cout << "Поставки с датой меньше заданной ........1" << endl;
				cout << "Поставки с заданной датой  ............. 2" << endl;
				cout << "Поставки с датой больше заданной ........3" << endl;
				cout << "......................................... " << endl;
				cout << "Введите номер функции:\t";
			}
			input_int_with_border(&t_flag, 1, 3);
			data_base<supplier> copied_data_base;
			switch (t_flag)
			{
			case 1:
				{
					if (!copied_data_base.filter_by_data(supplier_data_base, val_date, "<")) copied_data_base.table();
					else cout << "Не найдено совпадений." << endl;
					break;
				}
			case 2:
				{
				if (!copied_data_base.filter_by_data(supplier_data_base, val_date, "==")) copied_data_base.table();
				else cout << "Не найдено совпадений." << endl;
				break;
			}
			case 3:
				{
				if (!copied_data_base.filter_by_data(supplier_data_base, val_date, ">")) copied_data_base.table();
				else cout << "Не найдено совпадений." << endl;
				break;
			}
			default: { break; }
			}
			break;
		}
		case 7: {
			system("cls");
			supplier_data_base.sort("balance");
			break;
		}
		case 8: {
			system("cls");
			supplier reference_obj;
			auto counter = 0;
			cin >> reference_obj;
			for (auto obj : supplier_data_base.get()) {
				if (obj == reference_obj) {
					counter++;
				}
			}
			if (counter == 0) {
				supplier_data_base.push_back(reference_obj);
				cout << "\nВхождений не было обнаружено.";
				cout << "\nЭталонный объект был добавлен в БД." << endl;
			}
			else cout << "\nНайдено " << counter << " вхождений эталонного объекта" << endl;
			break;
		}
		//
		case 9: {
			system("cls");
			try {
				data_base<supplier> debtors_data_base("data_deptor.txt");
				debtors_data_base.table();
			}
			catch (exception e) {
				cout << e.what();
			}
			break;
			}		
		case 10: {
			system("cls");
			data_base<supplier> copied_data_base;
			::date val_date;
			cin >> val_date;
			supplier_data_base.set_debtor(val_date);
			if (copied_data_base.search_debtor(supplier_data_base)) {
				cout << "Не найдено совпадений." << endl;
			}
			else {
				copied_data_base.table();
				int t_flag;
				cout << endl;
				cout << "Сохранить базу должников: Да - 1, Нет - 2" << endl;
				cout << "Введите номер функции:\t";
				input_int_with_border(&t_flag, 1, 2);
				if (t_flag == 1) {
					copied_data_base.save("data_deptor.txt");
				}
				}
				break;
			}
		case 11: {
			system("cls");
			supplier_data_base.save("data_supplier.txt");
			seller_data_base.save("data_seller.txt");
			return 0;
			}
		default: {
			break;
			}
		}
	}

	SELLERS:
	while (true) {
		{
			cout << "|--------------------------------------------|" << endl;
			cout << "|   Меню управления базой данных продавцов   |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Переключиться на поставщиков  .......... 1 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Добавить продавца в БД  ................ 2 |" << endl;
			cout << "| Распечатать БД продавцов   ............. 3 |" << endl;
			cout << "| Поиск продавца по ФИО  ................. 4 |" << endl;
			cout << "| Фильтр по дате продажи ................. 5 |" << endl;
			cout << "| Сортировка по сальдо  .................. 6 |" << endl;
			cout << "| Проверка на вхождение объекта  ......... 7 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Выход из программы  .................... 8 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "           Введите номер функции: ";
			input_int_with_border(&flag, 1, 8);
			cout << endl;
		}
		switch (flag) {
		case 1: {
			system("cls");
			goto SUPPLIERS;
		}
		case 2: {
			system("cls");
			int start_count;
			cout << "Введите кол-во записей: ";
			input_int_with_border(&start_count, 1, 10);
			cout << endl;
			for (auto i = 1; i <= start_count; i++) {
				system("cls");
				cout << "Введите кол-во записей: " << start_count << endl;
				cout << i << " из " << start_count << endl;
				seller cur_obj;
				cin >> cur_obj;
				seller_data_base.push_back(cur_obj);
			}
			break;
		}
		case 3: {
			system("cls");
			if (seller_data_base.is_empty()) {
				cout << "В БД отсутствуют записи." << endl << endl;
			}
			else {
				seller_data_base.table();
			}
			break;
		}
		case 4: {
			system("cls");
			auto copied_data_base = search(seller_data_base);
			if (!copied_data_base.is_empty()) copied_data_base.table();
			else cout << "Не найдено совпадений." << endl;
			break;
		}
		case 5: {
			system("cls");
			::date val_date;
			cin >> val_date;
			int t_flag; {
				cout << endl;
				cout << "Продажи с датой меньше заданной ........1" << endl;
				cout << "Продажи с заданной датой  ............. 2" << endl;
				cout << "Продажи с датой больше заданной ........3" << endl;
				cout << "......................................... " << endl;
				cout << "Введите номер функции:\t";
			}
			input_int_with_border(&t_flag, 1, 3);
			data_base<seller> copied_data_base;
			switch (t_flag) {
			case 1: {
				if (!copied_data_base.filter_by_data(seller_data_base, val_date, "<")) copied_data_base.table();
				else cout << "Не найдено совпадений." << endl;
				break;
			}
			case 2: {
				if (!copied_data_base.filter_by_data(seller_data_base, val_date, "==")) copied_data_base.table();
				else cout << "Не найдено совпадений." << endl;
				break;
			}
			case 3: {
				if (!copied_data_base.filter_by_data(seller_data_base, val_date, ">")) copied_data_base.table();
				else cout << "Не найдено совпадений." << endl;
				break;
			}
			default: {
				break;
				}
			}
			break;
		}
		case 6: {
			system("cls");
			seller_data_base.sort("balance");
			break;
		}
		case 7: {
			system("cls");
			seller reference_obj;
			auto counter = 0;
			cout << reference_obj;
			for (auto obj : seller_data_base.get()) {
				if (obj == reference_obj) { counter++; }
			}
			if (counter == 0) {
				seller_data_base.push_back(reference_obj);
				cout << "\nВхождений не было обнаружено.";
				cout << "\nЭталонный объект был добавлен в БД." << endl;
			}
			else {
				cout << "\nНайдено " << counter << " вхождений эталонного объекта" << endl;
			}
			break;
		}
		case 8: {
			system("cls");
			supplier_data_base.save("data_supplier.txt");
			seller_data_base.save("data_seller.txt");
			return 0;
		}
		default: {
			break;
			}
		}
	}
}
