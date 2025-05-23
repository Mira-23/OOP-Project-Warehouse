#pragma once
#include <iostream>
#include <cstring>
#include <ctime>

enum class MeasurementUnit
{
	Kilograms,
	Litres
};

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
private:
	std::string name;
	std::time_t expirationDate;
	std::time_t enterDate;
	std::string manifacturer;
	MeasurementUnit measurementUnit;
	double quantity;
	int shelfId;
	std::string comment;

};

