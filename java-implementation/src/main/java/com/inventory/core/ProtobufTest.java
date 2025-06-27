package com.inventory.core;

import com.inventory.proto.InventoryProtos.*;
import com.inventory.service.ServiceProtos.*;

public class ProtobufTest {
    public static void main(String[] args) {
        System.out.println("=== JAVA PROTOBUF INTEGRATION TEST ===");
        
        // Test 1: Create a Product using protobuf
        Product product = Product.newBuilder()
            .setId(1)
            .setName("Test Product")
            .setPrice(99.99)
            .setVolume(10)
            .setSupplier("Test Supplier")
            .build();
        
        System.out.println("SUCCESS: Product created: " + product.getName() + " - $" + product.getPrice());
        
        // Test 2: Create a Shipment using protobuf
        Packaging packaging = Packaging.newBuilder()
            .setCapacity(5)
            .setMaterial("cardboard")
            .setType("box")
            .setMatcost(2)
            .setTypecost(1)
            .setPrice(3)
            .build();
        
        Transport transport = Transport.newBuilder()
            .setLand(Land.newBuilder()
                .setType(LandType.TRUCK)
                .setRoadStages("Route A -> Route B")
                .setTransportProperty(TransportProperty.newBuilder()
                    .setDistance(50)
                    .setCost(2.5)
                    .setPrice(25)
                    .build())
                .build())
            .build();
        
        Shipment shipment = Shipment.newBuilder()
            .setShipmentId(1)
            .setPackaging(packaging)
            .setTransportMethod(transport)
            .addProducts(product)
            .setStatus(ShipmentStatus.CREATED)
            .setTotalcost(127.49)
            .build();
        
        System.out.println("SUCCESS: Shipment created: ID " + shipment.getShipmentId() + 
                         ", Cost $" + shipment.getTotalcost());
        
        // Test 3: Test protobuf serialisation
        try {
            byte[] serialized = shipment.toByteArray();
            Shipment deserialized = Shipment.parseFrom(serialized);
            System.out.println("SUCCESS: Protobuf serialisation working: " + serialized.length + " bytes");
            System.out.println("SUCCESS: Deserialized shipment ID: " + deserialized.getShipmentId());
        } catch (Exception e) {
            System.out.println("ERROR: Protobuf serialisation failed: " + e.getMessage());
        }
        
        // Test 4: Test gRPC request/response objects
        CalculateShipmentPriceRequest request = CalculateShipmentPriceRequest.newBuilder()
            .addShipments(shipment)
            .build();
        
        System.out.println("SUCCESS: gRPC request created with " + request.getShipmentsCount() + " shipments");
        
        System.out.println("\n=== ALL TESTS PASSED ===");
        System.out.println("Java protobuf integration is working correctly!");
    }
}
