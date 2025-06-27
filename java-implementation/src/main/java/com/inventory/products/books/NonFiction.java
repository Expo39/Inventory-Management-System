package com.inventory.products.books;

// Represents a concrete subclass of Books
public class NonFiction extends Books {
    private String field;

    // Constructs an instance with specified details with base class attributes included
    public NonFiction(int id, String name, double price, int volume, String author, String publisher, String field, String supplier) {
        super(id, name, price, volume, author, publisher, supplier);
        this.field = field;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 12) {
            return price * volume * 0.25;
        }
        return 0;
    }

    // Provides a string representation the details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nNon-Fiction Book: " + name + "\nAuthor: " + author
               + "\nPublisher: " + publisher + "\nField: " + field
               + "\nPrice: €" + price + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
