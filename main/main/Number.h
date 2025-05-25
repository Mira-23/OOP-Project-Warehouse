#pragma once
#include "IStorageUnit.h"
#include <vector>
#include <cstring>

//Smallest storage unit - direct storage of products
class Number : public IStorageUnit
{
public:
	//bool isFull() const override;
	bool add(Product p) override;
private:
	std::vector<Product> products;
	double occupiedSpace;
	const double capacity = 100;
};

