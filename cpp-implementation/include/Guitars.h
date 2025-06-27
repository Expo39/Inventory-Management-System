#ifndef GUITARS_H
#define GUITARS_H

#include "Product.h"
#include <string>
#include <memory>

using namespace std;

// The abstract class for Guitars
class Guitars : public Product {
protected:
    string material; // Material of the guitar body
    int stringCount;      // Number of strings on the guitar

public:
    // Updated constructor to include supplier
    Guitars(int id, string name, double price, int volume, 
             string material, int stringCount, string supplier)
        : Product(id, name, price, volume, supplier), material(material), stringCount(stringCount) {}

};

// Concrete subclass for electric guitars
class Electric : public Guitars {
private:
    string pickupType; // Type of pickup used in the electric guitar

public:
    // Electric guitar constructor
    Electric(int id, string name, double price, int volume, 
              string material, int stringCount, string pickupType, 
             string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

};

// Concrete subclass for acoustic guitars
class Acoustic : public Guitars {
private:
    bool hasPickup; // Indicates if the acoustic guitar has a pickup

public:
    // Acoustic Guitar constructor
    Acoustic(int id, string name, double price, int volume, 
             string material, int stringCount, bool hasPickup, 
             string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

};

#endif
