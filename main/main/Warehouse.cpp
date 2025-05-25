#include "Warehouse.h"

bool Warehouse::add(Product product)
{
	if (findProduct(product) == product)
	{
		//check if number is full, if it isnt - add it to the exact number by using the found product's location variable
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
	//introduce a layer by layer findProduct function the same way as add
	return a;
}
