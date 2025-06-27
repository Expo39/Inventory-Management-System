#include "Transport.ih"

// Constructor for the Ocean class
Ocean::Ocean(OceanType type)
    : Transport(OceanTransportProperties.at(type).first, OceanTransportProperties.at(type).second),
      type(type), seaRoutes(OceanRoutes.at(type)) {
}

// Calculates the time taken to cover a distance at the object's speed.
double Ocean::calculateDeliveryTime() const {
    return distance / speed;
}

// Calculates the total cost of delivering over a distance.
double Ocean::calculateDeliveryCost() const {
    return distance * costPerKm;
}


// Converts the OceanType enum value to a readable string.
string Ocean::getTransportType() const {
    return toString(type); // Utilises the helper function defined below
}

// Returns a string describing the route stages for the specific ocean transport.
string Ocean::getRouteStages() const {
    return seaRoutes; 
}

// Helper function to convert OceanType enum to string
string toString(OceanType type) {
    switch (type) {
        case OceanType::Freighter: return "Freighter";
        case OceanType::SmallShip: return "SmallShip";
        case OceanType::Boat: return "Boat";
        default: return "Unknown"; // Default case to handle unexpected values
    }
}
