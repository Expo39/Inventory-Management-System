package com.inventory.others;

import java.util.Map;

// Represents packaging with specific attributes
public class Packaging {
    private int capacity;
    private String material;
    private String type;

    // Static maps to hold the cost of different materials and types of packaging
    private static final Map<String, Double> materialCosts = Map.of(
        "paper", 0.10,
        "cardboard", 0.25,
        "plastic", 0.15
    );

    private static final Map<String, Double> typeCosts = Map.of(
        "box", 0.50,
        "envelope", 0.20,
        "crate", 0.75
    );

    // Constructor to initialise packaging with capacity, material, and type
    public Packaging(int capacity, String material, String type) {
        this.capacity = capacity;
        this.material = material;
        this.type = type;
    }

    // Calculate the total cost of the packaging based on its material and type
    public double calculateCost() {
        double materialCost = materialCosts.get(material); // Cost based on the material
        double typeCost = typeCosts.get(type); // Cost based on the type
        return materialCost + typeCost; // Total cost is the sum of material and type costs
    }

    // Getters for packaging properties
    public String getType() {
        return type;
    }

    public String getMaterial() {
        return material;
    }

    public int getCapacity() {
        return capacity;
    }
}
