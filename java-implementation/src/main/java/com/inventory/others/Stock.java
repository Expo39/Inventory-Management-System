package com.inventory.others;

import java.util.HashMap;
import java.util.Map;
import com.inventory.products.Product;

// Represents a stock of products
public class Stock {
    private Map<Integer, Product> products;

    public Stock() {
        products = new HashMap<>();
    }

    // Adds a new product to the stock.
    public void addProduct(Product product) {
        int id = product.getId(); // Get ID of the product

        // Check if a product with this ID already exists in the stock
        if (products.containsKey(id)) {
            System.err.println("Cannot add product. Product with ID " + id + " is already in use.\n");
        } else {
            products.put(id, product); // Add the product to the stock
            System.out.println("Product with ID " + id + " added to stock.\n");
        }
    }

    // Updates an existing product in the stock
    public void updateProduct(int id, Product product) {
        if (products.containsKey(id)) {
            products.put(id, product); // Replace the existing product with the new one
            System.out.println("Product with ID " + id + " updated.\n");
        } else {
            System.err.println("Cannot update. Product with ID " + id + " not found.\n");
        }
    }

    // Retrieves a product by its ID. Returns the product or null if not found.
    public Product getProduct(int id) {
        if (products.containsKey(id)) {
            return products.get(id); // Return the product if found
        } else {
            System.err.println("Product with ID " + id + " not found.\n");
            return null;
        }
    }

    // Deletes a product from the stock by its ID.
    public void deleteProduct(int id) {
        if (products.remove(id) == null) { // Attempt to remove the product
            System.err.println("Cannot delete. Product with ID " + id + " not found.\n");
        } else {
            System.out.println("Product with ID " + id + " deleted.\n");
        }
    }

    // Retrieves and removes a product from the stock by its ID.
    public Product retrieveAndRemoveProduct(int productId) {
        return products.remove(productId); // This removes and returns the product
    }

    // Allows all the products in stock to be displayed
    public void displayAllProducts() {
        if (products.isEmpty()) {
            System.out.println("The stock is currently empty.");
        } else {
            System.out.println("Current Stock:\n");
            for (Product product : products.values()) {
                System.out.println(product.displayProductInfo());
            }
        }
    }

    // Getter for the products map (if needed)
    public Map<Integer, Product> getProducts() {
        return products;
    }
}
