#pragma once
#include "IStorageUnit.h"
#include <vector>

//Smallest storage unit - direct storage of products
class Number : public IStorageUnit
{
public:
	Number();
	IStorageUnit* clone() override;

	bool add(Product* p) override;
	bool addDirectly(Product* p) override;

	void removeProduct(Product* p);

	std::vector<Product*> getProducts();
private:
	void swap(Number& other);

	std::vector<Product*> products;
	double occupiedSpace;
	const double capacity = 100;
};

