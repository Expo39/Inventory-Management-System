#include "Product.ih"

// Constructor implementation for strategy games
Strategy::Strategy(int id, string name, double price, int volume, string genre, 
                   int ageRating, string theme, string supplier)
    : PC_Games(id, name, price, volume, genre, ageRating, supplier), 
      theme(theme) {}

// Calculates the discount depending on the current month and the packaged quantity
double Strategy::calculateDiscount(int volume, int month) const {
    if (month == 12) {
        return price * volume * 0.25;
    }
    return 0;
}

// Displays all the information
string Strategy::displayProductInfo() const {
    ostringstream info;

    info << "ID: " << id << "\nnGame: " << name << "\nSupplier: " << getSupplier()
    << "\nGenre: " << genre << "\nMinimum Age: " << ageRating
    << "\nTheme: " << theme << "\nnPrice: €" << price
    << "\nVolume: " << volume << " units\n\n";

    return info.str();

}