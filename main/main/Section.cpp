#include "Section.h"

/// <summary>
/// Section constructor, fills the shelf with a set amount of shelves
/// /// since the assignment does not mention how much there should be of each, i have decided to add 10 shelves
/// </summary>
Section::Section()
{
	for (int i = 0; i < shelfAmount; i++)
	{
		shelves.push_back(Shelf());
	}
}

/// <summary>
/// clone function so that the interface can be used correctly
/// </summary>
/// <returns></returns>
StorageUnit* Section::clone()
{
	return new Section(*this);
}

/// <summary>
/// add function that automatically adds a product to the section unless it's full
/// </summary>
/// <param name="product"></param>
/// <returns></returns>
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

/// <summary>
/// add function that adds a product to the section depending on the products location, unless it's full
/// </summary>
/// <param name="product"></param>
/// <returns></returns>
bool Section::addDirectly(Product* product)
{
	if (shelves[product->getShelfId()].addDirectly(product))
	{
		return true;
	}
	return false; // shelf full
}

/// <summary>
/// getter for the shelves of the section
/// </summary>
/// <returns></returns>
std::vector<Shelf>& Section::getShelves()
{
	return shelves;
}
