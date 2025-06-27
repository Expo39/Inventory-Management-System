package com.inventory.products.stationary;

import com.inventory.products.Product;

// Abstract class that represents the properties of a stationary product.
public abstract class Stationary extends Product {
    protected String material; // Material of a product

    // Constructs a stationary instance
    public Stationary(int id, String name, double price, int volume, String material, String supplier) {

        // Call the base class constructor with id, name, price, volume, and supplier
        super(id, name, price, volume, supplier);
        this.material = material;
    }
}
