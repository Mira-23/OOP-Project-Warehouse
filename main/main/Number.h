#pragma once
#include "IStorageUnit.h"
#include <vector>

//Smallest storage unit - direct storage of products
class Number : public IStorageUnit
{
public:
	Number();
	IStorageUnit* clone() override;
	//Number(const Number& other);
	//Number& operator=(Number& other);
	bool add(Product* p) override;
	void removeProduct(Product* p);
	std::vector<Product*> getProducts();
	bool addDirectly(Product* p) override;
	//int findProduct(Product* p);
	bool isEmpty();
private:
	void swap(Number& other);
	std::vector<Product*> products;
	double occupiedSpace;
	const double capacity = 100;
};

