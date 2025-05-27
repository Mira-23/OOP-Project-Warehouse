#include "Product.h"

Product::Product(std::string name,
	std::time_t expirationDate,
	std::time_t enterDate,
	std::string manifacturer,
	MeasurementUnit measurementUnit,
	double quantity,
	int shelfId,
	std::string comment)
{
	//implement
}

double Product::getQuantity() const
{
	return quantity;
}

void Product::reduceQuantityBy(double amount)
{
	quantity -= amount;
}

std::string Product::getName() const
{
	return name;
}

int& Product::operator[](int i)
{
	//deal with this!!!
	if (i < 0 || i > 2)
	{
		throw std::exception("Index out of bounds");
	}
    return location[i];
}

bool Product::operator==(const Product& other)
{
    return (name == other.name) &&
		(enterDate == other.enterDate) &&
		(manifacturer == other.manifacturer) &&
		(location[0] == other.location[0]) &&
		(location[1] == other.location[1]) &&
		(location[2] == other.location[2]) &&
		(measurementUnit == other.measurementUnit) &&
		(quantity == other.quantity);
}

bool Product::operator!=(const Product& other)
{
	return !(*this == other);
}

//this lets functions sort by name -> exp date -> quantity
bool Product::operator<(Product& other)
{
	if (name != other.name)
	{
		return name < other.name;
	}	
	if (expirationDate != other.expirationDate)
	{
		return expirationDate < other.expirationDate;
	}
	return quantity < other.quantity;
}
