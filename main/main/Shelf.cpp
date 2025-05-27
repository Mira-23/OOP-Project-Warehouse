#include "Shelf.h"

bool Shelf::add(Product product)
{
	if (numbers.size() == numberAmount)
	{
		return false;
	}
	for (int i = 0; i < numbers.size();i++) {
		if (numbers[i].add(product))
		{
			product[2] = i;
			return true;
		}
	}
	return false; // shelf full
}

std::vector<Number> Shelf::getNumbers()
{
	return numbers;
}
