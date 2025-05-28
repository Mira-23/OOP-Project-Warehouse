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

bool Warehouse::add(Product& product)
{
	int productIndex = findProduct(product);
	if (productIndex>=0 && (*productList[productIndex]) == product)
	{
		int sectionId = (*productList[productIndex])[0];
		int shelfId = (*productList[productIndex])[1];
		int numberId = (*productList[productIndex])[2];
		Number num = sections[sectionId].getShelves()[shelfId].getNumbers()[numberId];
		product[0] = sectionId;
		product[1] = shelfId;
		product[2] = numberId;
		return num.add(product);
	}
	/*if (sections.size() == sectionAmount) change to sections filled
	{
		return false;
	}*/
	for (int i = 0; i < sections.size();i++) {
		
		product[0] = i;
		if (sections[i].add(product))
		{	
			productList.push_back(new Product(product));
			return true;
		}
	}
	return false; // warehouse full
}

void Warehouse::remove(std::string name, double quantity)
{
	std::sort(productList.begin(), productList.end());
	int i = 0;
	//change this to a compare function in product
	while ((*productList[i]).getName() != name && i!=productList.size()) { i++; }
	if (i == productList.size())
	{
		std::cout << "Product does not exist in warehouse." << std::endl;
		return;
	}
	
	double totalQuantity = 0;
	i = 0;
	while (i != productList.size() && ((*productList[i]).getName() == name))
	{
		totalQuantity += (*productList[i]).getQuantity();
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

	std::vector<int> removedProducts;
	double sum = 0;
	i = 0;
	//same as above
	while (i != productList.size() && ((*productList[i]).getName() == name && sum!=quantity))
	{
		if (sum + (*productList[i]).getQuantity() <= quantity)
		{
			sum += (*productList[i]).getQuantity();

			int sectionId = (*productList[i])[0];
			int shelfId = (*productList[i])[1];
			int numberId = (*productList[i])[2];
			sections[sectionId].getShelves()[shelfId].getNumbers()[numberId].removeProduct(*productList[i]);
			removedProducts.push_back(i);

			quantity -= sum;
			std::cout << "Product removed due to qunatity" << std::endl;
		}
		else {
			(*productList[i]).reduceQuantityBy(quantity);
		}
		i++;
	}

	for (int j : removedProducts)
	{
		std::cout << "Product removed" << std::endl;
		productList.erase(productList.begin() + j);
	}
}

void Warehouse::swap(Warehouse& other)
{
	using std::swap;
	swap(sections, other.sections);
	swap(productList, other.productList);
}

int Warehouse::findProduct(Product p)
{
	int i = -1;
	std::vector<Product*>::iterator it = std::find_if(productList.begin(), productList.end(), [p](Product* prod) -> bool {return *prod == p; });
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
