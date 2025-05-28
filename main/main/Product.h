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
	Product();
	//Product(Product& other);
	Product(std::string name,
		struct tm expirationDate,
		struct tm enterDate,
		std::string manufacturer,
		MeasurementUnit measurementUnit,
		double quantity,
		std::string comment);
	Product(std::string name,
		std::string expirationDate,
		std::string enterDate,
		std::string manufacturer,
		std::string measurementUnit,
		std::string quantity,
		std::string comment);
	double getQuantity() const;
	void reduceQuantityBy(double amount);
	std::string getName() const;
	int& operator[](int i);
	bool operator==(const Product& other);
	bool operator!=(const Product& other);
	bool operator<(Product& other);
	friend std::ostream& operator<<(std::ostream& os, const Product& product);
	friend std::istream& operator>>(std::istream& is, Product& product);
private:
	std::string name;
	struct tm expirationDate;
	struct tm enterDate;
	std::string manufacturer;
	int location[3];
	MeasurementUnit measurementUnit;
	double quantity;
	std::string comment;

	bool compareDate(const tm& first, const struct tm& other);
	bool isDateValid(const struct tm& other);
};