#include <iostream>
#include <cstring>
#include <sstream>
#include "Warehouse.h"
#include "Product.h"

std::vector<std::string> getParams(std::string command,std::string operation,int paramCount)
{
	std::vector<std::string> params;
	std::istringstream ss(command.substr(operation.size()+1)); // gets the parameters as pure strings, needs to be changed from a constant
	std::string t;
	char del = '|';

	while (std::getline(ss, t, del))
	{
		params.push_back(t);
	}
	if (params.size() != paramCount)
	{
		throw std::invalid_argument("Wrong amount of parameters");
	}
	return params;
}

int main()
{
	//Menu prototype. This will change into a class later on.
	std::string command;
	std::cout << "> ";
	std::getline(std::cin,command);
	bool isOpen=false;

	Warehouse a;
	while (command != "exit")
	{
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
				<< "open <file>	opens <file>" << std::endl
				<< "close			closes currently opened file" << std::endl
				<< "save			saves the currently open file" << std::endl
				<< "saveas <file>	saves the currently open file in <file>" << std::endl
				<< "help			prints this information" << std::endl
				<< "exit			exists the program" << std::endl
				<< "print           prints out information for the products in the warehouse" << std::endl
				<< "add <name|exparation date|entry date|manifacturer|measurement unit|quantity|comment>	adds a product to the warehouse" << std::endl
				<< "remove <name|quantity>		removes product from warehouse" << std::endl
				<< "log <from|to>	prints logs from date to date" << std::endl
				<< "clean			removes all expired products from warehouse" << std::endl;
		}
		else if (command.substr(0,3) == "add" && isOpen)
		{
			//add Milk|28/06/2025|22/06/2025|Pilos|Litres|2|Just milk
			//add Apple|28/06/2025|22/06/2025|Pilos|Kilograms|1|Just an apple
			std::vector<std::string> params = getParams(command,"add",7);

			Product p(params[0],params[1],params[2],params[3],params[4],params[5],params[6]);
			if (a.add(p))
			{
				std::cout << "Product successfuly added" << std::endl;
			}
			else {
				std::cout << "Warehouse is full" << std::endl;
			}
		}
		else if (command.substr(0, 6) == "remove" && isOpen)
		{
			//remove Milk|1
			std::vector<std::string> params = getParams(command, "remove", 2);
			a.remove(params[0], std::stoi(params[1]));
		}
		else if (command.substr(0, 5) == "print" && isOpen)
		{
			a.print();
		}
		std::cout << "> ";
		std::getline(std::cin, command);
	}
	std::cout << "Exiting the program..." << std::endl;
}