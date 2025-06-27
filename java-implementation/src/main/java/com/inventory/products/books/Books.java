package com.inventory.products.books;

import com.inventory.products.Product;

// Abstract class that represents the properties of a book product.
public abstract class Books extends Product {
    protected String author;
    protected String publisher;

    // Constructs an instance
    public Books(int id, String name, double price, int volume, String author, String publisher, String supplier) {
        super(id, name, price, volume, supplier);
        this.author = author;
        this.publisher = publisher;
    }
}
