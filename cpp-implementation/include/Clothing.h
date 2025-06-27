#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"
#include <string>

using namespace std;

// The abstract class for clothing
class Clothing : public Product {
protected:
    string size;
    string material;

public:
    Clothing(int id, string name, double price, int volume, string size, 
             string material, string supplier)
        : Product(id, name, price, volume, supplier), 
          size(size), material(material) {}
};

// Concrete subclass for dresses
class Dresses : public Clothing {
public:
    Dresses(int id, string name, double price, int volume, string size, 
            string material, string type, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    string type;
};

// Concrete subclass for t-shirts
class Tshirts : public Clothing {
public:
    Tshirts(int id, string name, double price, int volume, string size, 
            string material, bool canBeIroned, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    bool canBeIroned;
};

#endif
