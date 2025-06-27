package com.inventory.core;

import com.inventory.others.Packaging;
import com.inventory.others.Stock;
import com.inventory.products.Product;
import com.inventory.products.stationary.Pens;
import com.inventory.products.clothing.Dresses;
import com.inventory.products.books.Fiction;
import com.inventory.products.electronics.Laptops;
import com.inventory.products.pcgames.Action;
import com.inventory.products.books.NonFiction;
import com.inventory.shipment.Shipments;
import com.inventory.transport.Land;
import com.inventory.transport.Ocean;
import com.inventory.transport.Air;
import com.inventory.transport.Transport;
import com.inventory.transport.TransportTypes;

public class CLI {

    private static Stock stock = new Stock(); // Create a stock to manage inventory

    public static void main(String[] args) {
        createProducts(); // Add initial products to the stock
        testStockOperations(); // Perform operations on the stock and display results
        testShipmentOperations(); // Perform operations on shipments and display results
    }

    // Creates sample products and adds them to the stock
    private static void createProducts() {
        
        stock.addProduct(new Pens(1, "Fancy Pen", 9.99, 100, "Plastic", "Blue Ink", "PenSupplier"));
        stock.addProduct(new Dresses(2, "Elegant Dress", 59.99, 50, "Medium", "Cotton", "Evening Wear", "Emerald Clothing"));
        stock.addProduct(new Fiction(3, "Adventure Tales", 19.99, 200, "J.K. Rowling", "Bloomsbury", "Adventure", "Diamond Libraries"));
        stock.addProduct(new Laptops(4, "UltraBook Pro", 999.99, 30, "TechBrand", "Windows", 2, "The IT Shop"));
        stock.addProduct(new Action(5, "Space Wars", 49.99, 100, "Action", 18, true, "COD Games"));
        stock.addProduct(new NonFiction(6, "World History", 29.99, 150, "S. Williams", "Academic Press", "History", "The library"));
        System.out.println("Products added to stock.");
    }

    // Tests various stock operations like getting, updating, and deleting products
    private static void testStockOperations() {

        stock.displayAllProducts();

        // Get a product by ID and display its information before update
        Product product = stock.getProduct(2);
        if (product != null) {
            System.out.println("\nProduct Info (Before Update):\n" + product.displayProductInfo());
        }

        // Update product information and display the updated info
        stock.updateProduct(2, new Dresses(2, "Updated Elegant Dress", 75.99, 40, "Small", "Silk", "Casual Wear", "Emerald Clothing"));

        product = stock.getProduct(2);
        if (product != null) {
            System.out.println("Product Info (After Update):\n" + product.displayProductInfo());
        }

        // Delete the product and verify it's no longer available
        stock.deleteProduct(2);
        product = stock.getProduct(2);
        if (product == null) {
            System.out.println("Product with ID 2 deleted.");
        }
    }

    // Tests various shipment operations and displays shipment details
    private static void testShipmentOperations() {

        // Create different types of transport
        Transport landTransport = new Land(TransportTypes.LandType.Truck);
        Transport oceanTransport = new Ocean(TransportTypes.OceanType.Freighter);
        Transport airTransport = new Air(TransportTypes.AirType.CargoPlane);

        // Create different types of packaging
        Packaging boxPackaging = new Packaging(10, "cardboard", "box");
        Packaging envelopePackaging = new Packaging(5, "paper", "envelope");
        Packaging cratePackaging = new Packaging(15, "plastic", "crate");

        // Create shipments with the transport and packaging
        Shipments landShipment = new Shipments(boxPackaging, landTransport);
        Shipments oceanShipment = new Shipments(envelopePackaging, oceanTransport);
        Shipments airShipment = new Shipments(cratePackaging, airTransport);

        // Add products to the shipment from stock
        landShipment.addProduct(stock, 1); // Add product with ID 1 to land shipment
        oceanShipment.addProduct(stock, 3); // Add product with ID 3 to ocean shipment
        airShipment.addProduct(stock, 4); // Add product with ID 4 to air shipment

        // Update transport method
        landShipment.updateTransportMethod(new Land(TransportTypes.LandType.Car));

        // Display shipments
        System.out.println("Land Shipment Details:");
        landShipment.displayShipmentDetails();
        System.out.println("Ocean Shipment Details:");
        oceanShipment.displayShipmentDetails();
        System.out.println("Air Shipment Details:");
        airShipment.displayShipmentDetails();

        // Demonstration of products in shipment before and after deletion of product
        System.out.println("\nDisplaying Products in Shipment ID 0 (before deletion):");
        Shipments.displayProductsInShipment(0);

        // Remove Product
        oceanShipment.removeProduct(3);

        // Dispatch shipments
        landShipment.dispatch();
        airShipment.dispatch();
        oceanShipment.cancel();

        // Since shipment is dispatched, transport method cannot be updated
        landShipment.updateTransportMethod(new Land(TransportTypes.LandType.Truck));
        
        System.out.println("\nDisplaying Products in Shipment ID 1: (After deletion)");
        Shipments.displayProductsInShipment(1);

        // Display final details of all shipments
        System.out.println("\nFinal Shipment Details:");
        landShipment.displayShipmentDetails();
        oceanShipment.displayShipmentDetails();
        airShipment.displayShipmentDetails();

        // Displays a simplified list of all shipments
        System.out.println("\nListing all shipments:");
        Shipments.listAllShipments();
     }
}
