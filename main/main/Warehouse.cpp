#include "Warehouse.h"
#include <algorithm>
#include <sstream>
#include <functional>

Warehouse::Warehouse() : changelog(ChangeLog())
{
	for (int i = 0; i < sectionAmount; i++)
	{
		sections.push_back(Section());
	}
}

Warehouse::Warehouse(const Warehouse& other) : sections(other.sections)
{
	for (Product* p : other.productList)
	{
		productList.push_back(new Product(*p));
	}
}

Warehouse& Warehouse::operator=(Warehouse& other)
{
	Warehouse copy(other);
	swap(copy);

	return *this;
}

void Warehouse::printLine(std::string name, std::string manufacturer, std::string measurementUnit, double quantity)
{
	std::cout << name << " " << manufacturer << " " << measurementUnit << " " << quantity << " " << std::endl;
}

void Warehouse::print()
{
	if (productList.size() == 0) { return; }

	std::string tempName = productList[0]->getName();
	double tempQuantity = productList[0]->getQuantity();

	//turn into a print function
	if (productList.size() == 1) {
		printLine(tempName, productList[0]->getManufacturer(), productList[0]->stringMeasurementUnit(), tempQuantity);
		return;
	}
	//turn into sort function
	std::sort(productList.begin(), productList.end(), [](Product* first, Product* other) {
		return *first < *other;
		});
	// name|manufacturer|measurementUnit|quantity
	
	for (int i =1;i<productList.size();i++)
	{
		if (tempName == productList[i]->getName())
		{
			tempQuantity += productList[0]->getQuantity();
		}
		else {
			printLine(tempName, productList[i-1]->getManufacturer(), productList[i-1]->stringMeasurementUnit(), tempQuantity);
			tempName = productList[i]->getName();
			tempQuantity = productList[i]->getQuantity();
		}
	}
	printLine(tempName, productList[productList.size()-1]->getManufacturer(), productList[productList.size() - 1]->stringMeasurementUnit(), tempQuantity);
}

bool Warehouse::add(Product* product)
{
	//if product is already in database, add it to the number unless it is full
	int productIndex = findProduct(product);
	if (productIndex >= 0 && (*productList[productIndex]) == *product)
	{
		return addDirectly(productList[productIndex]);
	}

	for (int i = 0; i < sections.size(); i++) {

		Product* newProduct = new Product(*product);
		(*newProduct).setSectionId(i);
		if (sections[i].add(newProduct))
		{
			productList.push_back(newProduct);
			changelog.submitChange("add", newProduct->productToString());
			return true;
		}
	}
	return false; // warehouse full
}

//is there an opposite of noexcept for a function? this needs it
void Warehouse::remove(std::string name, double quantity)
{
	//sorts the list so that the latest come up to the top, which is for the next code to iterate over it properly
	std::sort(productList.begin(), productList.end(), [](Product* first, Product* other) {
		return *first < *other;
		});

	//finds the index of the first product of the type that it's going to remove from
	int i = 0;
	while ((*productList[i]).getName() != name && i != productList.size()) { i++; }
	if (i == productList.size())
	{
		std::cout << "Product does not exist in warehouse." << std::endl;
		return;
	}

	//checks whether the total quantity of all the products that are removed is less than the amount requested
	double totalQuantity = 0;
	while (i != productList.size() && (productList[i]->getName() == name))
	{
		totalQuantity += productList[i]->getQuantity();
		i++;
	}

	if (totalQuantity < quantity)
	{
		std::cout << "Amount needed is more than total - withdraw all anyway? (Y/N)" << std::endl;
		std::string answer;
		std::cin >> answer;
		if (answer == "N")
		{
			return;
		}
	}

	//makes a vector for the indexes of the removed product types (from warehouse) so that they can be removed from the vector later
	std::vector<int> removedProducts;
	double sum = 0;
	i--;
	//if the quantity is more than one product holds - remove the soonest expiring one and continue removing until the quantity is full
	//if it isnt, directly removes the needed quantity from the first product
	//this continues until either the end or the product type changes
	while (i != productList.size() && ((*productList[i]).getName() == name && sum != quantity))
	{
		if (sum + productList[i]->getQuantity() <= quantity)
		{
			sum += productList[i]->getQuantity();

			int sectionId = productList[i]->getSectionId();
			int shelfId = productList[i]->getShelfId();
			int numberId = productList[i]->getNumberId();
			sections[sectionId].getShelves()[shelfId].getNumbers()[numberId].removeProduct(productList[i]);
			removedProducts.push_back(i);

			quantity -= sum;
			std::cout << "Product removed due to qunatity" << std::endl;
		}
		else {
			productList[i]->reduceQuantityBy(quantity);
			changelog.submitChange("change", productList[i]->productToString(),quantity);
		}
		i++;
	}

	//removes the removed products from the warehouse vector
	for (int j : removedProducts)
	{
		std::cout << "Product removed" << std::endl;
		changelog.submitChange("remove", productList[j]->productToString());
		delete productList[j];
		productList.erase(productList.begin() + j);
	}
}

void Warehouse::log(std::string from, std::string to) const
{
	changelog.printLog(from,to);
}

void Warehouse::clean()
{
	//goes through the list and removes expiring products
	std::vector<std::vector<Product*>::iterator> its;
	for (std::vector<Product*>::iterator it = productList.begin(); it != productList.end();)
	{
		if ((*it)->closeToExpiration())
		{
			int sectionId = (*it)->getSectionId();
			int shelfId = (*it)->getShelfId();
			int numberId = (*it)->getNumberId();
			sections[sectionId].getShelves()[shelfId].getNumbers()[numberId].removeProduct((*it));
			its.push_back(it);
		}
	}

	//this is done so that i can directly pass the iterator to the erase function, even if it doesn't look as good
	for (std::vector<Product*>::iterator it : its)
	{
		productList.erase(it);
		changelog.submitChange("clean", (*it)->productToString());
		delete *it;
	}
}

bool Warehouse::addDirectly(Product* p)
{
	Product* newProduct = new Product(*p);
	productList.push_back(newProduct);
	int sectionId = p->getSectionId();
	int shelfId = p->getShelfId();
	int numberId = p->getNumberId();
	Number num = sections[sectionId].getShelves()[shelfId].getNumbers()[numberId];
	(*p).setSectionId(sectionId);
	(*p).setShelfId(shelfId);
	(*p).setNumberId(numberId);
	return num.add(newProduct);
}

void Warehouse::swap(Warehouse& other)
{
	using std::swap;
	swap(sections, other.sections);
	swap(productList, other.productList);
}

//returns the index of the product if found, if not returns -1
//this is achieved by using find and a lambda which turns the pointers to products who have a defined == operator
int Warehouse::findProduct(Product* p)
{
	int i = -1;
	std::vector<Product*>::iterator it =
		std::find_if(productList.begin(), productList.end(), [p](Product* prod) -> bool {return *prod == *p; });
	if (it != productList.end())
	{
		i = std::distance(productList.begin(), it);;
	}
	return i;
}

void Warehouse::printProductList(std::ostream& os) const
{
	for (Product* p : productList)
	{
		os << *p;
	}
}

Warehouse::~Warehouse()
{
	for (Product* p : productList)
	{
		delete p;
	}
	std::cout << "This ran" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse)
{
	warehouse.printProductList(os);
	return os;
}

std::istream& operator>>(std::istream& is, Warehouse& warehouse)
{
	while (!is.eof())
	{
		Product p;
		is >> p;
		warehouse.addDirectly(&p);
	}
	return is;
}
