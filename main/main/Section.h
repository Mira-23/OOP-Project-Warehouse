#pragma once
#include "Shelf.h"
#include "StorageUnit.h"
#include <vector>

/// <summary>
/// Biggest storage unit - contains shelves
/// </summary>
class Section : public StorageUnit
{
public:
	Section();
	StorageUnit* clone() override;

	bool add(Product* p) override;
	bool addDirectly(Product* p) override;

	std::vector<Shelf> getShelves();
private:
	std::vector<Shelf> shelves;
	const int shelfAmount = 10;
};

