#include <iostream>
#include "Menu.hpp"

/// <summary>
/// Only serves as a way to start the program by using the start method of the class Menu
/// </summary>
/// <returns></returns>
int main()
{
	//Menu<std::ostream> menu;
	//menu.start(std::cout);

	//examples:
	std::stringstream ss;
	Menu<std::stringstream> string_menu;

	string_menu.open("open test.txt",ss);

	string_menu.add("add Milk|2025-06-22|2025-06-28|Pilos|2|Litres|Just milk",ss);
	string_menu.add("add Milk|2025-06-22|2025-06-30|Pilos|3|Litres|Just milk",ss);
	string_menu.add("add Apple|2025-06-22|2025-06-30|Big Farm|3|Kilograms|Just apples",ss);

	string_menu.print(ss);

	string_menu.check_losses("checklosses Milk|3|2|2025-05-29|2025-07-31",ss);

	string_menu.add("add Apple|2023-06-22|2024-06-30|Big Farm|3|Kilograms|Just apples",ss);
	string_menu.clean(ss);

	string_menu.remove("remove Milk|1",ss);
	string_menu.remove("remove Milk|1",ss);

	string_menu.log("log 2024-05-29|2026-05-31",ss);

	string_menu.print(ss);

	string_menu.save(ss);

	string_menu.close(ss);

	std::cout << ss.str();
}