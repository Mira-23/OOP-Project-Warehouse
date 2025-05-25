#pragma once
#include "Number.h"
#include <vector>

//Medium storage unit - stores numbers
class Shelf
{
public:
	bool isFull();
private:
	const int numberAmount = 10;
	std::vector<Number> numbers;
};

