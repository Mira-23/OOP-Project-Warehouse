#include "Section.h"

bool Section::add(Product product)
{
	if (shelves.size() == shelfAmount)
	{
		return false;
	}
	for (int i = 0; i < shelves.size();i++) {
		if (shelves[i].add(product))
		{
			product[1] = i;
			return true;
		}
	}
	return false; // section full
}

std::vector<Shelf> Section::getShelves()
{
	return shelves;
}
