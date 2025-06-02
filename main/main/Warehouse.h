#pragma once
#include "Section.h"
#include "StorageUnit.h"
#include "ChangeLog.h"
#include <vector>

/// <summary>
/// Main logic - holds the operations of the storage system (add, print, remove, log, clean, check losses and etc.)
/// </summary>
class Warehouse : public StorageUnit
{
public:
	Warehouse();
	StorageUnit* clone() override;
	Warehouse(const Warehouse& other);
	Warehouse& operator=(Warehouse& other);

	void print(std::ostream& os);
	bool add(Product* p) override;
	void remove(std::string name, double quantity);
	void log(std::string from, std::string to) const;
	void clean();
	void check_losses(std::string name, double price, double quantity, std::string from, std::string to);

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

	void swap(Warehouse& other);
	int findProduct(Product* p);
};
