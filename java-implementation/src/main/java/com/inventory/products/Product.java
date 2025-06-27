package com.inventory.products;

// Abstract class that represents the general properties of a product.
public abstract class Product {
    protected int id; // Unique identifier for the product
    protected String name; // Name of the product
    protected double price; // Price of the product
    protected int volume; // Quantity of the product in stock
    protected String supplier; // Supplier of the product

    // Constructs a Product instance with the specified id, name, price, volume, and supplier.
    public Product(int id, String name, double price, int volume, String supplier) {
        this.id = id; 
        this.name = name;
        this.price = price;
        this.volume = volume;
        this.supplier = supplier;
    }

    // Gets the product's unique identifier.
    public int getId() {
        return id;
    }

    // Gets the product's volume.
    public int getVolume() {
        return volume;
    }

    // Gets the product's price.
    public double getPrice() {
        return price;
    }

    // Gets the product's supplier.
    public String getSupplier() {
        return supplier;
    }

    // Calculates the discount for the product based on the volume and the month.
    public abstract double calculateDiscount(int volume, int month);

    // Provides a string representation of the product's information.
    public abstract String displayProductInfo();
}
