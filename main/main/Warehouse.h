#pragma once
#include "Section.h"
#include "IStorageUnit.h"
#include <vector>

//Main logic - holds the operations of the storage system
class Warehouse : public IStorageUnit
{
public:
	Warehouse();
	Warehouse(const Warehouse& other);
	Warehouse& operator=(Warehouse& other);
	void print();
	bool add(Product* p) override;
	bool isEmpty() override;
	void remove(std::string name, double quantity);
	void log() const;
	void clean();

	bool addDirectly(Product* p);

	friend std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse);
	friend std::istream& operator>>(std::istream& is, Warehouse& warehouse);

	void printProductList(std::ostream& os) const;


	~Warehouse() override;
private:
	const int sectionAmount = 1;
	std::vector<Section> sections;
	std::vector<Product*> productList;

	void printLine(std::string name, std::string manufacturer, std::string measurementUnit, double quantity);
	void swap(Warehouse& other);
	int findProduct(Product* p);
};
