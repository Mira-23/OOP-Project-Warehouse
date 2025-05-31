#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <sstream> //editing strings
#include <iomanip> //get_time

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
		std::string expirationDate,
		std::string enterDate,
		std::string manufacturer,
		std::string measurementUnit,
		std::string quantity,
		std::string comment);

	bool closeToExpiration();

	void setNumberId(int id);
	void setShelfId(int id);
	void setSectionId(int id);

	int getNumberId() const;
	int getShelfId() const;
	int getSectionId() const;

	std::string getName() const;
	std::string getManufacturer() const;

	std::string stringMeasurementUnit() const;

	double getQuantity() const;
	void reduceQuantityBy(double amount);

	struct tm getExpDate() const;

	bool operator==(const Product& other) const;
	bool operator!=(const Product& other) const;
	bool operator<(const Product& other) const;

	void print(std::ostream& os) const;
	std::string productToString() const;
	std::string productAsMessage() const;
	std::vector<std::string> getProductParams(std::string line, int paramCount, char del);

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

	bool compareDate(const tm& first, const struct tm& other) const;
	bool isDateValid(const struct tm& other) const;
};