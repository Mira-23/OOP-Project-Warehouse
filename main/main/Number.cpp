#include "Number.h"

Number::Number() : occupiedSpace(0) {}

bool Number::add(Product* product)
{
	if (products.size() == 0)
	{
		products.push_back(product);
		occupiedSpace += product->getQuantity();
		return true;
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

int Number::findProduct(Product* p)
{
	int i = -1;
	//std::vector<Product*>::iterator it = std::find_if(productList.begin(), productList.end(), [p](Product* prod) -> bool {return *prod == *p; });
	std::vector<Product*>::iterator it = std::find_if(products.begin(), products.end(), [p](Product* prod) -> bool {return *prod == *p; });
	if (it != products.end())
	{
		i = std::distance(products.begin(), it);;
	}
	return i;
}

void Number::removeProduct(Product* p)
{
	products.erase(std::find(products.begin(), products.end(), p));
}

std::vector<Product*> Number::getProducts()
{
	return products;
}

Number::~Number() {}