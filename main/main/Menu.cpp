#include "Menu.h"

Menu::Menu() : isOpen(false), filePath(""), warehouse(Warehouse()) {}

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
				try {
					open(command);
				}
				catch (std::exception ex) {
					std::cout << ex.what() << std::endl;
					exit();
				}

			}
			else if (command == "exit")
			{
				exit();
			}
			else {
				std::cout << "Please open a file first." << std::endl;
			}
		}
		else {
			if (command == "close")
			{
				close();
			}
			else if (command == "save")
			{
				try {
					save();
				}
				catch (std::exception ex) {
					std::cout << ex.what() << std::endl;
					exit();
				}
			}
			else if (command.substr(0, 6) == "saveas")
			{
				try {
					save_as(command);
				}
				catch (std::exception ex) {
					std::cout << ex.what() << std::endl;
					exit();
				}
				
			}
			else if (command == "help")
			{
				help();
			}
			else if (command.substr(0, 3) == "add")
			{
				try {
					add(command);
				}
				catch (std::exception ex) {
					std::cout << ex.what() << std::endl;
				}
			}
			else if (command.substr(0, 6) == "remove")
			{
				try {
					remove(command);
				}
				catch (std::exception ex) {
					std::cout << ex.what() << std::endl;
					exit();
				}
			}
			else if (command.substr(0, 3) == "log")
			{
				try {
					log(command);
				}
				catch (std::exception ex) {
					std::cout << ex.what() << std::endl;
					exit();
				}
			}
			else if (command.substr(0, 11) == "checklosses")
			{
				try {
					check_losses(command);
				}
				catch (std::exception ex) {
					std::cout << ex.what() << std::endl;
					exit();
				}
			}
			else if (command == "clean")
			{
				try {
					clean();
				}
				catch (std::exception ex) {
					std::cout << ex.what() << std::endl;
					exit();
				}
			}
			else if (command == "print")
			{
				try {
					print();
				}
				catch (std::exception ex) {
					std::cout << ex.what() << std::endl;
					exit();
				}
			}
			else if (command == "exit")
			{
				exit();
			}
			else {
				std::cout << "Unknown command, type help for available commands." << std::endl;
			}
		}

		std::cout << "> ";
		std::getline(std::cin, command);
		if (command == "")
		{
			std::getline(std::cin, command);
		}
	}
}

//
void Menu::open(std::string command)
{
	isOpen = true;
	std::vector<std::string> params = getParams(command, "open", 1);
	filePath = params[0];

	std::fstream file;

	file.open(filePath, std::ios::in | std::ios::app);
	
	if (!file.is_open())
	{
		throw std::exception("Error in making file");
	}

	if (!(file.peek() == std::ifstream::traits_type::eof()))
	{
		file >> warehouse;
	}
	
	file.close();
}

//
void Menu::close() noexcept
{
	isOpen = false;
	filePath = "";
	Warehouse newWarehouse = Warehouse();
	warehouse = newWarehouse;
	//clean all loaded info
}

//
void Menu::save_as(std::string command)
{
	std::vector<std::string> params = getParams(command, "saveas", 1);

	std::fstream file;

	file.open(params[0], std::ios::out | std::ios::trunc);

	if (!file.is_open())
	{
		throw std::exception("Error in making file");
	}

	file << warehouse;

	file.close();
}

//
void Menu::save()
{
	save_as("saveas " + filePath);
}

//
void Menu::help() noexcept
{
	std::cout << "The following commands are supported : " << std::endl
		<< "open <file>	opens <file>" << std::endl
		<< "close			closes currently opened file" << std::endl
		<< "save			saves the currently open file" << std::endl
		<< "saveas <file>	saves the currently open file in <file>" << std::endl
		<< "help			prints this information" << std::endl
		<< "exit			exists the program" << std::endl
		<< "print           prints out information for the products in the warehouse" << std::endl
		<< "add <name|exparation date|entry date|manifacturer|quantity|measurement unit|comment>	adds a product to the warehouse" << std::endl
		<< "remove <name|quantity>		removes product from warehouse" << std::endl
		<< "log <from|to>	prints logs from date to date" << std::endl
		<< "	supported format: dd/mm/YYYY" << std::endl
		<< "checklosses <product name|price|quantity|from|to>		checks the losses from expiring products" << std::endl
		<< "	supported format: dd/mm/YYYY" << std::endl
		<< "clean			removes all expired products from warehouse" << std::endl;
}

//
void Menu::exit() noexcept
{
	std::cout << "Exiting the program..." << std::endl;
	std::exit(0);
}

//
void Menu::add(std::string command)
{
	//add Milk|28/06/2025|22/06/2025|Pilos|2|Litres|Just milk
	//add Apple|28/06/2025|22/06/2025|Pilos|1|Kilograms|Just an apple
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

//
void Menu::remove(std::string command)
{
	//remove Milk|1
	std::vector<std::string> params = getParams(command, "remove", 2);
	warehouse.remove(params[0], std::stoi(params[1]));
}

//
void Menu::print() noexcept
{
	warehouse.print();
}

void Menu::clean()
{
	warehouse.clean();
}

void Menu::log(std::string command)
{
	std::vector<std::string> params = getParams(command, "log", 2);
	//log 30/05/2025|30/05/2025
	warehouse.log(params[0], params[1]);
}

void Menu::check_losses(std::string command)
{
	//product name|price|quantity|from|to
	//checklosses Milk|2|1|28/05/2025|31/05/2025
	std::vector<std::string> params = getParams(command, "checklosses", 5);
	warehouse.check_losses(params[0], std::stod(params[1]), std::stod(params[2]), params[3], params[4]);
}

//
std::vector<std::string> Menu::getParams(std::string command, std::string operation, int paramCount)
{
	std::vector<std::string> params;
	std::istringstream ss;
	try {
		ss = std::istringstream(command.substr(operation.size() + 1)); // gets the parameters as pure strings, needs to be changed from a constant
	}
	catch (std::exception) {
		throw std::invalid_argument("Invalid command format. Check help for proper format");
	}
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