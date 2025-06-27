#include "Product.ih"

// Updated constructor implementation for tshirts
Tshirts::Tshirts(int id, string name, double price, int volume,
                 string size, string material, bool canBeIroned, string supplier)
    : Clothing(id, name, price, volume, size, material, supplier),
      canBeIroned(canBeIroned) {}

// Calculates the discount depending on the current month and the packaged quantity
double Tshirts::calculateDiscount(int volume, int month) const {
    if (month == 12 && volume > 6) {
        return price * volume * 0.25;
    }
    return 0;
}

// Displays all the information 
string Tshirts::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nT-Shirt: " << name << "\nSupplier: " << getSupplier()
         << "\nSize: " << size << "\nMaterial: " << material
         << "\nCan it be ironed ?: " << (canBeIroned ? "Yes" : "No")
         << "\nPrice: €" << price << "\nVolume: " << volume << " units\n\n";
    return info.str();
}

