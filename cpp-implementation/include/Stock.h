#ifndef STOCK_H
#define STOCK_H

#include "Product.h"
#include <map>
#include <memory>

using namespace std;

// Stock class represents a collection of products, identified by unique IDs.
class Stock {
private:
    // Products are stored in an map, allowing fast access by ID.
    map<int, unique_ptr<Product>> products; 

public:
    Stock() = default; // Default constructor

    // Method to add a new product to the stock.
    void addProduct(unique_ptr<Product> product);

    // Method to update an existing product in the stock.
    void updateProduct(int id, unique_ptr<Product> product);

    // Method to retrieve a product by its ID. Returns a pointer to the product.
    Product* getProduct(int id) const;

    // Method to delete a product from the stock by its ID.
    void deleteProduct(int id);

    unique_ptr<Product> retrieveAndRemoveProduct(int id);
};

#endif