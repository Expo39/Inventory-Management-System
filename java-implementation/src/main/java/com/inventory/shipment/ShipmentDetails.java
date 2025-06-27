package com.inventory.shipment;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class ShipmentDetails {
    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    private int shipmentId;
    private Shipments.ShipmentStatus status;
    private LocalDateTime dispatchTime;
    private LocalDateTime estimatedDeliveryTime;

    // Constructor
    public ShipmentDetails(int shipmentId) {
        this.shipmentId = shipmentId;
    }

    // Getters and setters
    public int getShipmentId() {
        return shipmentId;
    }

    public Shipments.ShipmentStatus getStatus() {
        return status;
    }

    public void setStatus(Shipments.ShipmentStatus status) {
        this.status = status;
    }

    public String getDispatchTimeFormatted() {
        return dispatchTime != null ? dispatchTime.format(formatter) : "Not dispatched";
    }

    public LocalDateTime getDispatchTime() {
        return dispatchTime;
    }

    public void setDispatchTime(LocalDateTime dispatchTime) {
        this.dispatchTime = dispatchTime;
    }

    public String getEstimatedDeliveryTimeFormatted() {
        return estimatedDeliveryTime != null ? estimatedDeliveryTime.format(formatter) : "Not dispatched";
    }

    public LocalDateTime getEstimatedDeliveryTime() {
        return estimatedDeliveryTime;
    }

    public void setEstimatedDeliveryTime(LocalDateTime estimatedDeliveryTime) {
        this.estimatedDeliveryTime = estimatedDeliveryTime;
    }
}
