#include "Menu.h"

/// <summary>
/// default constructor for menu that sets default values for its members
/// </summary>
Menu::Menu() : isOpen(false), filePath(""), warehouse(Warehouse()) {}

/// <summary>
/// main logic for the menu - this is the "user interface" of the program
/// </summary>
void Menu::start()
{
	/// <summary>
	/// it prints out a guiding message to help the user use the menu
	/// </summary>
	std::cout << "Please first open / create file with open <file> " << std::endl;
	std::cout << "After opening, check available commands with \"help\"" << std::endl;

	std::string command;

	while (true)
	{
		/// <summary>
		/// only opens a new file if the current state is closed, and prints a message if that is not the case
		/// you can also exit the program even if nothing is opened
		/// if the state is open, cannot open a new file, and prints a message if that is attempted
		/// the menu handles all supported commands by using the function of the given command
		/// if parameters are wrong the command will stop and a message will be printed
		/// if something went wrong while executing said command (an exception), it will stop the program
		/// if an unsupported comman is written it will prompt the user to write a proper command
		/// </summary>
		
		std::cout << "> ";
		std::getline(std::cin, command);
		if (command == "")
		{
			std::getline(std::cin, command);
		}

		if (!isOpen)
		{
			if (command.substr(0, 4) == "open")
			{
				try {
					open(command);
				}
				catch (std::invalid_argument ex) {
					close();
					std::cout << ex.what() << std::endl;
					continue;
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
			if (command.substr(0, 4) == "open")
			{
				std::cout << "A file is already opened. To open a new file, close the current one." << std::endl;
			}
			else if (command == "close")
			{
				close();
			}
			else if (command == "save")
			{
				try {
					save();
				}
				catch (std::invalid_argument ex) {
					std::cout << ex.what() << std::endl;
					continue;
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
				catch (std::invalid_argument ex) {
					std::cout << ex.what() << std::endl;
					continue;
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
				catch (std::invalid_argument ex) {
					std::cout << ex.what() << std::endl;
					continue;
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
				catch (std::invalid_argument ex) {
					std::cout << ex.what() << std::endl;
					continue;
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
				catch (std::invalid_argument ex) {
					std::cout << ex.what() << std::endl;
					continue;
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
				catch (std::invalid_argument ex) {
					std::cout << ex.what() << std::endl;
					continue;
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
				catch (std::invalid_argument ex) {
					std::cout << ex.what() << std::endl;
					continue;
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
				catch (std::invalid_argument ex) {
					std::cout << ex.what() << std::endl;
					continue;
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
	}
}

/// <summary>
/// reads the warehouse from the given path using its >> operator
/// creates a new file if the given one does not exist
/// throws error if it failed to generate the new file
/// </summary>
/// <param name="command"></param>
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

	std::cout << "Successful file open/create" << std::endl;
}

/// <summary>
/// resets the information stored in the class
/// </summary>
void Menu::close() noexcept
{
	isOpen = false;
	filePath = "";
	Warehouse newWarehouse = Warehouse();
	warehouse = newWarehouse;
	std::cout << "File closed." << std::endl;
}

/// <summary>
/// prints out the warehouse to the given path using its << operator
/// throws error if it failed to generate the new file
/// </summary>
/// <param name="command"></param>
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

	std::cout << "File saved." << std::endl;
}

/// <summary>
/// saves the program to the already opened file using save_as
/// </summary>
void Menu::save()
{
	save_as("saveas " + filePath);
}

/// <summary>
/// prints out all of the supported commands
/// </summary>
void Menu::help() noexcept
{
	std::cout << "The following commands are supported : " << std::endl
		<< "- (supported date format: YYYY-mm-dd)" << std::endl
		<< "- (supported measurementUnits: Litres/Kilograms)" << std::endl
		<< "- (all parameters must be seperated by |)" << std::endl
		<< "open <file>  ->  opens <file>" << std::endl
		<< "close  ->  closes currently opened file" << std::endl
		<< "save  ->  saves the currently open file" << std::endl
		<< "saveas <file>  ->  saves the currently open file in <file>" << std::endl
		<< "help  ->  prints this information" << std::endl
		<< "exit  ->  exists the program" << std::endl
		<< "print  ->  prints out information for the products in the warehouse" << std::endl
		<< "add <name|entry date|exparation date|manifacturer|quantity|measurement unit|comment>  " << std::endl
		<< " -> adds a product to the warehouse" << std::endl
		<< "- an example of the supported format: add Milk|2025-06-22|2025-06-28|Pilos|2|Litres|Just milk" << std::endl
		<< "remove <name|quantity>  ->  removes product from warehouse" << std::endl
		<< "- an example of the supported format: remove Milk|1" << std::endl
		<< "log <from|to>  ->  prints logs from date to date" << std::endl
		<< "- an example of the supported format: log 2025-05-29|2025-05-31" << std::endl
		<< "checklosses <product name|price|quantity|from|to>  ->  checks the losses from expiring products" << std::endl
		<< "- an example of the supported format: checklosses Milk|3|2|2025-05-29|2025-05-31" << std::endl
		<< "clean -> removes all expired products from warehouse" << std::endl;
}

/// <summary>
/// exists the program
/// </summary>
void Menu::exit() noexcept
{
	std::cout << "Exiting the program..." << std::endl;
	std::exit(0);
}

/// <summary>
/// invokes the add function of the warehouse, and prints out whether the product was successfully added or whether the warehouse was full
/// </summary>
/// <param name="command"></param>
void Menu::add(std::string command)
{
	//add Milk|2025-06-22|2025-06-28|Pilos|2|Litres|Just milk
	//add Apple|2025-06-22|2025-06-28|Pilos|1|Kilograms|Just an apple
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

/// <summary>
/// invokes the remove function of the warehouse
/// </summary>
/// <param name="command"></param>
void Menu::remove(std::string command)
{
	//remove Milk|1
	std::vector<std::string> params = getParams(command, "remove", 2);
	warehouse.remove(params[0], std::stoi(params[1]),std::cout);
}

/// <summary>
/// invokes the print function of the warehouse
/// </summary>
void Menu::print() noexcept
{
	warehouse.print(std::cout);
}

/// <summary>
/// invokes the clean function of the warehouse
/// </summary>
void Menu::clean()
{
	warehouse.clean(std::cout);
}

/// <summary>
/// invokes the log function of the warehouse
/// </summary>
/// <param name="command"></param>
void Menu::log(std::string command)
{
	std::vector<std::string> params = getParams(command, "log", 2);
	//log 2025-05-29|2025-05-31
	warehouse.log(params[0], params[1], std::cout);
}

/// <summary>
/// invokes the check_losses function of the warehouse
/// </summary>
/// <param name="command"></param>
void Menu::check_losses(std::string command)
{
	//product name|price|quantity|from|to
	//checklosses Milk|2|1|2025-05-29|2025-05-31
	std::vector<std::string> params = getParams(command, "checklosses", 5);
	warehouse.check_losses(params[0], std::stod(params[1]), std::stod(params[2]), params[3], params[4], std::cout);
}

/// <summary>
/// a helper function to convert a given line into parameters for the desired command
/// done with the help of stringstream
/// </summary>
/// <param name="command"></param>
/// <param name="operation"></param>
/// <param name="paramCount"></param>
/// <returns></returns>
std::vector<std::string> Menu::getParams(std::string command, std::string operation, int paramCount)
{
	std::vector<std::string> params;
	std::istringstream ss(command);
	std::string t;
	try {
		std::getline(ss, t, ' '); // gets the parameters as pure strings
	}
	catch (std::exception) {
		throw std::invalid_argument("Invalid command format. Check help for proper format");
	}
	
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