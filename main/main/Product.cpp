#include "Product.h"
#include <cmath>

/// <summary>
/// basic default constructor for product that sets the default/empty values for each member
/// </summary>
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

/// <summary>
/// constructor for product that accepts the parameters as string, converts them, checks them for validity and creates the product if everything is accounted for
/// done with the help of stringstream
/// </summary>
/// <param name="name"></param>
/// <param name="enterDate"></param>
/// <param name="expirationDate"></param>
/// <param name="manufacturer"></param>
/// <param name="quantity"></param>
/// <param name="measurementUnit"></param>
/// <param name="comment"></param>
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
	else
	{
		throw std::invalid_argument("Invalid/Unsupported measurement unit");
	}

	if (name.empty())
	{
		throw std::invalid_argument("Product name cannot be empty.");
	}

	if (manufacturer.empty())
	{
		throw std::invalid_argument("Manufacturer name cannot be empty.");
	}

	double quantityValue = std::stod(quantity); // this throws invalid argument by itself if it fails, so it's redundant to check

	if (quantityValue <= 0)
	{
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

	if (ss2.fail() || !isDateValid(enDate))
	{
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

/// <summary>
/// setter for numberId
/// </summary>
/// <param name="id"></param>
void Product::setNumberId(int id)
{
	if (id < 0 || id>10)
	{
		throw std::invalid_argument("Invalid number Id.");
	}
	location[2] = id;
}
/// <summary>
/// setter for shelfId
/// </summary>
/// <param name="id"></param>
void Product::setShelfId(int id)
{
	if (id < 0 || id>10)
	{
		throw std::invalid_argument("Invalid shelf Id.");
	}
	location[1] = id;
}
/// <summary>
/// setter for sectionId
/// </summary>
/// <param name="id"></param>
void Product::setSectionId(int id)
{
	if (id < 0 || id>10)
	{
		throw std::invalid_argument("Invalid section Id.");
	}
	location[0] = id;
}

/// <summary>
/// getter for numberId
/// </summary>
/// <returns></returns>
int Product::getNumberId() const { return location[2]; }
/// <summary>
/// getter for shelfId
/// </summary>
/// <param name="id"></param>
int Product::getShelfId() const { return location[1]; }
/// <summary>
/// getter for sectionId
/// </summary>
/// <param name="id"></param>
int Product::getSectionId() const { return location[0]; }

/// <summary>
/// getter for the quantity
/// </summary>
/// <param name="id"></param>
double Product::getQuantity() const { return quantity; }

/// <summary>
/// function that reduces the quantity of the product given the amount
/// </summary>
/// <param name="amount"></param>
void Product::reduceQuantityBy(double amount)
{
	if (quantity < amount)
	{
		amount = quantity;
	}
	quantity -= amount;
}

tm Product::getEntDate() const
{
	return enterDate;
}

/// <summary>
/// getter for the expirationDate
/// </summary>
/// <param name="id"></param>
tm Product::getExpDate() const
{
	return expirationDate;
}

std::string Product::getComment() const
{
	return comment;
}

/// <summary>
/// getter for the name
/// </summary>
/// <param name="id"></param>
std::string Product::getName() const { return name; }

/// <summary>
/// getter for the manufacturer
/// </summary>
/// <param name="id"></param>
std::string Product::getManufacturer() const { return manufacturer; }

/// <summary>
/// function that converts the measurement unit to string
/// </summary>
/// <returns></returns>
std::string Product::stringMeasurementUnit() const
{
	std::string result;
	measurementUnit == MeasurementUnit::Kilograms ? result = "Kilograms" : result = "Litres";
	return result;
}

/// <summary>
/// checks whether the product's exparation date is 2 days before the current date, or after the current date (meaning its expired)
/// </summary>
/// <returns></returns>
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

/// <summary>
/// compares whether two products are equal based on their name, manufacturer, expiration date and measurement unit
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
bool Product::operator==(const Product& other) const
{
    return (name == other.name) &&
		(manufacturer == other.manufacturer) &&
		compareDate(expirationDate,other.expirationDate) &&
		(measurementUnit == other.measurementUnit);
}

/// <summary>
/// opposite of operator==
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
bool Product::operator!=(const Product& other) const
{
	return !(*this == other);
}

/// <summary>
/// compares whether the year, month and day of two dates are equal
/// </summary>
/// <param name="first"></param>
/// <param name="other"></param>
/// <returns></returns>
bool Product::compareDate(const tm& first, const tm& other) const
{
	return (first.tm_year == other.tm_year) &&
		(first.tm_mon == other.tm_mon) &&
		(first.tm_mday == other.tm_mday);
}

/// <summary>
/// checks whether a given date is valid
/// (used for validation in the constructor
/// </summary>
/// <param name="date"></param>
/// <returns></returns>
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

/// <summary>
/// this lets functions sort by name -> exp date -> quantity
/// </summary>
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

	if (t1 != t2)
	{
		return t1 < t2;
	}

	return quantity < other.quantity;
}

/// <summary>
/// prints base information about the product
/// </summary>
/// <param name="os"></param>
void Product::print(std::ostream& os) const
{
	os << productToString() << std::endl;
}

/// <summary>
/// turns the product into its base information (used for writing into files)
/// done with the help of stringstream
/// </summary>
/// <returns></returns>
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

/// <summary>
/// a prettier way of converting the information about the product as a string
/// done with the help of stringstream
/// </summary>
/// <returns></returns>
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

/// <summary>
/// a helper function to convert a given line into parameters for the creation of a product
/// done with the help of stringstream
/// </summary>
/// <param name="line"></param>
/// <param name="paramCount"></param>
/// <param name="del"></param>
/// <returns></returns>
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

/// <summary>
/// writes a product using the print function
/// </summary>
/// <param name="os"></param>
/// <param name="product"></param>
/// <returns></returns>
std::ostream& operator<<(std::ostream& os, const Product& product)
{
	std::string prod = product.productToString();
	os << prod << std::endl;;
	return os;
}

/// <summary>
/// reads a product from the given istream
/// also filters empty lines
/// </summary>
/// <param name="is"></param>
/// <param name="product"></param>
/// <returns></returns>
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
