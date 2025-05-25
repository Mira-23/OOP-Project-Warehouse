#pragma once
#include "Section.h"
#include "Product.h"
#include <vector>

//Main logic - holds the operations of the storage system
class Warehouse
{
public:
	void print() const;
	//change to raw values rather than object
	void add(Product p);
	void remove();
	void log() const;
	void clean();
private:
	std::vector<Section> sections;
	const int sectionAmount = 10;
	Product findProduct(Product p);
};

