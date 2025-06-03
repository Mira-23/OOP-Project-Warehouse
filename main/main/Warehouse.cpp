#include "Warehouse.h"
#include <algorithm>
#include <sstream>
#include <functional>

/// <summary>
/// Warehouse constructor, fills the warehouse with a set amount of sections, and initializes the changelog object
/// since the assignment does not mention how much there should be of each, i have decided to add 10 sections
/// </summary>
Warehouse::Warehouse() : changelog(ChangeLog())
{
	for (int i = 0; i < sectionAmount; i++)
	{
		sections.push_back(Section());
	}
}

/// <summary>
/// clone function so that the interface can be used correctly
/// </summary>
/// <returns></returns>
StorageUnit* Warehouse::clone()
{
	return new Warehouse(*this);
}

/// <summary>
/// Copy constructor for proper management of the product pointers
/// </summary>
/// <param name="other"></param>
Warehouse::Warehouse(const Warehouse& other) : sections(other.sections)
{
	for (Product* p : other.productList)
	{
		productList.push_back(new Product(*p));
	}
}

/// <summary>
/// operator= for proper management of the product pointers
/// made by utilizing the copy and swap method
/// </summary>
/// <param name="other"></param>
Warehouse& Warehouse::operator=(Warehouse& other)
{
	Warehouse copy(other);
	swap(copy);

	return *this;
}

/// <summary>
/// prints the entire product list, and then prints out every type of product with how much quantity of it is available
/// </summary>
void Warehouse::print(std::ostream& os)
{
	if (productList.size() == 0) { return; }

	for (Product* p : productList)
	{
		os << p->productAsMessage() << std::endl;
	}

	std::string tempName = productList[0]->getName();
	double tempQuantity = productList[0]->getQuantity();
	std::string measurementUn = productList[0]->stringMeasurementUnit();

	if (productList.size() == 1) {
		os << tempName << ": " << tempQuantity << " " << measurementUn << std::endl;
		return;
	}

	std::sort(productList.begin(), productList.end(), [](Product* first, Product* other) {
		return *first < *other;
		});
	// name|measurementUnit|quantity
	
	for (int i =1;i<productList.size();i++)
	{
		measurementUn = productList[i]->stringMeasurementUnit();
		if (tempName == productList[i]->getName())
		{
			tempQuantity += productList[i]->getQuantity();
		}
		else {
			std::cout << tempName << " " << tempQuantity << " " << measurementUn << std::endl;
			tempName = productList[i]->getName();
			tempQuantity = productList[i]->getQuantity();
		}
	}
	std::cout << tempName << ": " << tempQuantity << " " << measurementUn << std::endl;
}

/// <summary>
/// add function that automatically adds a product to the warehouse unless it's full
/// logs the addition to the changelog
/// </summary>
/// <param name="product"></param>
/// <returns></returns>
bool Warehouse::add(Product* product)
{
	//if product is already in database, add it to the number unless it is full
	int productIndex = findProduct(product);
	if (productIndex >= 0 && (*productList[productIndex]) == *product)
	{
		changelog.submitChange("add", productList[productIndex]->productAsMessage());
		return addDirectly(productList[productIndex]);
	}

	for (int i = 0; i < sectionAmount; i++) {

		Product* newProduct = new Product(*product);
		(*newProduct).setSectionId(i);
		if (sections[i].add(newProduct))
		{
			productList.push_back(newProduct);
			changelog.submitChange("add", newProduct->productAsMessage());
			return true;
		}
	}
	return false; // warehouse full
}

/// <summary>
/// sorts the product list (so that the product that is expiring the soonest comes up first), finds the 
/// logs the change/removal of a quantity/product in the changelog
/// </summary>
/// <param name="name"></param>
/// <param name="quantity"></param>
void Warehouse::remove(std::string name, double quantity, std::ostream& os)
{
	/// <summary>
	/// sorts the list so that the latest come up to the top, which is for the next code to iterate over it properly
	/// </summary>
	std::sort(productList.begin(), productList.end(), [](Product* first, Product* other) {
		return *first < *other;
		});

	/// <summary>
	/// finds the placement of the first product of the type that it's going to remove from
	/// </summary>
	std::vector<Product*>::iterator it = std::find_if(productList.begin(), productList.end(), [name](Product* p)
		{
			return p->getName() == name;
		});
	if (it == productList.end())
	{
		os << "Product does not exist in warehouse." << std::endl;
		return;
	}

	/// <summary>
	/// checks whether the total quantity of all the products that are removed is less than the amount requested
	/// </summary>
	double totalQuantity = 0;
	std::vector<Product*>::iterator jt = it;
	while (jt != productList.end() && ((*it)->getName() == name))
	{
		totalQuantity += (*jt)->getQuantity();
		jt++;
	}

	/// <summary>
	/// if the total quantity of all the products that are removed is less than the amount requested prompts the user whether they still want to extract everyting
	/// </summary>
	if (totalQuantity < quantity)
	{
		std::cout << "> Amount needed is more than total - withdraw all anyway? (Y/N)" << std::endl;
		std::cout << "> ";
		std::string answer;
		std::cin >> answer;

		if (answer == "N")
		{
			return;
		}
		else {
			quantity = totalQuantity;
		}
	}

	/// <summary>
	/// makes a vector for the placements of the removed product types (from warehouse) so that they can be removed from the vector later
	/// </summary>
	double sum = 0;

	/// <summary>
	//if the quantity is more than one product holds - remove the soonest expiring one and continue removing until the quantity is full
	//if it isnt, directly removes the needed quantity from the first product
	//this continues until either the end or the product type changes
	/// </summary>
	while (it != productList.end() && ((*it)->getName() == name && sum != quantity))
	{
		if (sum + (*it)->getQuantity() <= quantity)
		{
			sum += (*it)->getQuantity();

			int sectionId = (*it)->getSectionId();
			int shelfId = (*it)->getShelfId();
			int numberId = (*it)->getNumberId();
			try {
				sections[sectionId].getShelves()[shelfId].getNumbers()[numberId].removeProduct((*it));
			}
			catch (...)
			{
				os << "Product could not be erased";
				return;
			}
			os << "A batch of product " << (*it)->getName() << " was removed" << std::endl;
			changelog.submitChange("remove", (*it)->getName());
			delete (*it);
			it = productList.erase(it);
		}
		else {
			(*it)->reduceQuantityBy(quantity-sum);
			sum = quantity;
			changelog.submitChange("change", (*it)->getName(),quantity);
			std::cout << "Product " << (*it)->getName() << " had " << quantity << " " << (*it)->stringMeasurementUnit() << " removed" << std::endl;
			it++;
		}
		
	}
}

/// <summary>
/// prints all of the loaded log messages from date to date
/// </summary>
/// <param name="from"></param>
/// <param name="to"></param>
void Warehouse::log(std::string from, std::string to, std::ostream& os) const
{
	changelog.printLog(from,to, os);
}

/// <summary>
/// goes through the product list and removes expiring products from their location, and then from the productList
/// this also deletes the pointers of the removed products
/// logs any cleaned product in the changelog
/// </summary>
void Warehouse::clean(std::ostream& os)
{
	int count = 0;
	std::vector<Product*>::iterator it = productList.begin();
	while (it != productList.end())
	{
		if ((*it)->closeToExpiration())
		{
			int sectionId = (*it)->getSectionId();
			int shelfId = (*it)->getShelfId();
			int numberId = (*it)->getNumberId();
			sections[sectionId].getShelves()[shelfId].getNumbers()[numberId].removeProduct((*it));
			count++;
			os << "Cleaned ";
			(*it)->print(os);
			changelog.submitChange("clean", (*it)->productAsMessage());
			delete* it;

			it = productList.erase(it);
		}
		else {
			it++;
		}

	}

	if (count == 0)
	{
		std::cout << "No expired products." << std::endl;
		return;
	}
}

/// <summary>
/// goes through all products with the name, checks every product if it expires during the period, gets enough quantity
/// and from that quantity calculates how much is lost 
/// it follows a similar logic to remove, where if the quantity isnt met it prompts the user whether it should check for the available one
/// </summary>
/// <param name="name"></param>
/// <param name="price"></param>
/// <param name="quantity"></param>
/// <param name="from"></param>
/// <param name="to"></param>
void Warehouse::check_losses(std::string name, double price, double quantity, std::string from, std::string to, std::ostream& os)
{
	
	// sorts the list so that the latest come up to the top, which is for the next code to iterate over it properly
	
	std::sort(productList.begin(), productList.end(), [](Product* first, Product* other) {
		return *first < *other;
		});

	//finds the placement of the first product of the type that it's going to check from
	std::vector<Product*>::iterator it = std::find_if(productList.begin(), productList.end(), [name](Product* p)
		{
			return p->getName() == name;
		});
	if (it == productList.end())
	{
		std::cout << "Product does not exist in warehouse." << std::endl;
		return;
	}

	/// <summary>
	/// gets the dates ad transforms them into a time type that can be compared
	/// </summary>
	struct tm fromDate;
	fromDate.tm_hour = 0;
	fromDate.tm_min = 0;
	fromDate.tm_sec = 0;

	struct tm toDate;
	toDate.tm_hour = 0;
	toDate.tm_min = 0;
	toDate.tm_sec = 0;

	std::istringstream ss1(from);
	ss1 >> std::get_time(&fromDate, "%Y-%m-%d");

	std::istringstream ss2(to);
	ss2 >> std::get_time(&toDate, "%Y-%m-%d");

	if (ss1.fail() || ss2.fail())
	{
		throw std::invalid_argument("Invalid time format, YYYY-mm-dd only.");
	}

	std::time_t fromTime = mktime(&fromDate);
	std::time_t toTime = mktime(&toDate);
	

	double sum = 0;
	double lostExpenses = 0;
	while (it != productList.end() && ((*it)->getName() == name && sum != quantity))
	{

		double change = (*it)->getQuantity();
		if (sum + (*it)->getQuantity() <= quantity)
		{
			sum += (*it)->getQuantity();
		}
		else {
			change = quantity - sum;
			sum = quantity;
		}

		struct tm expDate = (*it)->getExpDate();
		std::time_t expTime = mktime(&expDate);
		if (expTime >= fromTime && expTime <= toTime)
		{
			lostExpenses += change * price;
		}
		it++;
	}

	
	if (sum < quantity)
	{
		std::cout << "Amount not met, only " << sum << " amount of " << name << " in warehouse." << std::endl;
		std::cout << "Still check losses? (Y/N)" << std::endl;
		std::string answer;
		std::cin >> answer;
		if (answer == "N")
		{
			return;
		}
	}

	os << "Money lost: " << lostExpenses << std::endl;
}

/// <summary>
/// add function that adds a product to the warehouse depending on the products location, unless it's full
/// </summary>
/// <param name="product"></param>
/// <returns></returns>
bool Warehouse::addDirectly(Product* p)
{
	Product* newProduct = new Product(*p);
	int sectionId = p->getSectionId();
	int shelfId = p->getShelfId();
	int numberId = p->getNumberId();
	newProduct->setSectionId(sectionId);
	newProduct->setShelfId(shelfId);
	newProduct->setNumberId(numberId);
	productList.push_back(newProduct);
	return sections[sectionId].addDirectly(newProduct);
}

/// <summary>
/// general swap method for warehouse using the standard swap function
/// </summary>
/// <param name="other"></param>
void Warehouse::swap(Warehouse& other)
{
	using std::swap;
	swap(sections, other.sections);
	swap(productList, other.productList);
}

/// <summary>
/// returns the index of the product if found, if not returns -1
/// this is achieved by using std::find and a lambda which turns the pointers to products who have a defined == operator
/// </summary>
/// /// <param name="product"></param>
int Warehouse::findProduct(Product* p)
{
	int i = -1;
	std::vector<Product*>::iterator it =
		std::find_if(productList.begin(), productList.end(), [p](Product* prod) -> bool {return *prod == *p; });
	if (it != productList.end())
	{
		i = std::distance(productList.begin(), it);
	}
	return i;
}

/// <summary>
/// prints every product in the product list using the << operator of Product
/// </summary>
/// <param name="os"></param>
void Warehouse::printProductList(std::ostream& os) const
{
	for (Product* p : productList)
	{
		Product pr = *p;
		os << pr;
	}
}

std::vector<Section>& Warehouse::getSections()
{
	return sections;
}

/// <summary>
/// destructor for warehouse to properly get rid of the pointers in the product list
/// </summary>
Warehouse::~Warehouse()
{
	for (Product* p : productList)
	{
		delete p;
	}
}

/// <summary>
/// prints every product in the product list
/// </summary>
/// <param name="os"></param>
/// <param name="warehouse"></param>
/// <returns></returns>
std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse)
{
	warehouse.printProductList(os);
	return os;
}

/// <summary>
/// reads every product in the given istream
/// </summary>
/// <param name="is"></param>
/// <param name="warehouse"></param>
/// <returns></returns>
std::istream& operator>>(std::istream& is, Warehouse& warehouse)
{
	Product p;
	while (is >> p) {
		warehouse.addDirectly(&p);
	}
	return is;
}
