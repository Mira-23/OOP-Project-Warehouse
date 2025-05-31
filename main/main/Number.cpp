#include "Number.h"

Number::Number() : occupiedSpace(0) {}

IStorageUnit* Number::clone()
{
	return new Number(*this);
}

bool Number::add(Product* product)
{
	if (isEmpty())
	{
		return addDirectly(product);
	}
	else if (product != products[0])
	{
		return false; // number occupied by different product
	}
	else if (product->getQuantity() + occupiedSpace <= capacity)
	{
		products.push_back(product);
		occupiedSpace += product->getQuantity();
		return true;
	}
	else {
		return false; // number full
	}
}

void Number::removeProduct(Product* p)
{
	products.erase(std::find_if(products.begin(), products.end(), [p](Product* prod) -> bool {return *prod == *p; }));
}

std::vector<Product*> Number::getProducts()
{
	return products;
}

bool Number::addDirectly(Product* product)
{
	products.push_back(product);
	occupiedSpace += product->getQuantity();
	return true;
}

void Number::swap(Number& other)
{
	using std::swap;
	swap(products, other.products);
	swap(occupiedSpace, other.occupiedSpace);
}

bool Number::isEmpty()
{
	return products.size()==0;
}