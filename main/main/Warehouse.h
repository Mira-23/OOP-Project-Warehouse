#pragma once
#include "Section.h"
#include "IStorageUnit.h"
#include <vector>

//Main logic - holds the operations of the storage system
class Warehouse : public IStorageUnit
{
public:
	void print() const;
	bool add(Product p);
	void remove();
	void log() const;
	void clean();
private:
	std::vector<Section> sections;
	const int sectionAmount = 10;
	std::vector<Product> productTypes;
	Product& findProduct(Product p);
};

