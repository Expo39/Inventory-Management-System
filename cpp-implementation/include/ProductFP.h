#ifndef PRODUCT_FACTORY_H
#define PRODUCT_FACTORY_H

#include "Stationary.h"
#include "PC_Games.h"
#include "Electronics.h"
#include "Clothing.h"
#include "Books.h"
#include "Guitars.h"
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Enum containing all the possible product types
enum class ProductType {
    Pen,            
    Notepad,        
    ActionGame,     
    StrategyGame,  
    Laptop,        
    Phone,        
    Dress,             
    Tshirt,             
    FictionBook,        
    NonFictionBook,     
    ElectricGuitar,     
    AcousticGuitar      
};

// Factory Pattern class for creating different types of products
class ProductFP {
public:
    // Create a product based on the given ProductType, parameters and supplier
    static unique_ptr<Product> createProduct(ProductType type, int id, string name, double price, int volume, const vector<string> properties, string supplier) {
        switch (type) {
            case ProductType::Pen:
                return make_unique<Pens>(id, name, price, volume, properties.at(0), properties.at(1), supplier);

            case ProductType::Notepad:
                return make_unique<Notepads>(id, name, price, volume, properties.at(0), stoi(properties.at(1)), supplier);

            case ProductType::ActionGame:
                return make_unique<Action>(id, name, price, volume, properties.at(0), stoi(properties.at(1)), properties.at(2) == "true", supplier);

            case ProductType::StrategyGame:
                return make_unique<Strategy>(id, name, price, volume, properties.at(0), stoi(properties.at(1)), properties.at(2), supplier);

            case ProductType::Laptop:
                return make_unique<Laptops>(id, name, price, volume, properties.at(0), properties.at(1), stoi(properties.at(2)), supplier);

            case ProductType::Phone:
                return make_unique<Phones>(id, name, price, volume, stoi(properties.at(0)), stoi(properties.at(1)), properties.at(2), stoi(properties.at(3)), supplier);

            case ProductType::Dress:
                return make_unique<Dresses>(id, name, price, volume, properties.at(0), properties.at(1), properties.at(2), supplier);

            case ProductType::Tshirt:
                return make_unique<Tshirts>(id, name, price, volume, properties.at(0), properties.at(1), properties.at(2) == "true", supplier);

            case ProductType::FictionBook:
                return make_unique<Fiction>(id, name, price, volume, properties.at(0), properties.at(1), properties.at(2), supplier);

            case ProductType::NonFictionBook:
                return make_unique<NonFiction>(id, name, price, volume, properties.at(0), properties.at(1), properties.at(2), supplier);

            case ProductType::ElectricGuitar:
                return make_unique<Electric>(id, name, price, volume, properties.at(0), stoi(properties.at(1)), properties.at(2), supplier);

            case ProductType::AcousticGuitar:
                return make_unique<Acoustic>(id, name, price, volume, properties.at(0), stoi(properties.at(1)), properties.at(2) == "true", supplier);

            default:
                throw invalid_argument("Unknown product type");
        }
    }
};

#endif
