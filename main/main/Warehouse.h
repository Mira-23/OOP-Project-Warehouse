#pragma once
#include "Section.h"
#include "IStorageUnit.h"
#include <vector>

//Main logic - holds the operations of the storage system
class Warehouse : public IStorageUnit
{
public:
	Warehouse(Warehouse& other);
	Warehouse& operator=(Warehouse& other);
	void print() const;
	bool add(Product p);
	void remove(std::string name, double quantity);
	void log() const;
	void clean();
	~Warehouse();
private:
	const int sectionAmount = 10;
	std::vector<Section> sections;
	std::vector<Product*> productList;
	void swap(Warehouse& other);
	int findProduct(Product p);
};

