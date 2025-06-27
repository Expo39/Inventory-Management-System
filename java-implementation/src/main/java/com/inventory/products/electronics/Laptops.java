package com.inventory.products.electronics;

// Represents a concrete subclass of Electronics
public class Laptops extends Electronics {
    private String operatingSystem;

    // Constructs an instance with specified details with base class attributes included
    public Laptops(int id, String name, double price, int volume, String brand, String operatingSystem, int warranty, String supplier) {
        super(id, name, price, volume, brand, warranty, supplier);
        this.operatingSystem = operatingSystem;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 6 || month == 12) {
            return price * volume * 0.50;
        }
        return 0;
    }

    // Provides a string representation the details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nLaptop: " + name + "\nBrand: " + brand
               + "\nOperating System: " + operatingSystem + "\nWarranty: " + warranty
               + " years\nPrice: €" + price + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
