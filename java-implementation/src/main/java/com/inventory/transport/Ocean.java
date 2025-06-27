package com.inventory.transport;

import com.inventory.transport.TransportTypes.OceanType;
import static com.inventory.transport.TransportTypes.OceanTransportProperties;
import static com.inventory.transport.TransportTypes.OceanRoutes;

// Represent the properties of ocean transport
public class Ocean extends Transport {
    private OceanType type; // The type of ocean transport
    private String seaRoutes; // Predefined sea routes for this transport type 

    // Constructs an Ocean transport instance with properties based on the properties
    public Ocean(OceanType type) {

        // Call the base class constructor with speed and cost
        super(OceanTransportProperties.get(type).getFirst(), OceanTransportProperties.get(type).getSecond());
        this.type = type;
        this.seaRoutes = OceanRoutes.get(type);
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

    // Return the predefined sea routes for this vessel
    @Override
    public String getRouteStages() {
        return seaRoutes;
    }

    // Convert the enum to a legible string
    private String toString(OceanType type) {
        switch (type) {
            case Freighter: return "Freighter";
            case SmallShip: return "SmallShip";
            case Boat: return "Boat";
            default: return "Unknown";
        }
    }
}
