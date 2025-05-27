#include "Warehouse.h"
#include <algorithm>
#include <functional>

bool Warehouse::add(Product product)
{
	int productIndex = findProduct(product);
	if (productIndex>=0 && (*productList[productIndex]) == product)
	{
		int sectionId = (*productList[productIndex])[0];
		int shelfId = (*productList[productIndex])[1];
		int numberId = (*productList[productIndex])[2];
		Number& num = sections[sectionId].getShelves()[shelfId].getNumbers()[numberId];
		product[0] = sectionId;
		product[1] = shelfId;
		product[2] = numberId;
		return num.add(product);
	}
	if (sections.size() == sectionAmount)
	{
		return false;
	}
	for (int i = 0; i < sections.size();i++) {
		if (sections[i].add(product))
		{
			product[0] = i;
			productList.push_back(&product);
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
	while ((*productList[i]).getName() != name || i!=productList.size()) { i++; }
	if (i == productList.size())
	{
		std::cout << "Product does not exist in warehouse." << std::endl;
		return;
	}
	
	double totalQuantity = 0;
	while (((*productList[i]).getName() == name) || i != productList.size())
	{
		totalQuantity += (*productList[i]).getQuantity();
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
	//same as above
	while (((*productList[i]).getName() == name && sum!=quantity) || i != productList.size())
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
		}
		else {
			(*productList[i]).reduceQuantityBy(quantity);
		}
		i++;
	}

	for (int i : removedProducts)
	{
		productList.erase(productList.begin() + i - 1);
	}
}

int Warehouse::findProduct(Product p)
{
	int i = -1;
	std::vector<Product*>::iterator it = std::find_if(productList.begin(), productList.end(), [p](Product* prod) {*prod == p; });
	if (it != productList.end())
	{
		i = std::distance(productList.begin(), it);;
	}
	return i;
}
