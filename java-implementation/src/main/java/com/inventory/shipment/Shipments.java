package com.inventory.shipment;

import com.inventory.others.Packaging;
import com.inventory.others.Stock;
import com.inventory.products.Product;
import com.inventory.transport.Transport;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Shipments {

    private static int nextShipmentId = 0;
    private static Map<Integer, Shipments> allShipments = new HashMap<>();

    private ShipmentDetails details;
    private List<Product> products = new ArrayList<>();
    private Packaging packaging;
    private Transport transportMethod;

    //Enum containing all the possible shipment status
    public enum ShipmentStatus {
        CREATED, DISPATCHED, CANCELLED
    }

    // Constructor for the Shipments class.
    public Shipments(Packaging packaging, Transport transportMethod) {
        this.details = new ShipmentDetails(nextShipmentId++);
        this.packaging = packaging;
        this.transportMethod = transportMethod;
        this.details.setStatus(ShipmentStatus.CREATED);
        allShipments.put(this.details.getShipmentId(), this);
    }

    // Adds a product if the shipment has not been dispatched or cancelled.
    public void addProduct(Stock stock, int productId) {
        if (this.details.getStatus() == ShipmentStatus.CREATED) {
            Product product = stock.retrieveAndRemoveProduct(productId);
            if (product != null) {
                products.add(product);
            } else {
                System.err.println("Product with ID " + productId + " not found in stock.");
            }
        } else {
            System.err.println("Cannot add product. Shipment already dispatched or canceled.");
        }
    }

    // Removes a product if the shipment has not been dispatched or cancelled.
    public void removeProduct(int productId) {
        if (this.details.getStatus() == ShipmentStatus.CREATED) {
            products.removeIf(product -> product.getId() == productId);
        } else {
            System.err.println("Cannot remove product. Shipment already dispatched or canceled.");
        }
    }

    // Updates the transport method if the shipment has not been dispatched or cancelled.
    public void updateTransportMethod(Transport newTransportMethod) {
        if (this.details.getStatus() == ShipmentStatus.CREATED) {
            this.transportMethod = newTransportMethod;
        } else {
            System.err.println("Cannot update transport method. Shipment already dispatched or canceled.");
        }
    }

    // Dispatches the shipment giving a dispatch time and estimated delivery time
    public void dispatch() {
        if (this.details.getStatus() == ShipmentStatus.CREATED) {
            this.details.setStatus(ShipmentStatus.DISPATCHED);
            this.details.setDispatchTime(LocalDateTime.now());
            if (transportMethod != null) {
                double deliveryTimeInHours = transportMethod.calculateDeliveryTime(100); // Example distance
                this.details.setEstimatedDeliveryTime(this.details.getDispatchTime().plusHours((long) deliveryTimeInHours));
            } else {
                System.err.println("Transport method not set. Cannot calculate estimated delivery time.");
            }
        } else {
            System.err.println("Cannot dispatch. Shipment already dispatched or canceled.");
        }
    }

    // Cancels a shipment if it has not been dispatched or cancelled.
    public void cancel() {
        if (this.details.getStatus() == ShipmentStatus.CREATED) {
            this.details.setStatus(ShipmentStatus.CANCELLED);
        } else {
            System.err.println("Cannot cancel. Shipment already dispatched or canceled.");
        }
    }

    // The total cost based on all the costs from the product, transport and packaging classes
    public double calculateTotalCost() {
        double totalCost = packaging.calculateCost();
        if (transportMethod != null) {
            totalCost += transportMethod.calculateDeliveryCost(100); // Example distance
        }
        if (details.getDispatchTime() != null) { // Check if dispatchTime is not null
            int dispatchMonth = details.getDispatchTime().getMonthValue();
            for (Product product : products) {
                int volume = product.getVolume();
                double discount = product.calculateDiscount(volume, dispatchMonth);
                totalCost += (product.getPrice() * volume - discount);
            }
        }
        return totalCost;
    }

    // Displays all the products found in the shipment
    public static void displayProductsInShipment(int shipmentId) {
        Shipments shipment = allShipments.get(shipmentId);
        if (shipment != null) {
            System.out.println("Products in Shipment ID " + shipmentId + ":");
            for (Product product : shipment.products) {
                System.out.println(product.displayProductInfo());
            }
        } else {
            System.out.println("Shipment with ID " + shipmentId + " not found.");
        }
    }

    // Displays the shipment details
    public void displayShipmentDetails() {
        System.out.println("Shipment ID: " + details.getShipmentId());
        System.out.println("Status: " + details.getStatus());
        System.out.println("Packaging: " + packaging.getType() + ", " + packaging.getMaterial());
        System.out.println("Total Packaged: " + packaging.getCapacity());
        System.out.println("Transport Method: " + (transportMethod != null ? transportMethod.getTransportType() : "None"));
        System.out.println("Route: " + (transportMethod != null ? transportMethod.getRouteStages() : "None"));
        System.out.printf("Total Cost: €%.2f%n", calculateTotalCost());
        System.out.println("Dispatch Time: " + details.getDispatchTimeFormatted());
        System.out.println("Estimated Delivery Time: " + details.getEstimatedDeliveryTimeFormatted());
        System.out.println();
    }

    // Lists a summary of all the shipments
    public static void listAllShipments() {
        for (Map.Entry<Integer, Shipments> entry : allShipments.entrySet()) {
            System.out.println("Shipment ID: " + entry.getKey() + " - Status: " + entry.getValue().details.getStatus());
        }
    }
}
