#pragma once
#include "Shelf.h"
#include "IStorageUnit.h"
#include <vector>

//Biggest storage unit - contains shelves
class Section : public IStorageUnit
{
public:
	Section();
	bool add(Product* p) override;
	std::vector<Shelf> getShelves();
	bool isEmpty() override;
	~Section() override;
private:
	std::vector<Shelf> shelves;
	const int shelfAmount = 1;
};

