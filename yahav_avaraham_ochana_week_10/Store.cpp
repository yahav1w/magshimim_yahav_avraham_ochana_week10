#include "Store.h"
#include <fstream>
#include <sstream>
#include <algorithm>

//the constructor create a new object kind store 
Store::Store(std::string storeName, std::string inventoryFileName)
{
	_storeName = storeName;
	getInventoryFromFile(inventoryFileName);
}

//the function return the store name
std::string Store::getName() const
{
	return _storeName;
}

//the function sort and return a string of the sorted product
//sortingCriteria - the kind of sorting
std::string Store::getSortedProductList(SortingCriteria sortingCriteria)
{
	std::ostringstream os;
	switch (sortingCriteria)
	{
	case CATEGORY:
		std::sort(_products.begin(), _products.end(), CategoryComparator);
		break;
	case NAME:
		std::sort(_products.begin(), _products.end(), NameComparator);
		break;
	case PRICE:
		std::sort(_products.begin(), _products.end(), PriceComparator);
		break;
	case SERIAL:
		std::sort(_products.begin(), _products.end(), SerialComparator);
		break;
	default:
		throw;
	}
	for (int i = 0;i < _products.size();i++)
	{
		os << _products[i] << "\n";
	}
	return os.str();
}

template <class T>
std::string Store::EnterStringKind(T objArr, ItemCategory kind)
{
	std::ostringstream os;
	for (int i = 0; i < _products.size();i++)
	{
		if (_products[i].getCategory() == kind)
		{
			os << _products[i] << "\n";
		}
	}
	return os.str();
}

//the function return a string with all the product that in the category ask about
//category - the category of the product to return
std::string Store::getProductListFilteredByCategory(ItemCategory category)
{
	std::string productText = "";
	switch (category)
	{
	case FOOD:
		productText = EnterStringKind(_products,category);
		break;
	case PHARM:
		productText = EnterStringKind(_products, category);
		break;
	case CLEANING:
		productText = EnterStringKind(_products, category);
		break;
	case HOME:
		productText = EnterStringKind(_products, category);
		break;
	case NONE:
		productText = EnterStringKind(_products, category);
		break;
	default:
		throw;
	}
	return productText;
}

Item Store::operator[](const int itemNumber) const
{
	if (itemNumber < 0 || itemNumber > _products.size())
	{
		throw std::invalid_argument("");
	}
	return _products[itemNumber];
}





//the function help to print the store by getting and returning an output stream
// os - the output stream 
// store - the store to read from the data
std::ostream& operator<<(std::ostream& os, const Store& store)
{
	os << "Store name:" << store.getName() << "\nProducts:\n";
	for (int i = 0; i < store._products.size();i++)
	{
		os << "[" << i+1 << "] - " << store._products[i].getName()  << "	price: " << store._products[i].getPrice() << "\n";
	}
	return os;
}



void Store::getInventoryFromFile(const std::string inventoryFileName)
{
	// This function reads a CSV file into the object inventory (std::deque<Item>)

	std::deque<std::deque<std::string>> content;	// the entire file as strings
	std::deque<std::string> row;					// a row in the file as string
	std::string line, word;							

	std::fstream file(inventoryFileName, std::ios::in);		// openning the csv file for read
	if (file.is_open())
	{
		while (std::getline(file, line))		// reading line by line
		{
			row.clear();

			std::stringstream str(line);		// adding the line to a std::stringstream

			while (std::getline(str, word, ','))	// reading each word seperated by ','
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
	{
		std::cerr << "Could not open the file " << inventoryFileName << "\n" << std::endl;
		throw std::invalid_argument("Could not open the file " + inventoryFileName);
	}

	/* Indexes
		0 --- Item's Name
		1 --- Item's Serial
		2 --- Item's Unit Price
		3 --- Item's Category (int)
	*/

	for (int i = 1; i < content.size(); i++)
	{
		std::string itemName = content[i][0];
		std::string itemSerial = content[i][1];
		double itemPrice = strtod(content[i][2].c_str(), nullptr);
		ItemCategory itemCategory = ItemCategory(stoi(content[i][3]));
		this->_products.push_back(Item(itemName, itemSerial, itemPrice, itemCategory));
	}

	// To print the content remove the comments:
	// for (int i = 0; i < content.size(); i++)
	//{
	//	for (int j = 0; j < content[i].size(); j++)
	//	{
	//		std::cout << content[i][j] << " ";
	//	}
	//	std::cout << "\n";
	//}

}