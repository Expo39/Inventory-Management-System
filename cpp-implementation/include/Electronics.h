#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"
#include <string>

using namespace std;

// The abstract class for Electronics
class Electronics : public Product {
protected:
    string brand;
    int warranty;

public:
    Electronics(int id, string name, double price, int volume, string brand, int warranty, const string& supplier)
        : Product(id, move(name), price, volume, supplier), brand(move(brand)), warranty(warranty) {}
};

// Concrete subclass for laptops
class Laptops : public Electronics {
public:
    Laptops(int id, string name, double price, int volume, string brand, string operatingSystem, int warranty, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    string operatingSystem;
};

// Concrete subclass for phones
class Phones : public Electronics {
public:
    Phones(int id, string name, double price, int volume, int year, int storage, string brand, int warranty, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    int year;
    int storage;
};

#endif
