#include "Transport.ih"

// Constructor for the Air class
Air::Air(AirType type)
    : Transport(AirTransportProperties.at(type).first, AirTransportProperties.at(type).second),
      type(type), airRoutes(AirRoutes.at(type)) {
    
}

// Calculates the time taken to cover a distance at the object's speed.
double Air::calculateDeliveryTime() const {
 
    return distance / speed;
}

// Calculates the total cost of delivering over a distance.
double Air::calculateDeliveryCost() const {
    return distance * costPerKm;
}

// Converts the OceanType enum value to a readable string.
string Air::getTransportType() const {
    return toString(type);
}

// Returns a string describing the route stages for the specific ocean transport.
string Air::getRouteStages() const {
    return airRoutes;
}

// Helper function to convert OceanType enum to string
string toString(AirType type) {
    switch (type) {
        case AirType::CargoPlane: return "CargoPlane";
        case AirType::CommercialPlane: return "CommercialPlane";
        case AirType::Helicopter: return "Helicopter";
        default: return "Unknown";
    }
}
