#pragma once
#include "Section.h"
#include "IStorageUnit.h"
#include "ChangeLog.h"
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
	void remove(std::string name, double quantity);
	void log(std::string from, std::string to) const;
	void clean();

	bool addDirectly(Product* p) override;

	friend std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse);
	friend std::istream& operator>>(std::istream& is, Warehouse& warehouse);

	void printProductList(std::ostream& os) const;

	~Warehouse() override;
private:
	const int sectionAmount = 10;
	std::vector<Section> sections;
	std::vector<Product*> productList;
	 ChangeLog changelog;

	void printLine(std::string name, std::string manufacturer, std::string measurementUnit, double quantity);
	void swap(Warehouse& other);
	int findProduct(Product* p);
};
