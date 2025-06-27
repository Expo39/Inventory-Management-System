#include "Product.ih"

// Updated constructor implementation for NonFiction books
NonFiction::NonFiction(int id, string name, double price, int volume,
                       string author, string publisher, string field, string supplier)
    : Books(id, name, price, volume, author, publisher, supplier),
      field(field) {}

// Calculates the discount depending on the current month and the packaged quantity
double NonFiction::calculateDiscount(int volume, int month) const {
    if (month == 12) {
        return price * volume * 0.25;
    }
    return 0;
}

// Displays all the information 
string NonFiction::displayProductInfo() const {
    ostringstream info;
    info << "ID: " << id << "\nNon-Fiction Book: " << name << "\nSupplier: " << getSupplier()
         << "\nAuthor: " << author << "\nPublisher: " << publisher 
         << "\nField: " << field << "\nPrice: €" << price 
         << "\nVolume: " << volume << " units\n\n";
    return info.str();
}

