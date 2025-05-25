#pragma once
#include "Number.h"
#include "IStorageUnit.h"
#include <vector>

//Medium storage unit - stores numbers
class Shelf : public IStorageUnit
{
public:
	bool add(Product p) override;
private:
	const int numberAmount = 10;
	std::vector<Number> numbers;
};

