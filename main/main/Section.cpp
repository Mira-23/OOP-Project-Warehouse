#include "Section.h"

bool Section::add(Product product)
{
	if (shelves.size() == shelfAmount)
	{
		return false;
	}
	for (Shelf shelf : shelves) {
		if (shelf.add(product))
		{
			return true;
		}
	}
	return false; // section full
}