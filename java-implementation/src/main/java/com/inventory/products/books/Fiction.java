package com.inventory.products.books;

// Represents a concrete subclass of Books
public class Fiction extends Books {
    private String genre;

    // Constructs an instance with specified details with base class attributes included
    public Fiction(int id, String name, double price, int volume, String author, String publisher, String genre, String supplier) {
        super(id, name, price, volume, author, publisher, supplier);
        this.genre = genre;
    }

    // Calculates the discount based on volume and month
    @Override
    public double calculateDiscount(int volume, int month) {
        if (month == 6 && volume > 3) {
            return price * volume * 0.50;
        }
        return 0;
    }

    // Provides a string representation the details
    @Override
    public String displayProductInfo() {
        return "ID: " + id + "\nFiction Book: " + name + "\nAuthor: " + author
               + "\nPublisher: " + publisher + "\nGenre: " + genre
               + "\nPrice: €" + price + "\nVolume: " + volume + " units\nSupplier: " + supplier + "\n\n";
    }
}
