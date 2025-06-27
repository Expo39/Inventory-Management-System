package com.inventory.products.guitars;

// Represents an acoustic guitar as a concrete subclass of Guitar.
public class Acoustic extends Guitars {
    private boolean hasPickup; // Indicates if the acoustic guitar has a pickup

    // Constructs an instance with specified details
    public Acoustic(int id, String name, double price, int volume, String material, int stringCount, boolean hasPickup, String supplier) {
        super(id, name, price, volume, material, stringCount, supplier);
        this.hasPickup = hasPickup;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 6 && volume > 3) {
            return price * volume * 0.50;
        }
        return 0;
    }

    // Provides a string representation of the acoustic guitar's details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nAcoustic Guitar: " + name + "\nMaterial: " + material
               + "\nHas Pickup: " + (hasPickup ? "Yes" : "No") + "\nPrice: €" + price
               + "\nString Count: " + stringCount + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
