#include <iostream>
#include "Menu.hpp"

/// <summary>
/// Only serves as a way to start the program by using the start method of the class Menu
/// </summary>
/// <returns></returns>
int main()
{
	Menu<std::ostream> menu;
	menu.start(std::cout);
}