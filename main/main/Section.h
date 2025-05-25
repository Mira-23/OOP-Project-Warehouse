#pragma once
#include "Shelf.h"
#include "IStorageUnit.h"
#include <vector>

//Biggest storage unit - contains shelves
class Section : public IStorageUnit
{
public:
	bool add(Product p) override;
private:
	std::vector<Shelf> shelves;
	const int shelfAmount = 50;
};

