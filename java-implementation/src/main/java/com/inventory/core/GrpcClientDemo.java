package com.inventory.core;

import com.inventory.proto.InventoryProtos.*;
import com.inventory.service.ServiceProtos.*;
import com.inventory.service.ShipmentPriceCalculatorGrpc;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import java.util.concurrent.TimeUnit;

public class GrpcClientDemo {
    
    public static void main(String[] args) throws Exception {
        // Create a channel to connect to the server
        ManagedChannel channel = ManagedChannelBuilder.forAddress("localhost", 50051)
            .usePlaintext()
            .build();
        
        try {
            // Create a blocking stub
            ShipmentPriceCalculatorGrpc.ShipmentPriceCalculatorBlockingStub stub = 
                ShipmentPriceCalculatorGrpc.newBlockingStub(channel);
            
            // Create sample data for testing
            System.out.println("Creating sample shipment data...");
            
            // Create a Books category
            Books books = Books.newBuilder()
                .setAuthor("Test Author")
                .setPublisher("Test Publisher")
                .setFiction(Fiction.newBuilder().setGenre("Sci-Fi").build())
                .build();
            
            // Create a product
            Product product = Product.newBuilder()
                .setId(1)
                .setName("Test Book")
                .setPrice(25.99)
                .setVolume(1)
                .setSupplier("Test Supplier")
                .setBooks(books)
                .build();
            
            // Create packaging
            Packaging packaging = Packaging.newBuilder()
                .setCapacity(10)
                .setMaterial("Cardboard")
                .setType("Box")
                .setMatcost(2)
                .setTypecost(3)
                .setPrice(5)
                .build();
            
            // Create transport method (Land transport)
            TransportProperty transportProp = TransportProperty.newBuilder()
                .setDistance(100.0)
                .setCost(0.15)
                .setPrice(15.0)
                .build();
            
            Land landTransport = Land.newBuilder()
                .setType(LandType.TRUCK)
                .setRoadStages("Highway -> Local")
                .setTransportProperty(transportProp)
                .build();
            
            Transport transport = Transport.newBuilder()
                .setLand(landTransport)
                .build();
            
            // Create a shipment
            Shipment shipment = Shipment.newBuilder()
                .setShipmentId(1)
                .addProducts(product)
                .setPackaging(packaging)
                .setTransportMethod(transport)
                .setStatus(ShipmentStatus.CREATED)
                .setTotalcost(0.0)  // Will be calculated by server
                .setDispatchTime("2024-01-01T10:00:00Z")
                .setEstimatedDeliveryTime("2024-01-03T15:00:00Z")
                .build();
            
            // Create the request
            CalculateShipmentPriceRequest request = CalculateShipmentPriceRequest.newBuilder()
                .addShipments(shipment)
                .build();
            
            System.out.println("Sending gRPC request to server...");
            System.out.println("Request contains:");
            System.out.println("- Product: " + product.getName() + " ($" + product.getPrice() + ")");
            System.out.println("- Packaging: " + packaging.getType() + " ($" + packaging.getPrice() + ")");
            System.out.println("- Transport: " + landTransport.getType() + " ($" + transportProp.getPrice() + ")");
            
            // Make the gRPC call
            CalculateShipmentPriceResponse response = stub.calculateShipmentPrice(request);
            
            System.out.println("\n=== gRPC Response Received ===");
            System.out.println("Total prices returned:");
            
            for (java.util.Map.Entry<Integer, Double> entry : response.getTotalPricesMap().entrySet()) {
                System.out.println("Shipment ID " + entry.getKey() + ": $" + String.format("%.2f", entry.getValue()));
            }
            
            // Verify the calculation manually
            double expectedTotal = (product.getPrice() * product.getVolume()) + packaging.getPrice() + transportProp.getPrice();
            System.out.println("\nExpected total: $" + String.format("%.2f", expectedTotal));
            
            Double actualTotal = response.getTotalPricesMap().get(1);
            if (actualTotal != null && Math.abs(actualTotal - expectedTotal) < 0.01) {
                System.out.println("SUCCESS: gRPC calculation is CORRECT!");
                System.out.println("SUCCESS: gRPC client-server communication is WORKING!");
            } else {
                System.out.println("ERROR: Calculation mismatch!");
                System.out.println("Expected: $" + expectedTotal + ", Got: $" + actualTotal);
            }
            
        } catch (Exception e) {
            System.err.println("gRPC call failed: " + e.getMessage());
            e.printStackTrace();
        } finally {
            // Shutdown the channel
            channel.shutdown().awaitTermination(5, TimeUnit.SECONDS);
        }
    }
}
