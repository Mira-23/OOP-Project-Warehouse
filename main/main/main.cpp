#include <iostream>
#include <cstring>
#include "Warehouse.h"
#include "Product.h"

int main()
{
	//Menu prototype. This will change into a class later on.
	std::string command;
	std::cout << "> ";
	std::cin >> command;
	bool isOpen=false;

	Warehouse a;
	while (command != "exit")
	{
		std::cout << "> ";
		std::cin >> command;
		if (command == "open" && !isOpen)
		{
			isOpen = true;
		}
		else if (command == "close" && isOpen)
		{
			isOpen = false;
		}
		else if (command == "save" && isOpen)
		{
			//save code
		}
		else if (command == "save as" && isOpen)
		{
			//save as code
		}
		else if (command == "help" && isOpen)
		{
			std::cout << "The following commands are supported : " << std::endl
				<< "open <file>	opens <file>"
				<< "close			closes currently opened file" << std::endl
				<< "save			saves the currently open file" << std::endl
				<< "saveas <file>	saves the currently open file in <file>" << std::endl
				<< "help			prints this information" << std::endl
				<< "exit			exists the program" << std::endl
				<< "print           prints out information for the products in the warehouse" << std::endl
				<< "add <name/exparation date/entry date/manifacturer/measurement unit/quantity/shelf id/comment>	adds a product to the warehouse" << std::endl
				<< "remove <name/quantity>		removes product from warehouse" << std::endl
				<< "log <from/to>	prints logs from date to date" << std::endl
				<< "clean			removes all expired products from warehouse" << std::endl;
		}
		else if (command == "add" && isOpen)
		{
			//add code
		}
	}
	std::cout << "Exiting the program..." << std::endl;
}