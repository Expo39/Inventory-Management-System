package com.inventory.products.clothing;

// Represents a concrete subclass of Clothing
public class Tshirts extends Clothing {
    private boolean canBeIroned;

    // Constructs an instance with specified details with base class attributes included
    public Tshirts(int id, String name, double price, int volume, String size, String material, boolean canBeIroned, String supplier) {
        super(id, name, price, volume, size, material, supplier);
        this.canBeIroned = canBeIroned;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 12 && volume > 6) {
            return price * volume * 0.25;
        }
        return 0;
    }

    // Provides a string representation the details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nT-Shirt: " + name + "\nSize: " + size
               + "\nMaterial: " + material + "\nCan it be ironed ?: "
               + (canBeIroned ? "Yes" : "No") + "\nPrice: €" 
               + price + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
