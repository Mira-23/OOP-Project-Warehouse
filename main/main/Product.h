#pragma once
#include <iostream>
#include <cstring>
#include <ctime>

enum class MeasurementUnit
{
	Kilograms,
	Litres
};

//
class Product
{
public:
	Product(std::string name,
		std::time_t expirationDate,
		std::time_t enterDate,
		std::string manifacturer,
		MeasurementUnit measurementUnit,
		double quantity,
		int shelfId,
		std::string comment);
	double getQuantity() const;
	void reduceQuantityBy(double amount);
	std::string getName() const;
	int& operator[](int i);
	bool operator==(const Product& other);
	bool operator!=(const Product& other);
	bool operator<(Product& other);
private:
	std::string name;
	std::time_t expirationDate;
	std::time_t enterDate;
	std::string manifacturer;
	int location[3];
	MeasurementUnit measurementUnit;
	double quantity;
	std::string comment;
};

