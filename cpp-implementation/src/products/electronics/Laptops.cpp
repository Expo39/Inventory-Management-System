#include "Product.ih"

// Updated constructor implementation for laptops
Laptops::Laptops(int id, string name, double price, int volume,
                 string brand, string operatingSystem, int warranty, string supplier)
    : Electronics(id, name, price, volume, brand, warranty, supplier),
      operatingSystem(operatingSystem) {}

// Calculates the discount depending on the current month and the packaged quantity
double Laptops::calculateDiscount(int volume, int month) const {
    if (month == 6 || month == 12) {
        return price * volume * 0.50;
    }
    return 0;
}

// Displays all the information 
string Laptops::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nLaptop: " << name << "\nSupplier: " << getSupplier()
         << "\nBrand: " << brand << "\nOperating System: " << operatingSystem
         << "\nWarranty: " << warranty << " years\nPrice: €" << price
         << "\nVolume: " << volume << " units\n\n";
    return info.str();
}
