#ifndef PC_GAMES_H
#define PC_GAMES_H

#include "Product.h"
#include <string>

using namespace std;

// The abstract class for PC_Games
class PC_Games : public Product {
protected:
    string genre;
    int ageRating;

public:
    // PC_Games constructor 
    PC_Games(int id, string name, double price, int volume, string genre, int ageRating, string supplier)
        : Product(id, name, price, volume, supplier), genre(genre), ageRating(ageRating) {}

};

// Concrete subclass for action games
class Action : public PC_Games {
public:
    Action(int id, string name, double price, int volume, string genre, int ageRating, bool multiplayer, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    bool multiplayer;
};

// Concrete subclass for strategy games
class Strategy : public PC_Games {
public:
    Strategy(int id, string name, double price, int volume, string genre, int ageRating, string theme, string supplier);

    double calculateDiscount(int volume, int month) const override;
    string displayProductInfo() const override;

private:
    string theme;
};

#endif
