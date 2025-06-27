#include "Product.ih"

// Updated constructor implementation for dresses
Dresses::Dresses(int id, string name, double price, int volume,
                 string size, string material, string type, string supplier)
    : Clothing(id, name, price, volume, size, material, supplier),
      type(type) {}

// Calculates the discount depending on the current month and the packaged quantity
double Dresses::calculateDiscount(int volume, int month) const {
    if (month == 6 && volume > 3) {
        return price * volume * 0.50;
    }
    return 0;
}

// Displays all the information
string Dresses::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nDress: " << name << "\nSupplier: " << getSupplier()
         << "\nSize: " << size << "\nMaterial: " << material
         << "\nType: " << type << "\nPrice: €" << price
         << "\nVolume: " << volume << " units\n\n";
    return info.str();
}
