package com.inventory.transport;

import com.inventory.transport.TransportTypes.AirType;
import static com.inventory.transport.TransportTypes.AirTransportProperties;
import static com.inventory.transport.TransportTypes.AirRoutes;

// Represent the properties of air transport
public class Air extends Transport {
    private AirType type;
    private String airRoutes;

    // Constructs an Air transport instance with properties based on the properties
    public Air(AirType type) {

         // Call the base class constructor with speed and cost
        super(AirTransportProperties.get(type).getFirst(), AirTransportProperties.get(type).getSecond());
        this.type = type;
        this.airRoutes = AirRoutes.get(type);
    }

    // Calculates delivery time
    @Override
    public double calculateDeliveryTime(double distance) {
        return distance / speed;
    }

    // Calculates delivery cost
    @Override
    public double calculateDeliveryCost(double distance) {
        return distance * costPerKm;
    }

    // Retrieves the transport type
    @Override
    public String getTransportType() {
        return toString(type);
    }

    // Returns the predetermined stages of a route based on the transport type
    @Override
    public String getRouteStages() {
        return airRoutes;
    }

    // Converts the enum to a legible string
    private String toString(AirType type) {
        switch (type) {
            case CargoPlane: return "CargoPlane";
            case CommercialPlane: return "CommercialPlane";
            case Helicopter: return "Helicopter";
            default: return "Unknown";
        }
    }
}
