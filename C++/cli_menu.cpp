#include <iostream>

#define CLEAR "\033[2J\033[H"

void menu();
void submenu1();
void submenu2();
void submenu3();

int main() { 
	menu();	

	return 0;
}

void menu()
{
	bool err = false;
	char opt = '-';

	do {
		std::cout << CLEAR;
		
		std::cout << "-------- RINCIPAL MENU --------\n";
		std::cout << "\t1 - SUBMENU 1\n";
		std::cout << "\t2 - SUBMENU 2\n";
		std::cout << "\t3 - SUBMENU 3\n";
		std::cout << "\n\t0 - EXIT\n";
		std::cout << "-------------------------------\n\n";
		if (err) {
			std::cout << "Wut you doin ;)\n"; 
			err = false;
		}
		std::cout << "Option? -> ";
		std::cin >> opt;

		switch (opt) {
			case '0':
				break;
			case '1':
				submenu1();
				break;
			case '2':
				submenu2();
				break;
			case '3':
				submenu3();
				break;
			default:
				err = true;
		}

	} while (opt != '0');	
}

void submenu1()
{
	bool err = false;
	char opt = '-';

	do {
		std::cout << CLEAR;
		
		std::cout << "---------- SUBMENU 1 ----------\n";
		std::cout << "\n\t0 - EXIT\n";
		std::cout << "-------------------------------\n\n";
		if (err) {
			std::cout << "Wut you doin ;)\n"; 
			err = false;
		}
		std::cout << "Option? -> ";
		std::cin >> opt;

		switch (opt) {
			case '0':
				break;
			default:
				err = true;
		}

	} while (opt != '0');	
}

void submenu2()
{
	bool err = false;
	char opt = '-';

	do {
		std::cout << CLEAR;
		
		std::cout << "---------- SUBMENU 2 ----------\n";
		std::cout << "\n\t0 - EXIT\n";
		std::cout << "-------------------------------\n\n";
		if (err) {
			std::cout << "Wut you doin ;)\n"; 
			err = false;
		}
		std::cout << "Option? -> ";
		std::cin >> opt;

		switch (opt) {
			case '0':
				break;
			default:
				err = true;
		}

	} while (opt != '0');	
}

void submenu3()
{
	bool err = false;
	char opt = '-';

	do {
		std::cout << CLEAR;
		
		std::cout << "---------- SUBMENU 3 ----------\n";
		std::cout << "\n\t0 - EXIT\n";
		std::cout << "-------------------------------\n\n";
		if (err) {
			std::cout << "Wut you doin ;)\n"; 
			err = false;
		}
		std::cout << "Option? -> ";
		std::cin >> opt;

		switch (opt) {
			case '0':
				break;
			default:
				err = true;
		}

	} while (opt != '0');	
}
