package com.inventory.products.clothing;

import com.inventory.products.Product;

// Abstract class that represents the properties of a clothing product.
public abstract class Clothing extends Product {
    protected String size;
    protected String material;

    // Constructs an instance
    public Clothing(int id, String name, double price, int volume, String size, String material, String supplier) {
        super(id, name, price, volume, supplier);
        this.size = size;
        this.material = material;
    }
}
