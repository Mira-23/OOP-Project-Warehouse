#pragma once
#include "IStorageUnit.h"
#include <vector>

//Smallest storage unit - direct storage of products
class Number : public IStorageUnit
{
public:
	Number();
	//Number(const Number& other);
	//Number& operator=(Number& other);
	bool add(Product* p) override;
	void removeProduct(Product* p);
	std::vector<Product*> getProducts();
	//int findProduct(Product* p);
	bool isEmpty();
	//~Number() override;
private:
	void swap(Number& other);
	std::vector<Product*> products;
	double occupiedSpace;
	const double capacity = 100;
};

