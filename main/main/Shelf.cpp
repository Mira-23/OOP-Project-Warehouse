#include "Shelf.h"

bool Shelf::add(Product product)
{
	if (numbers.size() == numberAmount)
	{
		return false;
	}
	for (Number number : numbers) {
		if (number.add(product))
		{
			return true;
		}
	}
	return false; // shelf full
}