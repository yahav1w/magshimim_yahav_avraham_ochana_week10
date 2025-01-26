#include "Customer.h"
#include "Store.h"
#include <map>
#include <iostream>

#define SHEFA_ISASCHAR_SIZE 29
#define MAGSH_IKEA_SIZE 25
#define MAGSHI_PHARM_SIZE 20

int main()
{
    std::map<std::string, Customer> abcCustomers;//the customers array
    double maxPrice = 0;
    int choice = 1, cusChoice = 1, storeToBuy = 0, addItem = 1, count = 0, cartAdd = 1,storeSize = 0;
    std::string name = "", Cart = "";
    std::set<Item>* Cus;
    std::map<std::string, Customer>::iterator it;
    Store s1("Shefa Isaschar", "InventorySuperMarket.csv");
    Store s2("MagshIKEA", "InventoryIKEA.csv");
    Store s3("MagshiPharm", "InventoryPharm.csv");
    Store print = s1;

    while (choice != 4)
    {
        std::cout << "Welcome to MagshiMart!\n1. To sign as customer and buy items\n2. To update existing customer's items\n3. To print the customer who pays the most\n4. To exit" << std::endl;
        std::cout << "\nYour Choice:\n";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter your name: ";
            std::cin >> name;
            abcCustomers.insert({ name, Customer(name) });

            std::cout << "Welcome!\nSelect one of the options from the options below :\n1. To create a new shopping cart\n2. To exit" << std::endl;
            std::cin >> cusChoice;

            switch (cusChoice)
            {
            case 1:
                std::cout << "Enter the new shopping cart name: ";
                std::cin >> Cart;
                it = abcCustomers.find(name);
                Cus = it->second.getShoppingCart(Cart);
                if (Cus != nullptr)
                {
                    std::cout << "Shopping cart already exists\n";
                    break;
                }
                it->second.createNewShoppingCart(Cart);
                std::cout << "Select the store to buy from :\n1. to buy in Shefa Isaschar(Super Market)\n";
                std::cout << "2. to buy in MagshIKEA(Home products)\n3. to buy in MagshiPharm(Pharm and utils)\n4. to exit\n";
                std::cin >> storeToBuy;
                while (storeToBuy != 1 && storeToBuy != 2 && storeToBuy != 3 && storeToBuy != 4)
                {
                    std::cout << "Invalid option. Try again: ";
                    std::cin >> storeToBuy;
                }
                switch (storeToBuy)
                {
                case 1:
                    print = s1;
                    storeSize = SHEFA_ISASCHAR_SIZE;
                    break;
                case 2:
                    print = s2;
                    storeSize = MAGSH_IKEA_SIZE;
                    break;
                case 3:
                    print = s3;
                    storeSize = MAGSHI_PHARM_SIZE;
                    break;
                default:
                    break;
                }
                while (addItem != 0)
                {
                    std::cout << "The items you can buy are: (0 to exit)\n";
                    std::cout << print;
                    std::cin >> addItem;
                    if (addItem != 0 && addItem <= storeSize)
                    {
                        std::set<Item>* c = abcCustomers[name].getShoppingCart(Cart);
                        abcCustomers[name].addItem(print[addItem - 1], Cart);
                    }
                }
                addItem = 1;
                break;
            default:
                break;
            }
            break;

        case 2:
            std::cout << "Enter your name: ";
            std::cin >> name;
            it = abcCustomers.find(name);
            if (it == abcCustomers.end())
            {
                std::cout << "Unable to find this user\n";
                break;
            }
            std::cout << "1. To create a new shopping cart\n2. Update existing shopping cart\n3. Back to main menu\n";
            std::cin >> cusChoice;
            switch (cusChoice)
            {
            case 1:
                std::cout << "Enter the shopping cart name: ";
                std::cin >> Cart;
                it = abcCustomers.find(name);
                Cus = it->second.getShoppingCart(Cart);
                if (Cus != nullptr)
                {
                    std::cout << "Shopping cart already exists\n";
                    break;
                }
                it->second.createNewShoppingCart(Cart);
                std::cout << "Select the store to buy from :\n1. to buy in Shefa Isaschar(Super Market)\n";
                std::cout << "2. to buy in MagshIKEA(Home products)\n3. to buy in MagshiPharm(Pharm and utils)\n4. to exit\n";
                std::cin >> storeToBuy;
                while (storeToBuy != 1 && storeToBuy != 2 && storeToBuy != 3 && storeToBuy != 4)
                {
                    std::cout << "Invalid option. Try again: ";
                    std::cin >> storeToBuy;
                }
                switch (storeToBuy)
                {
                case 1:
                    print = s1;
                    storeSize = SHEFA_ISASCHAR_SIZE;
                    break;
                case 2:
                    print = s2;
                    storeSize = MAGSH_IKEA_SIZE;
                    break;
                case 3:
                    print = s3;
                    storeSize = MAGSHI_PHARM_SIZE;
                    break;
                default:
                    break;
                }
                while (addItem != 0)
                {
                    std::cout << "The items you can buy are: (0 to exit)\n";
                    std::cout << print;
                    std::cin >> addItem;
                    if (addItem != 0 && addItem <= storeSize)
                    {
                        std::set<Item>* c = abcCustomers[name].getShoppingCart(Cart);
                        abcCustomers[name].addItem(print[addItem - 1], Cart);
                    }
                }
                addItem = 1;
                break;

            case 2:
                std::cout << "Select Shopping Cart: (-1 to exit, 0 to create a new shopping cart)\n";
                it = abcCustomers.find(name);
                count = it->second.getShoppingCarts().size();
                int i = 0;
                auto cus = it->second.getShoppingCarts();
                for (auto itMap = cus.begin(); itMap != cus.end(); ++itMap)  // Standard for loop
                {
                    std::cout << i + 1 << ". " << itMap->first << std::endl;  // itMap->first is the cart name
                    i++;
                }
                std::cin >> cartAdd;
                if (cartAdd > count)
                {
                    std::cout << "Does not have a cart in this number\n";
                    break;
                }
                if (cartAdd == -1)
                {
                    break;
                }
                count = 0;
                std::cout << "1. Add items\n2. Back to main menu\n";
                std::cin >> addItem;
                if (addItem != 1)
                {
                    break;
                }
                std::cout << "Enter the shopping cart name: ";
                std::cin >> Cart;
                if (cartAdd == 0)
                {
                    auto Cus = it->second.getShoppingCart(Cart);
                    if (Cus != nullptr)
                    {
                        std::cout << "Shopping cart already exists\n";
                        break;
                    }
                    it->second.createNewShoppingCart(Cart);
                }
                std::cout << "Select the store to buy from :\n1. to buy in Shefa Isaschar(Super Market)\n";
                std::cout << "2. to buy in MagshIKEA(Home products)\n3. to buy in MagshiPharm(Pharm and utils)\n4. to exit\n";
                std::cin >> storeToBuy;
                while (storeToBuy != 1 && storeToBuy != 2 && storeToBuy != 3 && storeToBuy != 4)
                {
                    std::cout << "Invalid option. Try again: ";
                    std::cin >> storeToBuy;
                }
                switch (storeToBuy)
                {
                case 1:
                    print = s1;
                    storeSize = SHEFA_ISASCHAR_SIZE;
                    break;
                case 2:
                    print = s2;
                    storeSize = MAGSH_IKEA_SIZE;
                    break;
                case 3:
                    print = s3;
                    storeSize = MAGSHI_PHARM_SIZE;
                    break;
                default:
                    break;
                }
                storeToBuy = 0;
                while (addItem != 0)
                {
                    std::cout << "The items you can buy are: (0 to exit)\n";
                    std::cout << print;
                    std::cin >> addItem;
                    if (addItem != 0 && addItem <= storeSize)
                    {
                        std::set<Item>* c = abcCustomers[name].getShoppingCart(Cart);
                        abcCustomers[name].addItem(print[addItem - 1], Cart);
                    }
                }
                addItem = 1;
                break;

            }
            break;

        case 3:
            for (auto itMap = abcCustomers.begin(); itMap != abcCustomers.end(); itMap++)
            {
                if (maxPrice < itMap->second.totalSum())
                {
                    maxPrice = itMap->second.totalSum();
                    name = itMap->first;
                }
            }
            std::cout << name << " - price - " << maxPrice << std::endl;
            maxPrice = 0;
            break;
        default:
            break;
        }
    }

    return 0;
}
