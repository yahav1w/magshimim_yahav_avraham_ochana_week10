#include "Item.h"
#include <iomanip>

//the constractor create a new object in kind Item
//name - the name of the item
//serialNumber - the id of the Item
//unitPrice - the price of one unit
//category - to which category the product related to
Item::Item(std::string name, std::string serialNumber, double unitPrice, ItemCategory category)
{
	if (unitPrice < 0)
	{
		throw std::invalid_argument("");
	}
	if (serialNumber.length() != 5)
	{
		throw std::invalid_argument("");
	}
	_name = name;
	_serialNumber = serialNumber;
	_unitPrice = unitPrice;
	_category = category;
	_count = 1;
}

//the function check if someone want to buy all the suplie of that item how much he will need to pay
//the function return the how much all the suplie of that item cost
double Item::totalPrice() const
{
	return _count * _unitPrice;
}

//check eho has higher id(serial number)
// other - the other item to compera with
//return true if this has the lower by asci order else false
bool Item::operator<(const Item& other) const
{
	return _serialNumber < other._serialNumber;
}

//check eho has higher id(serial number)
// other - the other item to compera with
//return true if this has the higher by asci order else false
bool Item::operator>(const Item& other) const
{
	return _serialNumber > other._serialNumber;
}

//check if this and other are the same product
// other - the other item to compera with
//return true if they are else return false
bool Item::operator==(const Item& other) const
{
	return _serialNumber == other._serialNumber;
}

//the function return the name of the item
std::string Item::getName() const
{
	return _name;
}

//the function return the serial number(id) of an item
std::string Item::getSerial() const
{
	return _serialNumber;
}

//the function return the price for only one unit of the item
double Item::getPrice() const
{
	return _unitPrice;
}

//the function return the suplie amount 
int Item::getCount() const
{
	return _count;
}

//the function return the category of the item
ItemCategory Item::getCategory() const
{
	return _category;
}

//set the amount of the item
// newCount - the new amount of the item 
void Item::setCount(int newCount)
{
	if (newCount < 0)
	{
		throw std::invalid_argument("");
	}
	_count = newCount;
}

//[Serial: <serial>, Name: <name>, Category: <category>, Price: <price>, Amount : <count>]
//the function return the os to print by the order of this ^ line
std::ostream& operator<<(std::ostream& os, const Item& item)
{
	os << "[Serial: " << item._serialNumber << ", Name: " << item._name << ", Category: " << getItemCategoryString(item._category)
		<< ", Price: " << std::fixed << std::setprecision(6) << item._unitPrice << ", Amount: " << item._count << "]";
	return os;
}
