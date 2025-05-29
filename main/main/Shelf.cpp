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
		bool wasNumberEmpty = numbers[i].isEmpty();
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

bool Shelf::isEmpty()
{
	for (Number n : numbers)
	{
		if (!n.isEmpty())
		{
			return false;
		}
	}
	return true;
}

Shelf::~Shelf() {}