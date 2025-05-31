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
	for (int i = 0; i < numberAmount;i++) {
		(*product).setNumberId(i);
		if (numbers[i].add(product))
		{
			return true;
		}
	}
	return false; // shelf full
}

bool Shelf::addDirectly(Product* product)
{
	if (numbers[product->getNumberId()].addDirectly(product))
	{
		return true;
	}
	return false; // shelf full
}

std::vector<Number> Shelf::getNumbers()
{
	return numbers;
}

Shelf::~Shelf() {}