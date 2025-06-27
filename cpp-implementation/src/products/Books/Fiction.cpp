#include "Product.ih"

// Updated constructor implementation for Fiction books
Fiction::Fiction(int id, string name, double price, int volume,
                 string author, string publisher, string genre, string supplier)
    : Books(id, name, price, volume, author, publisher, supplier),
      genre(genre) {}

// Calculates the discount depending on the current month and the packaged quantity
double Fiction::calculateDiscount(int volume, int month) const {
    if (month == 6 && volume > 3) {
        return price * volume * 0.50;
    }
    return 0;
}

// Displays all the information
string Fiction::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nFiction Book: " << name << "\nSupplier: " << getSupplier()
         << "\nAuthor: " << author << "\nPublisher: " << publisher 
         << "\nGenre: " << genre << "\nPrice: €" << price 
         << "\nVolume: " << volume << " units\n\n";
    return info.str();
}

