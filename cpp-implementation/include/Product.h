#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <memory>

using namespace std;

// The base abstract class for all products
class Product {
protected:
    int id;
    string name;
    double price;
    int volume;
    string supplier;

public:
    // Product constructor
    Product(int id, string name, double price, int volume, string supplier)
        : id(id), name(name), price(price), volume(volume), supplier(supplier) {}


    // Virtual destructor to allow for proper cleanup in derived classes
    virtual ~Product() = default;

    // Getter for the product ID
    int getId() const { return id; }

    // Getter for the product volume
    int getVolume() const { return volume; } 

    string getSupplier() const { return supplier; }

    // Getter for the product price
    int getPrice() const { return price; } 

    // Virtual methods that must be overridden in derived classes
    virtual double calculateDiscount(int volume, int month) const = 0;
    virtual string displayProductInfo() const = 0;
    
};

#endif
