#define _CRT_SECURE_NO_WARNINGS  // NOLINT(clang-diagnostic-reserved-id-macro)
#include<Windows.h>
#include"data_base.h"
#include "exception_input.h"
#include"seller.h"
#include "supplier.h"

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define NEW DEBUG_NEW

using namespace std;


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system(R"(title "Suppliers" and "Sellers")");
	system("color 71");

{
	data_base<supplier> supplier_data_base("data_supplier.txt");
	data_base<seller> seller_data_base("data_seller.txt");

	auto flag = 0;

SUPPLIERS:

	while (true) {
		{
			cout << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "|  ���� ���������� ����� ������ �����������  |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| ������������� �� ���������  ............ 1 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| �������� ���������� � ��  .............. 2 |" << endl;
			cout << "| ����������� �� ��������  ............... 3 |" << endl;
			cout << "| ������� ������ ��������  ............... 4 |" << endl;
			cout << "| ����� �������� �� �������� �����  ...... 5 |" << endl;
			cout << "| ������ �� ���� ����������  ............. 6 |" << endl;
			cout << "| ������ �� ���� �������� ................ 7 |" << endl;
			cout << "| ���������� �� ������  .................. 8 |" << endl;
			cout << "| �������� �� ��������� �������  ......... 9 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| ����������� �� ���������   ............ 10 |" << endl;
			cout << "| ����� ���������  ...................... 11 |" << endl;
			cout << "| ����� �� ���������  ................... 12 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "           ������� ����� �������: ";
			while (true) {
				try {
					is_int(cin, &flag, 1, 12);
					break;
				}
				catch (exception_input& e) {
					system("color 74");
					cout << "Input error: " << e.what() << endl;
					system("color 71");
					cout << "Try again: ";
				}
			}
			cout << endl;
		}
		switch (flag) {
		case 1:
		{
			system("cls");

			goto SELLERS;
		}
		case 2:
		{
			system("cls");

			int start_count;
			if (!supplier_data_base.is_empty()) {
				int t_flag;
				{
					cout << "|---------------------------------------------------|" << endl;
					cout << "|      ���� ���������� �������� � ���� ������       |" << endl;
					cout << "|---------------------------------------------------|" << endl;
					cout << "| �������� �������(�) � ������ ...................1 |" << endl;
					cout << "| �������� �������(�) � ����������� �������  ... 2 |" << endl;
					cout << "| �������� �������(�) � ����� ....................3 |" << endl;
					cout << "|---------------------------------------------------|" << endl;
					cout << "| ������ .........................................4 |" << endl;
					cout << "|---------------------------------------------------|" << endl;
					cout << "            ������� ����� ��������:\t";
					while (true) {
						try {
							is_int(cin, &t_flag, 1, 4);
							break;
						}
						catch (exception_input& e) {
							system("color 74");
							cout << "������ �����: " << e.what() << endl;
							system("color 71");
							cout << "��������� ����: ";
						}
					}
					cout << endl;
					if (t_flag == 4) { continue; }
				}
				cout << endl << "������� ���-�� �������(�� 1 �� 10): ";
				while (true) {
					try {
						is_int(cin, &start_count, 1, 10);
						break;
					}
					catch (exception_input& e) {
						system("color 74");
						cout << "������ �����: " << e.what() << endl;
						system("color 71");
						cout << "��������� ����: ";
					}
				}
				switch (t_flag) {
				case 1:
				{
					for (auto i = 1; i <= start_count; i++) {
						system("cls");
						cout << "���������� � ������" << endl;
						cout << "�������: " << i << " �� " << start_count << endl << endl;
						supplier cur_obj;
						cin >> cur_obj;
						supplier_data_base.push_front(cur_obj);
					}
					break;
				}
				case 2:
				{
					for (auto i = 1; i <= start_count; i++) {
						system("cls");
						cout << "���������� � ������������ �����" << endl;
						cout << "�������: " << i << " �� " << start_count << endl << endl;
						int pos;
						auto db_size = supplier_data_base.size();
						cout << "������� ������� �������: ";
						while (true) {
							try {
								is_int(cin, &pos, 1, db_size);
								break;
							}
							catch (exception_input& e) {
								system("color 74");
								cout << "������ �����: " << e.what() << endl;
								system("color 71");
								cout << "��������� ����: ";
							}
						}
						supplier cur_obj;
						cin >> cur_obj;
						supplier_data_base.insert(pos - 1, cur_obj);
					}
					break;
				}
				case 3:
				{
					for (auto i = 1; i <= start_count; i++) {
						system("cls");
						cout << "���������� � �����" << endl;
						cout << "�������: " << i << " �� " << start_count << endl << endl;
						supplier cur_obj;
						cin >> cur_obj;
						supplier_data_base.push_back(cur_obj);
					}
					break;
				}
				default: { break; }
				}
			}
			else {
				cout << endl << "������� ���-�� �������(�� 1 �� 10): ";
				while (true) {
					try {
						is_int(cin, &start_count, 1, 10);
						break;
					}
					catch (exception_input& e) {
						system("color 74");
						cout << "������ �����: " << e.what() << endl;
						system("color 71");
						cout << "��������� ����: ";
					}
				}
				for (auto i = 1; i <= start_count; i++) {
					system("cls");
					cout << "�������: " << i << " �� " << start_count << endl << endl;
					supplier cur_obj;
					cin >> cur_obj;
					supplier_data_base.push_back(cur_obj);
				}
			}
			break;
		}
		case 3:
		{
			system("cls");

			if (supplier_data_base.is_empty()) {
				cout << "There are no entries in the database." << endl << endl;
			}
			else { supplier_data_base.table(); }
			break;
		}
		case 4:
		{
			system("cls");

			if (!supplier_data_base.is_empty()) {
				data_base<supplier> deleting_supplier;
				deleting_supplier.push_front(*supplier_data_base.get().begin());
				deleting_supplier.table();
				cout << endl;
				cout << "������� ������ � ��������: �� - 1, ��� - 2" << endl;
				cout << "������� ����� �������:\t";
				int t_flag;
				while (true) {
					try {
						is_int(cin, &t_flag, 1, 2);
						break;
					}
					catch (exception_input& e) {
						system("color 74");
						cout << "Input error: " << e.what() << endl;
						system("color 71");
						cout << "Try again: ";
					}
				}
				if (t_flag == 1) {
					supplier_data_base.pop_front();
					cout << "Completed..." << endl;
				}
			}
			else { cout << "� �� ����������� ������." << endl; }
			break;
		}
		case 5:
		{
			system("cls");

			auto copied_data_base = search(supplier_data_base);
			if (!copied_data_base.is_empty()) { copied_data_base.table(); }
			else { cout << "�� ������� ����������." << endl; }
			break;
		}
		case 6:
		{
			system("cls");

			data_base<supplier> copied_data_base;
			if (!copied_data_base.filter_by_type(supplier_data_base)) {
				copied_data_base.table();
			}
			else { cout << "�� ������� ����������." << endl; }
			break;
		}
		case 7:
		{
			system("cls");

			int t_flag;
			{
				cout << "|--------------------------------------------|" << endl;
				cout << "|       ���� ������ �������� �� ����         |" << endl;
				cout << "|--------------------------------------------|" << endl;
				cout << "| �������� � ����� ������ �������� ........1 |" << endl;
				cout << "| �������� � �������� �����  ............. 2 |" << endl;
				cout << "| �������� � ����� ������ �������� ........3 |" << endl;
				cout << "|--------------------------------------------|" << endl;
				cout << "| ������ ..................................4 |" << endl;
				cout << "|--------------------------------------------|" << endl;
				cout << "         ������� ����� �������:\t";
				while (true) {
					try {
						is_int(cin, &t_flag, 1, 4);
						break;
					}
					catch (exception_input& e) {
						system("color 74");
						cout << "Input error: " << e.what() << endl;
						system("color 71");
						cout << "Try again: ";
					}
				}
				cout << endl;
				if (t_flag == 4) { continue; }
			}
			date val_date;
			cin >> val_date;
			data_base<supplier> copied_data_base;
			switch (t_flag) {
			case 1:
			{
				if (!copied_data_base.filter_by_data(supplier_data_base, val_date,
					[](supplier& a, date& b) -> bool { return a.get_date() < b; })
					) {
					copied_data_base.table();
				}
				else { cout << "�� ������� ����������." << endl; }
				break;
			}
			case 2:
			{
				if (!copied_data_base.filter_by_data(supplier_data_base, val_date,
					[](supplier& a, date& b) -> bool { return a.get_date() == b; })
					) {
					copied_data_base.table();
				}
				else { cout << "�� ������� ����������." << endl; }
				break;
			}
			case 3:
			{
				if (!copied_data_base.filter_by_data(supplier_data_base, val_date,
					[](supplier& a, date& b) -> bool { return a.get_date() > b; })
					) {
					copied_data_base.table();
				}
				else { cout << "�� ������� ����������." << endl; }
				break;
			}
			default: { break; }
			}
			break;
		}
		case 8:
		{
			system("cls");

			supplier_data_base.sort(sort_by_balance);
			break;
		}
		case 9:
		{
			system("cls");

			supplier reference_obj;
			auto counter = 0;
			cin >> reference_obj;
			for (const auto& obj : supplier_data_base.get()) {
				if (obj == reference_obj) { counter++; }
			}
			if (counter == 0) {
				cout << "\n��������� �� ���� ����������.";
				supplier_data_base.push_back(reference_obj);
				cout << "\n��������� ������ ��� �������� � ��." << endl;
			}
			else {
				cout << "\n������� " << counter << " ��������� ���������� �������" << endl;
			}
			break;
		}
		case 10:
		{
			system("cls");

			data_base<supplier> debtors_data_base("data_deptor.txt");
			debtors_data_base.table();
			break;
		}
		case 11:
		{
			system("cls");

			data_base<supplier> copied_data_base;
			date val_date;
			cin >> val_date;
			supplier_data_base.set_debtor(val_date);
			if (copied_data_base.search_debtor(supplier_data_base)) {
				cout << "�� ������� ����������." << endl;
			}
			else {
				copied_data_base.table();
				cout << endl;
				cout << "��������� ���� ���������: �� - 1, ��� - 2" << endl;
				cout << "������� ����� �������:\t";
				int t_flag;
				while (true) {
					try {
						is_int(cin, &t_flag, 1, 2);
						break;
					}
					catch (exception_input& e) {
						system("color 74");
						cout << "Input error: " << e.what() << endl;
						system("color 71");
						cout << "Try again: ";
					}
				}
				if (t_flag == 1) {
					copied_data_base.save("data_deptor.txt");
				}
			}
			break;
		}
		case 12:
		{
			system("cls");

			supplier_data_base.save("data_supplier.txt");
			seller_data_base.save("data_seller.txt");
				
			goto EXIT;
		}
		default: { break; }
		}
	}

SELLERS:
	while (true) {
		{
			cout << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "|         Database management menu           |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Switch to suppliers  ................... 1 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Add a sale to the database  ............ 2 |" << endl;
			cout << "| Print the sellers database   ........... 3 |" << endl;
			cout << "| Delete the first sale  ................. 4 |" << endl;
			cout << "| Search for a seller by full name  ...... 5 |" << endl;
			cout << "| Filter by date of sale ................. 6 |" << endl;
			cout << "| Sorting by balance  .................... 7 |" << endl;
			cout << "| Check for presence of object  .......... 8 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "| Exit  .................................. 9 |" << endl;
			cout << "|--------------------------------------------|" << endl;
			cout << "          Enter the function number: ";
			while (true) {
				try {
					is_int(cin, &flag, 1, 9);
					break;
				}
				catch (exception_input& e) {
					system("color 74");
					cout << "Input error: " << e.what() << endl;
					system("color 71");
					cout << "Try again: ";
				}
			}
			cout << endl;
		}
		switch (flag) {
		case 1:
		{
			system("cls");

			goto SUPPLIERS;
		}
		case 2:
		{
			system("cls");

			int start_count;
			if (!seller_data_base.is_empty()) {
				int t_flag;
				{

					cout << "|---------------------------------------------------|" << endl;
					cout << "|       ���� ���������� ������� � ���� ������       |" << endl;
					cout << "|---------------------------------------------------|" << endl;
					cout << "| �������� �������(�) � ������ ...................1 |" << endl;
					cout << "| �������� �������(�) � ����������� �������  ... 2 |" << endl;
					cout << "| �������� �������(�) � ����� ....................3 |" << endl;
					cout << "|---------------------------------------------------|" << endl;
					cout << "| ������ .........................................4 |" << endl;
					cout << "|---------------------------------------------------|" << endl;
					cout << "            ������� ����� ��������:\t";
					while (true) {
						try {
							is_int(cin, &t_flag, 1, 4);
							break;
						}
						catch (exception_input& e) {
							system("color 74");
							cout << "Input error: " << e.what() << endl;
							system("color 71");
							cout << "Try again: ";
						}
					}
					cout << endl;
					if (t_flag == 4) { continue; }
				}
				cout << endl << "������� ���-�� �������(�� 1 �� 10): ";
				while (true) {
					try {
						is_int(cin, &start_count, 1, 10);
						break;
					}
					catch (exception_input& e) {
						system("color 74");
						cout << "������ �����: " << e.what() << endl;
						system("color 71");
						cout << "��������� ����: ";
					}
				}
				switch (t_flag) {
				case 1:
				{
					for (auto i = 1; i <= start_count; i++) {
						system("cls");
						cout << "���������� � ������" << endl;
						cout << "�������: " << i << " �� " << start_count << endl << endl;
						seller cur_obj;
						cin >> cur_obj;
						seller_data_base.push_front(cur_obj);
					}
					break;
				}
				case 2:
				{
					for (auto i = 1; i <= start_count; i++) {
						system("cls");
						cout << "���������� � ������������ �����" << endl;
						cout << "�������: " << i << " �� " << start_count << endl << endl;
						int pos;
						auto db_size = seller_data_base.size();
						cout << "������� ������� �������: ";
						while (true) {
							try {
								is_int(cin, &pos, 1, db_size);
								break;
							}
							catch (exception_input& e) {
								system("color 74");
								cout << "������ �����: " << e.what() << endl;
								system("color 71");
								cout << "��������� ����: ";
							}
						}
						seller cur_obj;
						cin >> cur_obj;
						seller_data_base.insert(pos - 1, cur_obj);
					}
					break;
				}
				case 3:
				{
					for (auto i = 1; i <= start_count; i++) {
						system("cls");
						cout << "���������� � �����" << endl;
						cout << "�������: " << i << " �� " << start_count << endl << endl;
						seller cur_obj;
						cin >> cur_obj;
						seller_data_base.push_back(cur_obj);
					}
					break;
				}
				default: { break; }
				}
			}
			else {
				cout << endl << "������� ���-�� �������(�� 1 �� 10): ";
				while (true) {
					try {
						is_int(cin, &start_count, 1, 10);
						break;
					}
					catch (exception_input& e) {
						system("color 74");
						cout << "Input error: " << e.what() << endl;
						system("color 71");
						cout << "Try again: ";
					}
				}
				for (auto i = 1; i <= start_count; i++) {
					system("cls");
					cout << "�������: " << i << " �� " << start_count << endl << endl;
					seller cur_obj;
					cin >> cur_obj;
					seller_data_base.push_back(cur_obj);
				}
			}
			break;
		}
		case 3:
		{
			system("cls");

			if (seller_data_base.is_empty()) { cout << "There are no entries in the database." << endl << endl; }
			else { seller_data_base.table(); }
			break;
		}
		case 4:
		{
			system("cls");

			if (!seller_data_base.is_empty()) {
				data_base<seller> deleting_seller;
				deleting_seller.push_front(*seller_data_base.get().begin());
				deleting_seller.table();
				cout << endl;
				cout << "������� ������ � �������: �� - 1, ��� - 2" << endl;
				cout << "������� ����� �������:\t";
				int t_flag;
				while (true) {
					try {
						is_int(cin, &t_flag, 1, 2);
						break;
					}
					catch (exception_input& e) {
						system("color 74");
						cout << "Input error: " << e.what() << endl;
						system("color 71");
						cout << "Try again: ";
					}
				}
				if (t_flag == 1) {
					seller_data_base.pop_front();
					cout << "�������..." << endl;
				}
			}
			else { cout << "� �� ����������� ������." << endl; }
			break;
		}
		case 5:
		{
			system("cls");

			auto copied_data_base = search(seller_data_base);
			if (!copied_data_base.is_empty()) copied_data_base.table();
			else cout << "�� ������� ����������." << endl;
			break;
		}
		case 6:
		{
			system("cls");

			int t_flag;
			{
				cout << "|--------------------------------------------|" << endl;
				cout << "|        ���� ������ ������ �� ����          |" << endl;
				cout << "|--------------------------------------------|" << endl;
				cout << "| �������� � ����� ������ �������� ........1 |" << endl;
				cout << "| �������� � �������� �����  ............. 2 |" << endl;
				cout << "| �������� � ����� ������ �������� ........3 |" << endl;
				cout << "|--------------------------------------------|" << endl;
				cout << "| ������ ..................................4 |" << endl;
				cout << "|--------------------------------------------|" << endl;
				cout << "         ������� ����� �������:\t";
				while (true) {
					try {
						is_int(cin, &t_flag, 1, 4);
						break;
					}
					catch (exception_input& e) {
						system("color 74");
						cout << "Input error: " << e.what() << endl;
						system("color 71");
						cout << "Try again: ";
					}
				}
				cout << endl;
				if (t_flag == 4) { continue; }
			}
			data_base<seller> copied_data_base;
			date val_date;
			cin >> val_date;
			switch (t_flag) {
			case 1:
			{
				if (!copied_data_base.filter_by_data(seller_data_base, val_date,
					[](seller& a, date& b) -> bool { return a.get_date() < b; })
					) {
					copied_data_base.table();
				}
				else { cout << "�� ������� ����������." << endl; }
				break;
			}
			case 2:
			{
				if (!copied_data_base.filter_by_data(seller_data_base, val_date,
					[](seller& a, date& b) -> bool { return a.get_date() == b; })
					) {
					copied_data_base.table();
				}
				else { cout << "�� ������� ����������." << endl; }
				break;
			}
			case 3:
			{
				if (!copied_data_base.filter_by_data(seller_data_base, val_date,
					[](seller& a, date& b) -> bool { return a.get_date() > b; })
					) {
					copied_data_base.table();
				}
				else { cout << "�� ������� ����������." << endl; }
				break;
			}
			default: { break; }
			}
			break;
		}
		case 7:
		{
			system("cls");

			seller_data_base.sort();
			break;
		}
		case 8:
		{
			system("cls");

			seller reference_obj;
			auto counter = 0;
			cout << reference_obj;
			for (const auto& obj : seller_data_base.get()) {
				if (obj == reference_obj) { ++counter; }
			}
			if (counter == 0) {
				seller_data_base.push_back(reference_obj);
				cout << "\n��������� �� ���� ����������.";
				cout << "\n��������� ������ ��� �������� � ��." << endl;
			}
			else {
				cout << "\n������� " << counter << " ��������� ���������� �������" << endl;
			}
			break;
		}
		case 9:
		{
			system("cls");

			supplier_data_base.save("data_supplier.txt");
			seller_data_base.save("data_seller.txt");
				
			goto EXIT;
		}
		default: { break; }
		}
	}

}
EXIT:

	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
