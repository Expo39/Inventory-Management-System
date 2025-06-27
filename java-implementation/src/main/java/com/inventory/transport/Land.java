package com.inventory.transport;

import com.inventory.transport.TransportTypes.LandType;
import static com.inventory.transport.TransportTypes.LandTransportProperties;
import static com.inventory.transport.TransportTypes.LandRoutes;

// Represent the properties of land transport
public class Land extends Transport {
    private LandType type; // The type of land transport
    private String roadStages; // The predefined route stages for a specific land transport type

    // Constructs a Land transport instance with properties based on the properties
    public Land(LandType type) {

        // Call the base class constructor with speed and cost
        super(LandTransportProperties.get(type).getFirst(), LandTransportProperties.get(type).getSecond());
        this.type = type;
        this.roadStages = LandRoutes.get(type);
    }

    // Calculate delivery time
    @Override
    public double calculateDeliveryTime(double distance) {
        return distance / speed;
    }

    // Calculate the delivery cost
    @Override
    public double calculateDeliveryCost(double distance) {
        return distance * costPerKm;
    }

    // Return a string representation of the transport type
    @Override
    public String getTransportType() {
        return toString(type);
    }

    // Return the predefined land routes for this vessel
    @Override
    public String getRouteStages() {
        return roadStages;
    }

    // Converts the enum to a legible string
    private String toString(LandType type) {
        switch (type) {
            case Truck: return "Truck";
            case Car: return "Car";
            case Pickup: return "Pickup";
            default: return "Unknown";
        }
    }
}
