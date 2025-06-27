package com.inventory.products.clothing;

// Represents a concrete subclass of Clothing
public class Dresses extends Clothing {
    private String type;

    // Constructs an instance with specified details with base class attributes included
    public Dresses(int id, String name, double price, int volume, String size, String material, String type, String supplier) {
        super(id, name, price, volume, size, material, supplier);
        this.type = type;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 6 && volume > 3) {
            return price * volume * 0.50;
        }
        return 0;
    }

    // Provides a string representation the details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nName: " + name + "\nSize: " + size
               + "\nPrice: €" + price + "\nMaterial: " + material
               + "\nType: " + type + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
