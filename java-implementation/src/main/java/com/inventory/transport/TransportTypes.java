package com.inventory.transport;

import java.util.Map;

// Definitions of the various types of transportation available
public class TransportTypes {
    // Enumerations for different types of land transport
    public enum LandType {
        Truck, Car, Pickup
    }

    // Enumerations for different types of ocean transport
    public enum OceanType {
        Freighter, SmallShip, Boat
    }

    // Enumerations for different types of air transport
    public enum AirType {
        CargoPlane, CommercialPlane, Helicopter
    }

    // Maps for transport properties of land transport types
    public static final Map<LandType, Pair<Double, Double>> LandTransportProperties = Map.of(
        LandType.Truck, new Pair<>(60.0, 0.8),
        LandType.Car, new Pair<>(90.0, 0.5),
        LandType.Pickup, new Pair<>(70.0, 0.7)
    );

    // Maps for transport properties of ocean transport types
    public static final Map<OceanType, Pair<Double, Double>> OceanTransportProperties = Map.of(
        OceanType.Freighter, new Pair<>(30.0, 2.0),
        OceanType.SmallShip, new Pair<>(40.0, 1.5),
        OceanType.Boat, new Pair<>(20.0, 1.0)
    );

    // Maps for transport properties of air transport types
    public static final Map<AirType, Pair<Double, Double>> AirTransportProperties = Map.of(
        AirType.CargoPlane, new Pair<>(800.0, 10.0),
        AirType.CommercialPlane, new Pair<>(900.0, 12.0),
        AirType.Helicopter, new Pair<>(300.0, 15.0)
    );

    // Maps for predefined routes for each land transport type
    public static final Map<LandType, String> LandRoutes = Map.of(
        LandType.Truck, "Highway A1 -> Highway B2 -> Local Road C3",
        LandType.Car, "Main Street -> Bridge D4 -> Avenue E5",
        LandType.Pickup, "Dirt Track F6 -> Mountain Pass G7 -> Valley Road H8"
    );

    // Maps for predefined sea routes for each ocean transport type
    public static final Map<OceanType, String> OceanRoutes = Map.of(
        OceanType.Freighter, "Sea Lane M -> Sea Lane N -> Port O",
        OceanType.SmallShip, "Coastal Path P -> Island Q -> Dock R",
        OceanType.Boat, "River S -> Canal T -> Marina U"
    );

    // Maps for predefined air routes for each air transport type
    public static final Map<AirType, String> AirRoutes = Map.of(
        AirType.CargoPlane, "Airspace X -> Airspace Y -> Airspace Z",
        AirType.CommercialPlane, "Flight Path V -> Flight Path W -> Airport AA",
        AirType.Helicopter, "Heli Route BB -> Heli Route CC -> Heliport DD"
    );

    
    // Used to store two related values
    public static class Pair<K, V> {
        private K first;
        private V second;

        public Pair(K first, V second) {
            this.first = first;
            this.second = second;
        }

        public K getFirst() { return first; }
        public V getSecond() { return second; }
    }
}
