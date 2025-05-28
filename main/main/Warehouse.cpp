#include "Warehouse.h"
#include <algorithm>
#include <functional>

Warehouse::Warehouse()
{
	for (int i = 0; i < sectionAmount; i++)
	{
		sections.push_back(Section());
	}
}

Warehouse::Warehouse(Warehouse& other) : sections(other.sections)
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

void Warehouse::print() const
{
	//temporary
	for (Product* p : productList)
	{
		std::cout << p->getName() << std::endl;
	}
}

bool Warehouse::add(Product* product)
{
	//if product is already in database, add it to the number unless it is full
	int productIndex = findProduct(product);
	if (productIndex >= 0 && (*productList[productIndex]) == *product)
	{
		int sectionId = (*productList[productIndex])[0];
		int shelfId = (*productList[productIndex])[1];
		int numberId = (*productList[productIndex])[2];
		Number num = sections[sectionId].getShelves()[shelfId].getNumbers()[numberId];
		(*product)[0] = sectionId;
		(*product)[1] = shelfId;
		(*product)[2] = numberId;
		return num.add(product);
	}
	/*if (sections.size() == sectionAmount) change to sections filled
	{
		return false;
	}*/
	for (int i = 0; i < sections.size(); i++) {

		Product* newProduct = new Product(*product);
		(*newProduct)[0] = i;
		if (sections[i].add(newProduct))
		{
			productList.push_back(newProduct);
			return true;
		}
	}
	return false; // warehouse full
}

void Warehouse::remove(std::string name, double quantity)
{
	//sorts the list so that the latest come up to the top, which is for the next code to iterate over it properly
	std::sort(productList.begin(), productList.end(), [](Product* first, Product* other) {
		return *first < *other;
		});

	//finds the index of the first product of the type that it's going to remove from
	int i = 0;
	//change this to a compare function in product
	while ((*productList[i]).getName() != name && i != productList.size()) { i++; }
	if (i == productList.size())
	{
		std::cout << "Product does not exist in warehouse." << std::endl;
		return;
	}

	//checks whether the total quantity of all the products that are removed is less than the amount requested
	double totalQuantity = 0;
	i = 0;
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
	i = 0;
	//same as above
	//if the quantity is more than one product holds - remove the soonest expiring one and continue removing until the quantity is full
	//if it isnt, directly removes the needed quantity from the first product
	while (i != productList.size() && ((*productList[i]).getName() == name && sum != quantity))
	{
		if (sum + productList[i]->getQuantity() <= quantity)
		{
			sum += productList[i]->getQuantity();

			int sectionId = (*productList[i])[0];
			int shelfId = (*productList[i])[1];
			int numberId = (*productList[i])[2];
			sections[sectionId].getShelves()[shelfId].getNumbers()[numberId].removeProduct(productList[i]);
			removedProducts.push_back(i);

			quantity -= sum;
			std::cout << "Product removed due to qunatity" << std::endl;
		}
		else {
			productList[i]->reduceQuantityBy(quantity);
		}
		i++;
	}

	//removes the removed products from the warehouse vector
	for (int j : removedProducts)
	{
		std::cout << "Product removed" << std::endl;
		productList.erase(productList.begin() + j);
	}
}

void Warehouse::clean()
{
	for (Product* p : productList)
	{
		if (p->closeToExpiration())
		{
			int sectionId = (*p)[0];
			int shelfId = (*p)[1];
			int numberId = (*p)[2];
			sections[sectionId].getShelves()[shelfId].getNumbers()[numberId].removeProduct(p);
			//also remove from this vector
		}
	}
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

Warehouse::~Warehouse()
{
	for (Product* p : productList)
	{
		delete p;
	}
}