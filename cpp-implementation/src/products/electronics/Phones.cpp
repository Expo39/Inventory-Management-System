#include "Product.ih"

// Updated constructor implementation for phones
Phones::Phones(int id, string name, double price, int volume, int year, int storage,
               string brand, int warranty, string supplier)
    : Electronics(id, move(name), price, volume, move(brand), warranty, supplier),
      year(year), storage(storage) {}

// Calculates the discount depending on the current month and the packaged quantity
double Phones::calculateDiscount(int volume, int month) const {
    if (month == 12) {
        return price * volume * 0.25;
    }
    return 0;
}

// Displays all the information 
string Phones::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nPhone: " << name << "\nSupplier: " << getSupplier()
         << "\nBrand: " << brand << "\nWarranty: " << warranty << " years\nStorage: " << storage 
         << " GB\nYear: " << year << "\nPrice: €" << price << "\nVolume: " << volume << " units\n\n";
    return info.str();
}

