#include "Product.h"
#include <string>
#include <sstream>
#include <iomanip>

Product::Product(std::string name,
	std::string expirationDate,
	std::string enterDate,
	std::string manufacturer,
	std::string measurementUnit,
	std::string quantity,
	std::string comment)
{
	MeasurementUnit un;
	if (measurementUnit == "Kilograms")
	{
		un = MeasurementUnit::Kilograms;
	}
	else if (measurementUnit == "Litres")
	{
		un = MeasurementUnit::Litres;
	}
	else {
		throw std::invalid_argument("Invalid/Unsupported measurement unit");
	}

	if (name.empty()) {
		throw std::invalid_argument("Product name cannot be empty.");
	}

	if (manufacturer.empty()) {
		throw std::invalid_argument("Manufacturer name cannot be empty.");
	}

	double quantityValue = std::stod(quantity); // this throws invalid argument by itself if it fails, so it's redundant to check

	if (quantityValue <= 0) {
		throw std::invalid_argument("Quantity must be greater than 0.");
	}

	struct tm exDate = {};
	struct tm enDate = {};

	std::istringstream ss1(expirationDate);
	ss1 >> std::get_time(&exDate, "%d/%m/%Y");
	
	if (ss1.fail() || !isDateValid(exDate)) {
		throw std::invalid_argument("Invalid expiration date.");
	}

	std::istringstream ss2(enterDate);
	ss2 >> std::get_time(&enDate, "%d/%m/%Y");

	if (ss2.fail() || !isDateValid(enDate)) {
		throw std::invalid_argument("Invalid enter date.");
	}

	this->name = name;
	this->expirationDate = exDate;
	this->enterDate = enDate;
	this->manufacturer = manufacturer; 
	this->measurementUnit = un; 
	this->quantity = quantityValue; 
	this->comment = comment; 

	for (int i = 0; i < 3; i++)
	{
		location[i] = -1;
	}
}

void Product::setNumberId(int id) { location[2] = id; }
void Product::setShelfId(int id) { location[1] = id; }
void Product::setSectionId(int id) { location[0] = id; }

int Product::getNumberId() const { return location[2]; }
int Product::getShelfId() const { return location[1]; }
int Product::getSectionId() const { return location[0]; }

double Product::getQuantity() const { return quantity; }

void Product::reduceQuantityBy(double amount) { quantity -= amount; }

std::string Product::getName() const { return name; }

bool Product::closeToExpiration()
{
	struct tm* newTime = new struct tm(expirationDate);
	time_t t1 = std::time(0);
	time_t t2 = mktime(newTime);
	double twoDays = 2 * 24 * 60 * 60;
	bool check = difftime(t1, t2) <= twoDays;
	delete newTime;
	return check;
}

bool Product::operator==(const Product& other)
{
    return (name == other.name) &&
		(manufacturer == other.manufacturer) &&
		compareDate(enterDate,other.enterDate) &&
		(location[0] == other.location[0]) &&
		(location[1] == other.location[1]) &&
		(location[2] == other.location[2]) &&
		(measurementUnit == other.measurementUnit) &&
		(quantity == other.quantity);
}

bool Product::operator!=(const Product& other)
{
	return !(*this == other);
}

bool Product::compareDate(const tm& first, const tm& other)
{
	return (first.tm_year == other.tm_year) &&
		(first.tm_mon == other.tm_mon) &&
		(first.tm_mday == other.tm_mday);
}

bool Product::isDateValid(const tm& date)
{
	struct tm copy = date;
	copy.tm_isdst = -1;
	time_t t = mktime(&copy);

	if (t == -1) return false;

	return compareDate(copy, date);
}

//this lets functions sort by name -> exp date -> quantity
bool Product::operator<(Product& other)
{
	if (name != other.name)
	{
		return name < other.name;
	}	
	if (!compareDate(expirationDate,other.expirationDate))
	{
		return expirationDate.tm_mday < other.expirationDate.tm_mday &&
			expirationDate.tm_mon < other.expirationDate.tm_mon &&
			expirationDate.tm_year < other.expirationDate.tm_year;
	}
	return quantity < other.quantity;
}
