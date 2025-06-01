#include "Shelf.h"

/// <summary>
/// Shelf constructor, fills the shelf with a set amount of numbers
/// /// since the assignment does not mention how much there should be of each, i have decided to add 10 numbers
/// </summary>
Shelf::Shelf()
{
	for (int i = 0; i < numberAmount; i++)
	{
		numbers.push_back(Number());
	}
}

/// <summary>
/// clone function so that the interface can be used correctly
/// </summary>
/// <returns></returns>
IStorageUnit* Shelf::clone()
{
	return new Shelf(*this);
}

/// <summary>
/// add function that automatically adds a product to the shelf unless it's full
/// </summary>
/// <param name="product"></param>
/// <returns></returns>
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

/// <summary>
/// add function that adds a product to the shelf depending on the products location, unless it's full
/// </summary>
/// <param name="product"></param>
/// <returns></returns>
bool Shelf::addDirectly(Product* product)
{
	if (numbers[product->getNumberId()].addDirectly(product))
	{
		return true;
	}
	return false; // shelf full
}

/// <summary>
/// getter for the products of the shelf
/// </summary>
/// <returns></returns>
std::vector<Number> Shelf::getNumbers()
{
	return numbers;
}