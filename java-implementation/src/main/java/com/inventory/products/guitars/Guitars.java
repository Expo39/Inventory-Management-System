package com.inventory.products.guitars;

import com.inventory.products.Product;

// Abstract class representing the properties of a guitar.
public abstract class Guitars extends Product {
    protected String material; // Material of the guitar body
    protected int stringCount; // Number of strings on the guitar

    // Constructs a Guitar instance with specified details
    public Guitars(int id, String name, double price, int volume, String material, int stringCount, String supplier) {
        super(id, name, price, volume, supplier);
        this.material = material;
        this.stringCount = stringCount;
    }
}
