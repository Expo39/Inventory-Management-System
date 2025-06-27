#include "Product.ih"

// Constructor implementation for Acoustic guitars
Acoustic::Acoustic(int id, string name, double price, int volume, 
                    string material, int stringCount, bool hasPickup, 
                    string supplier)
    : Guitars(id, name, price, volume, material, stringCount, supplier), 
      hasPickup(hasPickup) {}

// Calculates the discount depending on the current month and the packaged quantity
double Acoustic::calculateDiscount(int volume, int month) const {
    if (month == 6 && volume > 3) {
        return price * volume * 0.50;
    }
    return 0;
}

// Displays all the information
string Acoustic::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nAcoustic Guitar: " << name << "\nSupplier: " << getSupplier()
         << "\nMaterial: " << material << "\nHas Pickup: " << (hasPickup ? "Yes" : "No")
         << "\nPrice: €" << price << "\nString Count: " << stringCount
         << "\nVolume: " << volume << " units\n\n";
    return info.str();
}
