package com.inventory.products.pcgames;

// Represents a concrete subclass of PC_Games
public class Strategy extends PC_Games {
    private String theme;

    // Constructs an instance with specified details with base class attributes included
    public Strategy(int id, String name, double price, int volume, String genre, int ageRating, String theme, String supplier) {
        super(id, name, price, volume, genre, ageRating, supplier);
        this.theme = theme;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 12) {
            return price * volume * 0.25;
        }
        return 0;
    }

    // Provides a string representation the details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nGame: " + name + "\nGenre: " + genre
               + "\nMinimum Age: " + ageRating + "\nTheme: " + theme
               + "\nPrice: €" + price + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
