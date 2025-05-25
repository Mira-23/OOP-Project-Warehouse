#pragma once
#include "Product.h"
#include <vector>
#include <cstring>

//Smallest storage unit - direct storage of products
class Number
{
public:
	bool isFull();
private:
	std::vector<Product> products;
	std::string heldProduct;
	const double capacity = 100;
};

