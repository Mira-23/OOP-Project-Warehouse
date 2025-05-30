#include "Number.h"

Number::Number() : occupiedSpace(0) {}

//Number::Number(const Number& other) : occupiedSpace(other.occupiedSpace)
//{
//	for (Product* p : other.products)
//	{
//		products.push_back(new Product(*p));
//	}
//}
//
//Number& Number::operator=(Number& other)
//{
//	Number copy(other);
//	swap(copy);
//
//	return *this;
//}

bool Number::add(Product* product)
{
	if (isEmpty())
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

//int Number::findProduct(Product* p)
//{
//	int i = -1;
//	std::vector<Product*>::iterator it = std::find_if(products.begin(), products.end(), [p](Product* prod) -> bool {return *prod == *p; });
//	if (it != products.end())
//	{
//		i = std::distance(products.begin(), it);;
//	}
//	return i;
//}

void Number::removeProduct(Product* p)
{
	bool a = *products[0] == *p;
	std::cout << std::boolalpha << a;
	products.erase(std::find_if(products.begin(), products.end(), [p](Product* prod) -> bool {return *prod == *p; }));
}

std::vector<Product*> Number::getProducts()
{
	return products;
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

//Number::~Number()
//{
//	for (Product* p : products)
//	{
//		delete p;
//	}
//}