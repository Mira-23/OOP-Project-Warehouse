#pragma once
#include "Shelf.h"
#include "IStorageUnit.h"
#include <vector>

//Biggest storage unit - contains shelves
class Section : public IStorageUnit
{
public:
	Section();
	IStorageUnit* clone() override;
	bool add(Product* p) override;
	bool addDirectly(Product* p) override;
	std::vector<Shelf> getShelves();
private:
	std::vector<Shelf> shelves;
	const int shelfAmount = 10;
};

