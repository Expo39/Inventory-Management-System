package com.inventory.products.guitars;

// Represents an electric guitar as a concrete subclass of Guitar.
public class Electric extends Guitars {
    private String pickupType; // Type of pickup used in the electric guitar

    // Constructs an ElectricGuitar instance with specified details
    public Electric(int id, String name, double price, int volume, String material, int stringCount, String pickupType, String supplier) {
        super(id, name, price, volume, material, stringCount, supplier);
        this.pickupType = pickupType;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 12) {
            return price * volume * 0.50;
        }
        return 0;
    }

    // Provides a string representation of the electric guitar's details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nElectric Guitar: " + name + "\nMaterial: " + material
               + "\nPickup Type: " + pickupType + "\nPrice: €" + price
               + "\nString Count: " + stringCount + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
