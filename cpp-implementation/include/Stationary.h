#ifndef STATIONARY_H
#define STATIONARY_H

#include "Product.h"
#include <string>

using namespace std;

// The abstract class for stationary products
class Stationary : public Product {
protected:
    string material;

public:
    Stationary(int id, string name, double price, int volume, 
             string material, string supplier)
        : Product(id, name, price, volume, supplier), material(material) {}

};

// Concrete subclass for notepads
class Notepads : public Stationary {
public:
    Notepads(int id, string name, double price, int volume, 
             string material, int pages, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    int pages;
};

// Concrete subclass for pens
class Pens : public Stationary {
public:
    Pens(int id, string name, double price, int volume, 
         string material, string inkType, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    string inkType;
};

#endif 
