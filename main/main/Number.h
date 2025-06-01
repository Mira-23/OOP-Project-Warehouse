#pragma once
#include "IStorageUnit.h"
#include <vector>

/// <summary>
/// Smallest storage unit - direct storage of products
/// </summary>
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
	std::vector<Product*> products;
	double occupiedSpace;
	const double capacity = 100;
};

