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
	Product(std::string name,
		std::time_t expirationDate,
		std::time_t enterDate,
		std::string manifacturer,
		MeasurementUnit measurementUnit,
		double quantity,
		int shelfId,
		std::string comment);
	bool operator==(Product& other);
	bool operator!=(Product& other);
	double getQuantity() const;
private:
	std::string name;
	std::time_t expirationDate;
	std::time_t enterDate;
	std::string manifacturer;
	int placement[3];
	MeasurementUnit measurementUnit;
	double quantity;
	int shelfId;
	std::string comment;

};

