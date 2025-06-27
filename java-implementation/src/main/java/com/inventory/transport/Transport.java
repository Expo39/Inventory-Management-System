package com.inventory.transport;

// Abstract base class for all transportation methods. 
public abstract class Transport {
    
    protected double speed; // Transportation speed in km/h
    protected double costPerKm; // Transportation cost per kilometer

    public Transport(double speed, double costPerKm) {
        this.speed = speed;
        this.costPerKm = costPerKm;
    }

    public abstract String getTransportType();
    public abstract String getRouteStages();
    public abstract double calculateDeliveryTime(double distance);
    public abstract double calculateDeliveryCost(double distance);
}
