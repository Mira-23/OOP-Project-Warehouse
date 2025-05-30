#include "Section.h"

Section::Section()
{
	for (int i = 0; i < shelfAmount; i++)
	{
		shelves.push_back(Shelf());
	}
}

bool Section::add(Product* product)
{
	for (int i = 0; i < shelfAmount;i++) {
		(*product).setShelfId(i);
		if (shelves[i].add(product))
		{
			return true;
		}
	}
	return false; // section full
}

std::vector<Shelf> Section::getShelves()
{
	return shelves;
}

Section::~Section() {}
