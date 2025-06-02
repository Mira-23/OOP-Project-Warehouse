#include "Number.h"

Number::Number() : occupiedSpace(0) {}

/// <summary>
/// clone function so that the interface can be used correctly
/// </summary>
/// <returns></returns>
StorageUnit* Number::clone()
{
	return new Number(*this);
}

/// <summary>
/// add function that automatically adds a product to the shelf unless it's full
/// this also accounts for whether the current number is occupied by the same/different product
/// </summary>
/// <param name="product"></param>
/// <returns></returns>
bool Number::add(Product* product)
{
	if (products.size() == 0)
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

/// <summary>
/// removes a product from the number
/// </summary>
/// <param name="p"></param>
void Number::removeProduct(Product* p)
{
	std::vector<Product*>::iterator it = std::find_if(products.begin(), products.end(), [p](Product* prod) -> bool {return *prod == *p; });
	if (it == products.end())
	{
		std::cout << "Product does not exist" << std::endl;
		return;
	}
	products.erase(it);
}

/// <summary>
/// getter for the products in the number
/// </summary>
/// <returns></returns>
std::vector<Product*> Number::getProducts()
{
	return products;
}

/// <summary>
/// add function that adds a product to the number depending on the products location, unless it's full
/// </summary>
/// <param name="product"></param>
/// <returns></returns>
bool Number::addDirectly(Product* product)
{
	products.push_back(product);
	occupiedSpace += product->getQuantity();
	return true;
}