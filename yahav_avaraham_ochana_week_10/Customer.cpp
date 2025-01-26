#include "Customer.h"

//constructor entering the name of the customer
//name - the name of the customer
Customer::Customer(std::string name)
{
	_name = name;
}

//constractor entering empty to his name
Customer::Customer()
{
	_name = "";
}

// destructors
Customer::~Customer()
{
	for (auto  it = _shoppingCarts.begin(); it != _shoppingCarts.end(); ++it)
	{
		delete it->second;
	}
	_shoppingCarts.clear();
}
//the function create a new cart for the customer
//shoppingCartName - the name of the cart to add
void Customer::createNewShoppingCart(std::string shoppingCartName)
{
	auto a = _shoppingCarts.begin();
	if (_shoppingCarts.find(shoppingCartName) != _shoppingCarts.end())
	{
		throw std::invalid_argument("");
		return;
	}
	_shoppingCarts[shoppingCartName] = new std::set<Item>;
}

//the function return the price of the cart of him by her name
//shoppingCartName - the name of the cart
double Customer::shoppingCartSum(std::string shoppingCartName)
{
	double sum = 0;
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end())
	{
		std::set<Item>& c = *it->second;
		auto itSet = c.begin();
		for (int i = 0;itSet != c.end();i++)
		{
			sum += itSet->totalPrice();
			itSet++;
		}
	}
	return sum;
}

//the function calculate the sum of all the cart
//the function return the price to buy all his cart
double Customer::totalSum()
{
	double sum = 0;
	for (auto it = _shoppingCarts.begin();it != _shoppingCarts.end();it++)
	{
		sum += shoppingCartSum(it->first);
	}
	return sum;
}

//the function will add an item to the cart of the user
//item - the item to add
//shoppingCartName - the cart to add the item
void Customer::addItem(Item item, std::string shoppingCartName)
{
	auto it = _shoppingCarts.find(shoppingCartName);
	auto itSet = it->second->begin();
	while(itSet != it->second->end())
	{
		if (itSet->getSerial() == item.getSerial())
		{
			Item item = *itSet;
			item.setCount(itSet->getCount() + 1);
			it->second->erase(itSet);
			it->second->insert(item);
			return;
		}
		itSet++;
	}
	auto Set = it->second;
	Set->insert(item);
	
}

void Customer::removeItem(Item item, std::string shoppingCartName)
{
	auto it = _shoppingCarts.find(shoppingCartName);
	for (auto itSet = it->second->begin();itSet != it->second->end();itSet++)
	{
		if (itSet->getSerial() == item.getSerial())
		{
			if (itSet->getCount() != 1)
			{
				Item item = *itSet;
				item.setCount(itSet->getCount() - 1);
				it->second->erase(itSet);
				it->second->insert(item);
				return;
			}
			else
			{
				std::set<Item>& c = *it->second;
				it->second->erase(item);
				return;
			}
		}
	}
}

std::map<std::string, std::set<Item>*> Customer::getShoppingCarts()
{
	return _shoppingCarts;
}

//return the name of the customer
std::string Customer::getName()
{
	return _name;
}

std::set<Item>* Customer::getShoppingCart(std::string shoppingCartName)
{
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end())
	{
		return it->second;
	}
	return nullptr;
}
