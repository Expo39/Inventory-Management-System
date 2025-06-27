package com.inventory.products.pcgames;

// Represents a concrete subclass of PC_Games
public class Action extends PC_Games {
    private boolean multiplayer;

    //  Constructs an instance with specified details with base class attributes included
    public Action(int id, String name, double price, int volume, String genre, int ageRating, boolean multiplayer, String supplier) {
        super(id, name, price, volume, genre, ageRating, supplier);
        this.multiplayer = multiplayer;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 12) {
            return price * volume * 0.50;
        }
        return 0;
    }

    // Provides a string representation the details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nGame: " + name + "\nGenre: " + genre
               + "\nMinimum Age: " + ageRating + "\nMultiplayer ?: " + (multiplayer ? "Yes" : "No")
               + "\nPrice: €" + price + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
