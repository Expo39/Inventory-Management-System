#ifndef DISPLAY_STATE_H
#define DISPLAY_STATE_H

#include "Protobufs.pb.h"

using namespace std;

// Function declarations
void createProducts(Protobufs::Stock& stock);
void createAndDispatchShipment(Protobufs::Stock& stock, Protobufs::AllShipments& allShipments);

// Enumeration conversions to strings
string shipmentStatusToString(Protobufs::ShipmentStatus status);
string transportTypeToString(const Protobufs::Transport& transport);

// Display functions
void displayProductDetails(const Protobufs::Product& product);
void displayShipmentDetails(const Protobufs::Shipment& shipment);

// Handles serialisation and deserialisation
class Facade {
public:
    static void save(const Protobufs::Stock& stock, const Protobufs::AllShipments& allShipments, const string& filename);
    static void load(Protobufs::Stock& stock, Protobufs::AllShipments& allShipments, const string& filename);
};

#endif 
