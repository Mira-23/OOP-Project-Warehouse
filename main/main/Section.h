#pragma once
#include "Shelf.h"
#include <vector>

//Biggest storage unit - contains shelves
class Section
{
public:
	bool isFull();
private:
	std::vector <Shelf> shelves;
	const int shelfAmount = 50;
};

