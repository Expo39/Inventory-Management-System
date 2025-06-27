package com.inventory.core;

import com.inventory.proto.InventoryProtos.*;
import com.inventory.service.ServiceProtos.*;
import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class InventoryManagementSystem {

    private Stock stock;
    private AllShipments allShipments;
    private static final String STATE_FILE = "app_state.bin";

    public InventoryManagementSystem() {
        this.stock = Stock.newBuilder().build();
        this.allShipments = AllShipments.newBuilder().build();
    }

    public static void main(String[] args) {
        InventoryManagementSystem system = new InventoryManagementSystem();
        
        // Load previous state
        system.loadState();
        
        // Create products
        system.createProducts();
        
        // Create and dispatch shipments
        system.createAndDispatchShipments();
        
        // Display shipment details
        system.displayAllShipments();
        
        // Save current state
        system.saveState();
    }

    private void createProducts() {
        Map<Integer, Product> products = new HashMap<>(stock.getProductsMap());

        // Create a Pen product
        Product penProduct = Product.newBuilder()
            .setId(1)
            .setName("Fancy Pen")
            .setPrice(9.99)
            .setVolume(100)
            .setSupplier("PenSupplier")
            .setStationary(Stationary.newBuilder()
                .setMaterial("Plastic")
                .setPens(Pens.newBuilder()
                    .setInkType("Blue Ink")
                    .build())
                .build())
            .build();
        products.put(1, penProduct);

        // Create a Dress product
        Product dressProduct = Product.newBuilder()
            .setId(2)
            .setName("Elegant Dress")
            .setPrice(59.99)
            .setVolume(50)
            .setSupplier("DressSupplier")
            .setClothing(Clothing.newBuilder()
                .setSize("Medium")
                .setMaterial("Cotton")
                .setDresses(Dresses.newBuilder()
                    .setType("Evening Wear")
                    .build())
                .build())
            .build();
        products.put(2, dressProduct);

        // Create a Guitar product
        Product guitarProduct = Product.newBuilder()
            .setId(3)
            .setName("Classic Acoustic Guitar")
            .setPrice(199.99)
            .setVolume(20)
            .setSupplier("GuitarSupplier")
            .setGuitars(Guitars.newBuilder()
                .setMaterial("Wood")
                .setStringCount(6)
                .setAcoustic(Acoustic.newBuilder()
                    .setHasPickup(true)
                    .build())
                .build())
            .build();
        products.put(3, guitarProduct);

        this.stock = Stock.newBuilder()
            .putAllProducts(products)
            .build();

        System.out.println("Products created and added to stock.");
    }

    private void createAndDispatchShipments() {
        Map<Integer, Shipment> shipments = new HashMap<>(allShipments.getShipmentsMap());

        // Create first shipment
        Packaging firstPackaging = Packaging.newBuilder()
            .setCapacity(10)
            .setMaterial("cardboard")
            .setType("box")
            .setMatcost(5)
            .setTypecost(7)
            .setPrice(12)
            .build();

        Transport firstTransport = Transport.newBuilder()
            .setLand(Land.newBuilder()
                .setType(LandType.TRUCK)
                .setRoadStages("Highway A1 -> Highway B2 -> Local Road C3")
                .setTransportProperty(TransportProperty.newBuilder()
                    .setDistance(100)
                    .setCost(2.0)
                    .setPrice(200)
                    .build())
                .build())
            .build();

        Shipment.Builder firstShipmentBuilder = Shipment.newBuilder()
            .setShipmentId(1)
            .setPackaging(firstPackaging)
            .setTransportMethod(firstTransport)
            .addProducts(stock.getProductsMap().get(1))
            .addProducts(stock.getProductsMap().get(2))
            .setStatus(ShipmentStatus.DISPATCHED)
            .setDispatchTime("5th January")
            .setEstimatedDeliveryTime("6th January");

        // Calculate cost for the shipment without totalcost and then set it
        Shipment tempFirstShipment = firstShipmentBuilder.setTotalcost(0.0).build();
        double firstShipmentCost = calculateShipmentCost(tempFirstShipment);
        Shipment firstShipment = firstShipmentBuilder.setTotalcost(firstShipmentCost).build();

        shipments.put(1, firstShipment);

        // Create second shipment
        Packaging secondPackaging = Packaging.newBuilder()
            .setCapacity(15)
            .setMaterial("plastic")
            .setType("crate")
            .setMatcost(3)
            .setTypecost(1)
            .setPrice(4)
            .build();

        Transport secondTransport = Transport.newBuilder()
            .setOcean(Ocean.newBuilder()
                .setType(OceanType.FREIGHTER)
                .setSeaRoutes("Sea Lane M -> Sea Lane N -> Port O")
                .setTransportProperty(TransportProperty.newBuilder()
                    .setDistance(230)
                    .setCost(5.2)
                    .setPrice(1196)
                    .build())
                .build())
            .build();

        Shipment.Builder secondShipmentBuilder = Shipment.newBuilder()
            .setShipmentId(2)
            .setPackaging(secondPackaging)
            .setTransportMethod(secondTransport)
            .addProducts(stock.getProductsMap().get(3))
            .setStatus(ShipmentStatus.CREATED)
            .setDispatchTime("Not Dispatched")
            .setEstimatedDeliveryTime("Not Dispatched");

        // Calculate cost for the shipment without totalcost and then set it
        Shipment tempSecondShipment = secondShipmentBuilder.setTotalcost(0.0).build();
        double secondShipmentCost = calculateShipmentCost(tempSecondShipment);
        Shipment secondShipment = secondShipmentBuilder.setTotalcost(secondShipmentCost).build();

        shipments.put(2, secondShipment);

        this.allShipments = AllShipments.newBuilder()
            .putAllShipments(shipments)
            .build();

        System.out.println("Shipments created and processed.");
    }

    private double calculateShipmentCost(Shipment shipment) {
        double totalCost = 0.0;
        
        // Add product costs
        for (Product product : shipment.getProductsList()) {
            totalCost += product.getPrice() * product.getVolume();
        }
        
        // Add packaging cost
        totalCost += shipment.getPackaging().getPrice();
        
        // Add transport cost
        if (shipment.hasTransportMethod()) {
            Transport transport = shipment.getTransportMethod();
            if (transport.hasLand()) {
                totalCost += transport.getLand().getTransportProperty().getPrice();
            } else if (transport.hasOcean()) {
                totalCost += transport.getOcean().getTransportProperty().getPrice();
            } else if (transport.hasAir()) {
                totalCost += transport.getAir().getTransportProperty().getPrice();
            }
        }
        
        return totalCost;
    }

    private void displayAllShipments() {
        System.out.println("\n=== SHIPMENT DETAILS ===");
        for (Map.Entry<Integer, Shipment> entry : allShipments.getShipmentsMap().entrySet()) {
            displayShipmentDetails(entry.getValue());
            System.out.println();
        }
    }

    private void displayShipmentDetails(Shipment shipment) {
        System.out.println("Shipment ID: " + shipment.getShipmentId());
        System.out.println("Status: " + shipment.getStatus());
        System.out.println("Total Cost: $" + shipment.getTotalcost());
        System.out.println("Dispatch Time: " + shipment.getDispatchTime());
        System.out.println("Estimated Delivery: " + shipment.getEstimatedDeliveryTime());
        
        // Display packaging
        Packaging packaging = shipment.getPackaging();
        System.out.println("Packaging: " + packaging.getType() + " (" + 
                         packaging.getMaterial() + "), Capacity: " + packaging.getCapacity());
        
        // Display transport
        Transport transport = shipment.getTransportMethod();
        if (transport.hasLand()) {
            System.out.println("Transport: Land - " + transport.getLand().getType() + 
                             " via " + transport.getLand().getRoadStages());
        } else if (transport.hasOcean()) {
            System.out.println("Transport: Ocean - " + transport.getOcean().getType() + 
                             " via " + transport.getOcean().getSeaRoutes());
        } else if (transport.hasAir()) {
            System.out.println("Transport: Air - " + transport.getAir().getType() + 
                             " via " + transport.getAir().getAirRoutes());
        }
        
        // Display products
        System.out.println("Products:");
        for (Product product : shipment.getProductsList()) {
            displayProductDetails(product);
        }
    }

    private void displayProductDetails(Product product) {
        System.out.println("  - " + product.getName() + " (ID: " + product.getId() + 
                         ") - $" + product.getPrice() + ", Volume: " + product.getVolume() + 
                         ", Supplier: " + product.getSupplier());
        
        if (product.hasStationary()) {
            Stationary stationary = product.getStationary();
            System.out.println("    Stationary: " + stationary.getMaterial());
            if (stationary.hasPens()) {
                System.out.println("      Pen - Ink: " + stationary.getPens().getInkType());
            }
        } else if (product.hasClothing()) {
            Clothing clothing = product.getClothing();
            System.out.println("    Clothing: Size " + clothing.getSize() + ", " + clothing.getMaterial());
            if (clothing.hasDresses()) {
                System.out.println("      Dress - Type: " + clothing.getDresses().getType());
            }
        } else if (product.hasGuitars()) {
            Guitars guitars = product.getGuitars();
            System.out.println("    Guitar: " + guitars.getMaterial() + ", " + guitars.getStringCount() + " strings");
            if (guitars.hasAcoustic()) {
                System.out.println("      Acoustic - Has Pickup: " + guitars.getAcoustic().getHasPickup());
            }
        }
    }

    private void saveState() {
        try (FileOutputStream fos = new FileOutputStream(STATE_FILE)) {
            stock.writeTo(fos);
            allShipments.writeTo(fos);
            System.out.println("State saved to " + STATE_FILE);
        } catch (IOException e) {
            System.err.println("Error saving state: " + e.getMessage());
        }
    }

    private void loadState() {
        File file = new File(STATE_FILE);
        if (!file.exists()) {
            System.out.println("No previous state file found. Starting fresh.");
            return;
        }
        
        try (FileInputStream fis = new FileInputStream(file)) {
            this.stock = Stock.parseFrom(fis);
            this.allShipments = AllShipments.parseFrom(fis);
            System.out.println("Previous state loaded from " + STATE_FILE);
        } catch (IOException e) {
            System.err.println("Error loading state: " + e.getMessage());
            // Initialise empty state on error
            this.stock = Stock.newBuilder().build();
            this.allShipments = AllShipments.newBuilder().build();
        }
    }
}
