#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Warehouse.h"
#include "Product.h"

class Menu
{
public:
	Menu();
	void start();
private:
	void add(std::string command);
	void remove(std::string command);
	void print();
	void clean();
	void log(std::string command);
	

	void open(std::string command);
	void close();
	void save_as(std::string command);
	void save();
	void help();
	void exit();

	std::vector<std::string> getParams(std::string command, std::string operation, int paramCount);

	bool isOpen;
	std::string filePath;
	Warehouse warehouse;
};

