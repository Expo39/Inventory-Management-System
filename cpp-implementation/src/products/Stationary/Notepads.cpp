#include "Product.ih"

// Constructor implementation for Notepads
Notepads::Notepads(int id, string name, double price, int volume, 
                    string material, int pages, string supplier)
    : Stationary(id, name, price, volume, material, supplier), pages(pages) {}

// Calculates the discount depending on the current month and the packaged quantity
double Notepads::calculateDiscount(int volume, int month) const {
    if (month == 12 && volume > 5) {
        return price * volume * 0.25;
    }
    return 0;
}

// Displays all the information 
string Notepads::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nNotepad Name: " << name << "\nSupplier: " << getSupplier()
         << "\nMaterial: " << material << "\nNumber of Pages: " << pages
         << "\nPrice: €" << price << "\nVolume: " << volume << " units\n\n";
    return info.str();
}
