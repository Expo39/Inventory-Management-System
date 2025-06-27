package com.inventory.core;

import com.inventory.proto.InventoryProtos.*;
import com.inventory.service.ServiceProtos.*;
import com.inventory.service.ShipmentPriceCalculatorGrpc;
import io.grpc.Server;
import io.grpc.ServerBuilder;
import io.grpc.stub.StreamObserver;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class GrpcServer extends ShipmentPriceCalculatorGrpc.ShipmentPriceCalculatorImplBase {

    @Override
    public void calculateShipmentPrice(CalculateShipmentPriceRequest request,
                                     StreamObserver<CalculateShipmentPriceResponse> responseObserver) {
        Map<Integer, Double> totalPrices = new HashMap<>();
        
        for (Shipment shipment : request.getShipmentsList()) {
            double totalPrice = calculateShipmentCost(shipment);
            totalPrices.put(shipment.getShipmentId(), totalPrice);
        }
        
        CalculateShipmentPriceResponse response = CalculateShipmentPriceResponse.newBuilder()
            .putAllTotalPrices(totalPrices)
            .build();
        
        responseObserver.onNext(response);
        responseObserver.onCompleted();
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
    
    public static void main(String[] args) throws IOException, InterruptedException {
        Server server = ServerBuilder.forPort(50051)
            .addService(new GrpcServer())
            .build()
            .start();
        
        System.out.println("Server started, listening on port 50051");
        
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.err.println("*** shutting down gRPC server since JVM is shutting down");
            server.shutdown();
            System.err.println("*** server shut down");
        }));
        
        server.awaitTermination();
    }
}
