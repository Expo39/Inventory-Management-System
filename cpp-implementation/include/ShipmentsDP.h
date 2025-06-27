#ifndef SHIPMENTSDP_H
#define SHIPMENTSDP_H

#include "Shipments.h"
#include "TransportFP.h"
#include <iostream>

// Abstract Decorator Class for Shipments
class ShipmentsDP {
protected:
    Shipment* shipment; // Holds a pointer to the original 'Shipment' object being decorated.

public:
    // Constructor to initialise the decorator with a 'Shipment' object.
    ShipmentsDP(Shipment* shipment) : shipment(shipment) {
    
    }
};

// Concrete Decorator Class for applying a global discount and changing transport method based on route closure.
class Decorator : public ShipmentsDP {
private:
    double discountRate; // GLobal Discount rate to apply to the shipment's total cost.
    bool routeClosure; // Flag to indicate if there is a route closure affecting the shipment.

public:
    // Constructor which is initialised with a shipment, discount rate, and route closure status.
    Decorator(Shipment* shipment, double discountRate, bool routeClosure)
        : ShipmentsDP(shipment), discountRate(discountRate), routeClosure(routeClosure) {}

    // Calculates the total cost after applying the discount.
    double calculateTotalCost() const {
        double originalCost = shipment->calculateTotalCost(); // Get the original total cost from the shipment.
        double discountAmount = originalCost * discountRate;
        return originalCost - discountAmount; 
    }

    // Changes the transport method if there is a route closure.
    void RouteClosed() const {
        if (routeClosure) {

            // Creates a new transport method using the Transport Factory Pattern.
            auto newTransport = TransportFP::createTransport(TransportType::Air, {"CargoPlane"});

            // Updates the transport method of the shipment. Casting away since a modification on a const function is done.
            const_cast<Shipment*>(shipment)->updateTransportMethod(std::move(newTransport));
        }
    }

    // Displays shipment details after applying any modifications.
    void displayShipmentDetails() const {
        RouteClosed(); // Check and change the transport method if needed.
        shipment->displayShipmentDetails(); // Display the original shipment details.

        // Display the additional info about the discounted cost.
        std::cout << "Total Cost after Discount: €" << calculateTotalCost() << '\n';
    }
};

#endif 
