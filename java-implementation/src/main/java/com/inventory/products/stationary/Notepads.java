package com.inventory.products.stationary;

// Represents a concrete subclass of Stationary
public class Notepads extends Stationary {
    private int pages;

    //  Constructs an instance with specified details with base class attributes included
    public Notepads(int id, String name, double price, int volume, String material, int pages, String supplier) {
        super(id, name, price, volume, material, supplier);
        this.pages = pages;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 12 && volume > 5) {
            return price * volume * 0.25;
        }
        return 0;
    }

    // Provides a string representation the details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nBrand Name: " + name + "\nPaper Type: " + material
               + "\nNo. of Pages: " + pages + "\nPrice: €" + price
               + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
