#include "Shelf.h"

Shelf::Shelf()
{
	for (int i = 0; i < numberAmount; i++)
	{
		numbers.push_back(Number());
	}
}

bool Shelf::add(Product* product)
{
	for (int i = 0; i < numbers.size();i++) {
		(*product).setNumberId(i);
		if (numbers[i].add(product))
		{
			return true;
		}
	}
	return false; // shelf full
}

std::vector<Number> Shelf::getNumbers()
{
	return numbers;
}

Shelf::~Shelf() {}