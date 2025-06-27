#ifndef SHIPMENT_H
#define SHIPMENT_H

#include "Product.h"
#include "Packaging.h"
#include "Transport.h"
#include "Stock.h" 

#include <memory>
#include <chrono>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Enumeration for possible statuses of a shipment
enum class ShipmentStatus {
    Created,
    Dispatched,
    Cancelled
};

// Shipment class definition
class Shipment {
private:
    int shipmentId; // Unique ID for this shipment
    static int nextShipmentId; // Static variable to generate unique IDs for each new shipment

    static map<int, Shipment*> allShipments; // Static map to keep track of all created shipments
    vector<unique_ptr<Product>> products; // Products included in the shipment
    
    Packaging packaging; // Packaging details of the shipment

    unique_ptr<Transport> transportMethod; // Transport method used for the shipment

    ShipmentStatus status; // Current status of the shipment

    int dispatchMonth; // Month when the shipment was dispatched
    chrono::system_clock::time_point dispatchTime; // Time when the shipment was dispatched
    chrono::system_clock::time_point estimatedDeliveryTime; // Estimated delivery time of the shipment

    // Convert a time point to a readable string
    string convertTimePointToString(const chrono::system_clock::time_point& timePoint) const;

public:
    // Constructor to create a shipment which includes the packaging and transport methods
    Shipment(const Packaging& packaging, unique_ptr<Transport> transportMethod);

    // Functions to manipulate the products & transport in the shipment
    void addProduct(Stock& stock, int productId); // Updated to retrieve product from Stock
    void removeProduct(int productId);
    void updateTransportMethod(unique_ptr<Transport> newTransportMethod);

    // Functions to control the shipment's lifecycle
    void dispatch();
    void cancel();

    // Getter functions for shipment information
    int getShipmentId() const;
    ShipmentStatus getStatus() const;
    double calculateTotalCost() const;
    string getDispatchTime() const;
    string getEstimatedDeliveryTime() const;

    // Static functions to convert and display shipment status
    static string shipmentStatusToString(ShipmentStatus status);
    static void displayProductsInShipment(int shipmentId);
    static void listAllShipments();

    // Function to display detailed information about the shipment
    void displayShipmentDetails() const;

};

#endif
