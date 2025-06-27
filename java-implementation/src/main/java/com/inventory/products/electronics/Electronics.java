package com.inventory.products.electronics;

import com.inventory.products.Product;

// Abstract class that represents the properties of an electronics product.
public abstract class Electronics extends Product {
    protected String brand;
    protected int warranty;

    // Constructs an instance
    public Electronics(int id, String name, double price, int volume, String brand, int warranty, String supplier) {
        super(id, name, price, volume, supplier);
        this.brand = brand;
        this.warranty = warranty;
    }
}
