package com.inventory.products.stationary;

// Represents a pen as a concrete subclass of Stationary.
public class Pens extends Stationary {
    private String inkType; // Type of ink used in the pen

    //  Constructs a Pens instance with specified details
    public Pens(int id, String name, double price, int volume, String material, String inkType, String supplier) {
        super(id, name, price, volume, material, supplier);
        this.inkType = inkType;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if ((month == 6 && volume > 5) || (month == 12 && volume > 5)) {
            return price * volume * 0.25;
        }
        return 0;
    }
    
    // Provides a string representation of the pen's details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nPen: " + name + "\nMaterial: " + material
               + "\nInk Type: " + inkType + "\nPrice: €" + price
               + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n";
    }
}
