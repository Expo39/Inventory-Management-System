#include <iostream>
#include "Stock.h"
#include "Shipments.h"
#include "ShipmentsDP.h" // Include the ShipmentsDP header
#include "Transport.h"
#include "TransportFP.h"
#include "Stationary.h"
#include "Clothing.h"       
#include "Books.h"               
#include "Electronics.h"    
#include "PC_Games.h"  
#include "ProductFP.h"  

using namespace std;

// Function prototypes
void createProducts(Stock& stock);
void testStockOperations(Stock& stock);
void testShipmentOperations(Stock& stock);

int main() {
    Stock stock;

    createProducts(stock);
    // testStockOperations(stock); 
     testShipmentOperations(stock);

}

void createProducts(Stock& stock) {
    stock.addProduct(ProductFP::createProduct(ProductType::Pen, 1, "Fancy Pen", 9.99, 100, {"Plastic", "Blue Ink"}, "PenSupplier"));
    stock.addProduct(ProductFP::createProduct(ProductType::Dress, 2, "Elegant Dress", 59.99, 50, {"Medium", "Cotton", "Evening Wear"}, "DressSupplier"));
    stock.addProduct(ProductFP::createProduct(ProductType::FictionBook, 3, "Adventure Tales", 19.99, 200, {"J.K. Rowling", "Bloomsbury", "Adventure"}, "BookSupplier"));
    stock.addProduct(ProductFP::createProduct(ProductType::Laptop, 4, "UltraBook Pro", 999.99, 30, {"TechBrand", "Windows", "2"}, "LaptopSupplier"));
    stock.addProduct(ProductFP::createProduct(ProductType::ActionGame, 5, "Space Wars", 49.99, 100, {"Action", "18", "true"}, "GameSupplier"));
    stock.addProduct(ProductFP::createProduct(ProductType::NonFictionBook, 6, "World History", 29.99, 150, {"S. Williams", "Academic Press", "History"}, "BookSupplier"));
}


void testStockOperations(Stock& stock) {
    // Retrieve and display product info for product with ID 2
    Product* product = stock.getProduct(2);
    if (product) {
        cout << "\nProduct Info (Before Update):\n" << product->displayProductInfo() << "\n\n";
    }

    // Update product with ID 2
    auto updatedProduct = ProductFP::createProduct(ProductType::Dress, 2, "Updated Elegant Dress", 75.99, 40, {"Small", "Silk", "Casual Wear"}, "DressSupplier");
    stock.updateProduct(2, move(updatedProduct));

    // Attempt to display updated product info
    product = stock.getProduct(2);
    if (product) {
        cout << "Product Info (After Update):\n" << product->displayProductInfo() << "\n\n";
    }

    // Delete product with ID 2
    stock.deleteProduct(2);

    // Try to display info of deleted product
    product = stock.getProduct(2);

     // Attempt to update a non-existing product
    auto nonExistingProduct = ProductFP::createProduct(ProductType::FictionBook, 7, "Imaginary Book", 45.99, 15, {"No Author", "No Publisher", "Sci-Fi"}, "BookSupplier");
    stock.updateProduct(7, move(nonExistingProduct));

}

void testShipmentOperations(Stock& stock) {
    // Create transport objects using TransportFP
    auto landTransport = TransportFP::createTransport(TransportType::Land, {"Truck"});
    auto oceanTransport = TransportFP::createTransport(TransportType::Ocean, {"Freighter"});
    auto airTransport = TransportFP::createTransport(TransportType::Air, {"CargoPlane"});

    // Create packaging types
    Packaging boxPackaging(10, "cardboard", "box");
    Packaging envelopePackaging(5, "paper", "envelope");
    Packaging cratePackaging(15, "plastic", "crate");

    // Create shipments
    Shipment landShipment(boxPackaging, move(landTransport));
    Shipment oceanShipment(envelopePackaging, move(oceanTransport));
    Shipment airShipment(cratePackaging, move(airTransport));

    // Land shipment gets one product (ID: 1)
    landShipment.addProduct(stock, 1); // Updated to retrieve from stock

    // Ocean shipment gets two products (ID: 2 and ID: 3)
    oceanShipment.addProduct(stock, 2);
    oceanShipment.addProduct(stock, 3);

    // Air shipment gets one product (ID: 4)
    airShipment.addProduct(stock, 4);

    // // Update transport method for the land shipment using TransportFP
    // unique_ptr<Transport> updatedLandTransport = TransportFP::createTransport(TransportType::Land, {"Car"});
    // landShipment.updateTransportMethod(move(updatedLandTransport));

    // // Display initial shipment details
    // cout << "\n";
    // landShipment.displayShipmentDetails();
    // oceanShipment.displayShipmentDetails();
    // airShipment.displayShipmentDetails();

    // Land shipment gets one product (ID: 1)
    landShipment.addProduct(stock, 1); // Updated to retrieve from stock

    cout << "Original Shipment: \n";
    landShipment.displayShipmentDetails();

    // Apply a 10% discount using the DiscountDecorator

    // Assuming 'routeClosed' is a boolean indicating whether the route is closed
    Decorator decoratorshipment(&landShipment, 0.10, true);

    cout << "Modified Shipment: \n";
    decoratorshipment.displayShipmentDetails();

    // Shipment::displayProductsInShipment(oceanShipment.getShipmentId());

    // // Remove a product from the ocean shipment
    // oceanShipment.removeProduct(2); // Assuming product with ID 2 exists

    // Shipment::displayProductsInShipment(oceanShipment.getShipmentId());

    // // Dispatch land and air shipments
    // landShipment.dispatch();
    // airShipment.dispatch();

    // // Cancel the ocean shipment
    // oceanShipment.cancel();

    // // Cannot be modified/cancelled since it has already been dispatched
    // airShipment.addProduct(stock, 4); // Add product with ID 4 to air shipment

    // // Cannot be modified/cancelled since it has already been dispatched
    // airShipment.cancel();

    // // Display shipment details after dispatch and cancellations
    // cout << "\n";
    // landShipment.displayShipmentDetails();
    // oceanShipment.displayShipmentDetails();
    // airShipment.displayShipmentDetails();

    // cout << "\nListing all shipments:\n";
    // Shipment::listAllShipments();
}
