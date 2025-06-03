#pragma once
#include "Number.h"
#include "StorageUnit.h"
#include <vector>

/// <summary>
/// Medium storage unit - stores numbers
/// </summary>
class Shelf : public StorageUnit
{
public:
	Shelf();
	StorageUnit* clone() override;

	bool add(Product* p) override;
	bool addDirectly(Product* p) override;

	std::vector<Number>& getNumbers();
private:
	const int numberAmount = 10;
	std::vector<Number> numbers;
};

