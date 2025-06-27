#include "Product.ih"

// Constructor implementation for electric guitars
Electric::Electric(int id, string name, double price, int volume, 
                string material, int stringCount, 
                 string pickupType, string supplier)
    : Guitars(id, name, price, volume, material, stringCount, supplier), 
      pickupType(pickupType) {}

// Calculates the discount depending on the current month and the packaged quantity
double Electric::calculateDiscount(int volume, int month) const {
    if (month == 12) {
        return price * volume * 0.50;
    }
    return 0;
}

// Displays all the information 
string Electric::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nElectric Guitar: " << name << "\nSupplier: " << getSupplier()
         << "\nMaterial: " << material << "\nPickup Type: " << pickupType
         << "\nPrice: €" << price << "\nString Count: " << stringCount
         << "\nVolume: " << volume << " units\n\n";
    return info.str();
}

