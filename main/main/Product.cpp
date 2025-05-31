#include "Product.h"
#include <cmath>

Product::Product()
{
	name = "";
	expirationDate = struct tm();
	enterDate = struct tm();
	manufacturer = "";
	quantity = 0;
	measurementUnit = MeasurementUnit::Kilograms;
	comment = "";

	for (int i = 0; i < 3; i++)
	{
		location[i] = -1;
	}
}

Product::Product(std::string name,
	std::string enterDate,
	std::string expirationDate,
	std::string manufacturer,
	std::string quantity,
	std::string measurementUnit,
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
	ss1 >> std::get_time(&exDate, "%Y-%m-%d");
	
	if (ss1.fail() || !isDateValid(exDate)) {
		throw std::invalid_argument("Invalid expiration date.");
	}

	std::istringstream ss2(enterDate);
	ss2 >> std::get_time(&enDate, "%Y-%m-%d");

	if (ss2.fail() || !isDateValid(enDate)) {
		throw std::invalid_argument("Invalid enter date.");
	}

	this->name = name;
	this->enterDate = enDate;
	this->expirationDate = exDate;
	this->manufacturer = manufacturer; 
	this->quantity = quantityValue;
	this->measurementUnit = un; 
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

tm Product::getExpDate() const
{
	return expirationDate;
}

std::string Product::getName() const { return name; }

std::string Product::getManufacturer() const { return manufacturer; }

std::string Product::stringMeasurementUnit() const
{
	std::string result;
	measurementUnit == MeasurementUnit::Kilograms ? result = "Kilograms" : result = "Litres";
	return result;
}

bool Product::closeToExpiration()
{
	expirationDate.tm_hour = 0;
	expirationDate.tm_min = 0;
	expirationDate.tm_sec = 0;

	time_t t1 = std::time(0);
	time_t t2 = mktime(&expirationDate);
	long diff = ((std::abs(t2-t1) / 60) / 60) / 24;
	bool check = (diff <= 2) || t1>t2; //expires in 2 days
	return check;
}

bool Product::operator==(const Product& other) const
{
    return (name == other.name) &&
		(manufacturer == other.manufacturer) &&
		compareDate(expirationDate,other.expirationDate) &&
		(quantity == other.quantity) &&
		(measurementUnit == other.measurementUnit);
}

bool Product::operator!=(const Product& other) const
{
	return !(*this == other);
}

bool Product::compareDate(const tm& first, const tm& other) const
{
	return (first.tm_year == other.tm_year) &&
		(first.tm_mon == other.tm_mon) &&
		(first.tm_mday == other.tm_mday);
}

bool Product::isDateValid(const tm& date) const
{
	struct tm copy = date;

	copy.tm_hour = 0;
	copy.tm_min = 0;
	copy.tm_sec = 0;

	copy.tm_isdst = -1;
	time_t t = mktime(&copy);

	if (t == -1) return false;

	return compareDate(copy, date);
}

//this lets functions sort by name -> exp date -> quantity
bool Product::operator<(const Product& other) const
{
	if (name != other.name)
	{
		return name < other.name;
	}

	std::tm thisDate = expirationDate;
	thisDate.tm_hour = 0;
	thisDate.tm_min = 0;
	thisDate.tm_sec = 0;

	std::tm otherDate = other.expirationDate;
	otherDate.tm_hour = 0;
	otherDate.tm_min = 0;
	otherDate.tm_sec = 0;

	time_t t1 = mktime(&thisDate);
	time_t t2 = mktime(&otherDate);

	if (t1 != t2) {
		return t1 < t2;
	}

	return quantity < other.quantity;
}

void Product::print(std::ostream& os) const
{
	os << productToString() << std::endl;
}

std::string Product::productToString() const
{
	std::string mUnit;
	measurementUnit == MeasurementUnit::Kilograms ? mUnit = "Kilograms" : mUnit = "Litres";
	std::stringstream  ss;
	ss << name << "|"
		<< enterDate.tm_year + 1900 << "-" << enterDate.tm_mon + 1 << "-" << enterDate.tm_mday << "|"
		<< expirationDate.tm_year + 1900 << "-" << expirationDate.tm_mon + 1 << "-" << expirationDate.tm_mday << "|"
		<< manufacturer << "|"
		<< location[0] << "/" << location[1] << "/" << location[2] << "|"
		<< quantity << "|"
		<< mUnit << "|"
		<< comment;
	std::string result = ss.str();
	return result;
}

std::string Product::productAsMessage() const
{
	std::string mUnit;
	measurementUnit == MeasurementUnit::Kilograms ? mUnit = "Kilograms" : mUnit = "Litres";
	std::stringstream  ss;
	ss << "Product " << name
		<< " that entered on " << enterDate.tm_year + 1900 << "-" << enterDate.tm_mon + 1 << "-" << enterDate.tm_mday
		<< " and expires on " << expirationDate.tm_year + 1900 << "-" << expirationDate.tm_mon + 1 << "-" << expirationDate.tm_mday
		<< " from manufacturer " << manufacturer << " with location: SectionId: " << location[0] << ", ShelfId: " << location[1]
		<< ", with NumberId: " << location[2] << " with quantity of " << quantity << " " << mUnit << " (" << comment << ")";
	std::string result = ss.str();
	return result;
}

std::vector<std::string> Product::getProductParams(std::string line, int paramCount, char del)
{
	std::vector<std::string> params;
	std::istringstream ss(line); // gets the parameters as pure strings
	std::string t;

	while (std::getline(ss, t, del))
	{
		params.push_back(t);
	}
	if (params.size() == 7 && (params[6] == "Litres" || params[6] == "Kilograms"))
	{
		params.push_back(" ");
	}
	if (params.size() != paramCount)
	{
		throw std::invalid_argument("Wrong amount of parameters in product reading");
	}
	return params;
}

std::ostream& operator<<(std::ostream& os, const Product& product)
{
	std::string prod = product.productToString();
	os << prod << std::endl;;
	return os;
}

std::istream& operator>>(std::istream& is, Product& product)
{
	std::string line;
	std::getline(is, line);
	if (line.empty())
	{
		is.setstate(std::ios::failbit);
		return is;
	}
	std::vector<std::string> params = product.getProductParams(line, 8, '|');
	product = Product(params[0],params[1],params[2],params[3],params[5],params[6],params[7]);
	std::vector<std::string> indexParams = product.getProductParams(params[4], 3, '/');
	product.setSectionId(std::stoi(indexParams[0]));
	product.setShelfId(std::stoi(indexParams[1]));
	product.setNumberId(std::stoi(indexParams[2]));
	return is;
}
