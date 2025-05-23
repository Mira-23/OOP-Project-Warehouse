#pragma once
#include "Product.h"
#include <vector>
class Shelf
{
public:
	Shelf(int id);
	int getId();
private:
	int id;
	const double storageSpace = 100.0;
	double currentSpace;
	std::vector<Product> products;
};

