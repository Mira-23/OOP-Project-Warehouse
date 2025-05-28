#pragma once
#include "Number.h"
#include "IStorageUnit.h"
#include <vector>

//Medium storage unit - stores numbers
class Shelf : public IStorageUnit
{
public:
	Shelf();
	bool add(Product& p) override;
	std::vector<Number> getNumbers();
	~Shelf();
private:
	const int numberAmount = 10;
	std::vector<Number> numbers;
};

