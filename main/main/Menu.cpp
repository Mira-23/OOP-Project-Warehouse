#include "Menu.h"

void Menu::open(std::string command)
{
	isOpen = true;
	std::vector<std::string> params = getParams(command, "open", 1);
	filePath = params[0];

	file.open(filePath);

	file >> warehouse;
	file.close();
}

void Menu::close()
{
	isOpen = false;
	file = std::fstream();
	Warehouse newWarehouse = Warehouse();
	warehouse = newWarehouse;
	//clean all loaded info
}

void Menu::save_as(std::string command)
{
	std::vector<std::string> params = getParams(command, "saveas", 1);

	file.open(params[0]);

	file << warehouse;

	file.close();
}

void Menu::save()
{
	save_as("saveas " + filePath);
}

void Menu::help()
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

void Menu::exit()
{
	std::cout << "Exiting the program..." << std::endl;
	std::exit(0);
}

std::vector<std::string> Menu::getParams(std::string command, std::string operation, int paramCount)
{
	std::vector<std::string> params;
	std::istringstream ss(command.substr(operation.size() + 1)); // gets the parameters as pure strings, needs to be changed from a constant
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

Menu::Menu() : isOpen(false), filePath(""), file(std::fstream()), warehouse(Warehouse()) {}

void Menu::start()
{
	std::string command;
	std::cout << "> ";
	std::getline(std::cin, command);

	while (true)
	{
		if (!isOpen)
		{
			if (command.substr(0, 4) == "open")
			{
				open(command);
			}
			else if (command == "exit")
			{
				exit();
			}
		}
		else {
			if (command == "close")
			{
				close();
			}
			else if (command == "save")
			{
				save();
			}
			else if (command.substr(0, 6) == "saveas")
			{
				save_as(command);
			}
			else if (command == "help")
			{
				help();
			}
			else if (command.substr(0, 3) == "add")
			{
				add(command);
			}
			else if (command.substr(0, 6) == "remove")
			{
				remove(command);
			}
			else if (command.substr(0, 3) == "log")
			{
				log(command);
			}
			else if (command == "print")
			{
				print();
			}
			
		}
		
		std::cout << "> ";
		std::getline(std::cin, command);
	}
}

void Menu::add(std::string command)
{
	//add Milk|28/06/2025|22/06/2025|Pilos|Litres|2|Just milk
	//add Apple|28/06/2025|22/06/2025|Pilos|Kilograms|1|Just an apple
	std::vector<std::string> params = getParams(command, "add", 7);

	Product p(params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
	if (warehouse.add(&p))
	{
		std::cout << "Product successfuly added" << std::endl;
	}
	else {
		std::cout << "Warehouse is full" << std::endl;
	}
}

void Menu::remove(std::string command)
{
	//remove Milk|1
	std::vector<std::string> params = getParams(command, "remove", 2);
	warehouse.remove(params[0], std::stoi(params[1]));
}

void Menu::print()
{
	warehouse.print();
}

void Menu::clean()
{
	warehouse.clean();
}

void Menu::log(std::string command)
{
}
