#include "Warehouse.h"
#include <algorithm>

bool Warehouse::add(Product product)
{
	if (findProduct(product) == product)
	{
		//check if number is full, if it is - add it anew and change the number in the adress, if it isnt - add it to the exact number by using the found product's location variable
	}
	if (sections.size() == sectionAmount)
	{
		return false;
	}
	for (Section section : sections) {
		if (section.add(product))
		{
			return true;
		}
	}
	return false; // warehouse full
}

Product& Warehouse::findProduct(Product p)
{
	Product a;
	std::vector<Product>::iterator it = std::find(productTypes.begin(), productTypes.end(), p);
	if (it != productTypes.end())
	{
		a = *it;
	}
	return a;
}
