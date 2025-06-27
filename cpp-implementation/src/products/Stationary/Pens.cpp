#include "Product.ih"

// Constructor implementation for Pens
Pens::Pens(int id, string name, double price, int volume, 
            string material, string inkType, string supplier)
    : Stationary(id, name, price, volume, material, supplier), inkType(inkType) {}

// Implementation of calculateDiscount for Pens
double Pens::calculateDiscount(int volume, int month) const {
    if ((month == 6 && volume > 5) || (month == 12 && volume > 5)) {
        return price * volume * 0.25;
    }
    return 0;
}

// Implementation of displayProductInfo for Pens
string Pens::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nPen: " << name << "\nSupplier: " << supplier
         << "\nMaterial: " << material << "\nInk Type: " << inkType
         << "\nPrice: €" << price << "\nVolume: " << volume << " units\n\n";
    return info.str();
}
