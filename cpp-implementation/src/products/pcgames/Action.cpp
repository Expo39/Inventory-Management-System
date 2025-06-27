#include "Product.ih"

// Constructor implementation for action games
Action::Action(int id, string name, double price, int volume, string genre, 
               int ageRating, bool multiplayer, string supplier)
    : PC_Games(id, name, price, volume, genre, ageRating, supplier), 
      multiplayer(multiplayer) {}

// Calculates the discount depending on the current month and the packaged quantity
double Action::calculateDiscount(int volume, int month) const {
    if (month == 12) {
        return price * volume * 0.50;
    }
    return 0;
}

// Displays all the information 
string Action::displayProductInfo() const {
    ostringstream info;

    info << "ID: " << id << "\nnGame: " << name << "\nSupplier: " << getSupplier()
    << "\nGenre: " << genre << "\nMinimum Age: " << ageRating
    << "\nMultiplayer: " << (multiplayer ? "Yes" : "No") << "\nnPrice: €" << price
    << "\nVolume: " << volume << " units\n\n";

    return info.str();
}

