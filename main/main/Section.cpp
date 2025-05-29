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
	for (int i = 0; i < shelves.size();i++) {
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

bool Section::isEmpty()
{
	for (Shelf s : shelves)
	{
		if (!s.isEmpty())
		{
			return false;
		}
	}
	return true;
}

Section::~Section() {}
