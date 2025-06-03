#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Warehouse.h"
#include "Product.h"

/// <summary>
/// A class that handles the interactive logic of the program
/// </summary>
//template <typename T>
class Menu
{
public:
	Menu();
	void start();
private:
	void add(std::string command);
	void remove(std::string command);
	void print() noexcept;
	void clean();
	void log(std::string command);
	void check_losses(std::string command);

	void open(std::string command);
	void close() noexcept;
	void save_as(std::string command);
	void save();
	void help() noexcept;
	void exit() noexcept;

	std::vector<std::string> getParams(std::string command, std::string operation, int paramCount);

	bool isOpen;
	std::string filePath;
	Warehouse warehouse;
};

