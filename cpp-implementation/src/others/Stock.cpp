#include "Others.ih"

// Adds a new product to the stock.
void Stock::addProduct(unique_ptr<Product> product) {
    int id = product->getId(); // Get ID of the product

    // Check if a product with this ID already exists in the stock
    if (products.find(id) != products.end()) {
        cerr << "Cannot order product. Product with ID " << id << " is already in use.\n\n";
    } else {
        products[id] = move(product); // Add the product to the stock
        cout << "Product with ID " << id << " ordered from supplier.\n";
    }
}

// Updates an existing product in the stock
void Stock::updateProduct(int id, unique_ptr<Product> product) {
    auto it = products.find(id); // Find the product by its ID

    if (it != products.end()) {
        products[id] = move(product); // Replace the existing product with the new one
        cout << "Product with ID " << id << " updated.\n\n";
    } else {
        cerr << "Cannot update. Product with ID " << id << " not found.\n\n";
    }
}

// Retrieves a product by its ID. Returns a pointer to the product or nullptr if not found.
Product* Stock::getProduct(int id) const {
    auto it = products.find(id); // Find the product by its ID

    if (it != products.end()) {
        return it->second.get(); // Return the product if found
    } else {
        cerr << "Product with ID " << id << " not found.\n\n";
        return nullptr;
    }
}

// Deletes a product from the stock by its ID.
void Stock::deleteProduct(int id) {
    if (products.erase(id) == 0) { // Attempt to erase the product
        cerr << "Cannot delete. Product with ID " << id << " not found.\n\n";
    } else {
        cout << "Product with ID " << id << " deleted.\n\n";
    }
}

std::unique_ptr<Product> Stock::retrieveAndRemoveProduct(int id) {
    auto it = products.find(id);
    if (it != products.end()) {
        std::unique_ptr<Product> product = std::move(it->second); // Move the product out of the map
        products.erase(it); // Erase the product from the map
        return product; // Return the moved product
    } else {
        std::cerr << "Product with ID " << id << " not found in stock.\n";
        return nullptr;
    }
}
