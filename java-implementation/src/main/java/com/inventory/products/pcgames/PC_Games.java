package com.inventory.products.pcgames;

import com.inventory.products.Product;

// Abstract class that represents the properties of a PC game product.
public abstract class PC_Games extends Product {
    protected String genre;
    protected int ageRating;

    // Constructs an instance
    public PC_Games(int id, String name, double price, int volume, String genre, int ageRating, String supplier) {
        super(id, name, price, volume, supplier);
        this.genre = genre;
        this.ageRating = ageRating;
    }
}
