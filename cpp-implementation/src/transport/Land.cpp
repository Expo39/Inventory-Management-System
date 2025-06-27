#include "Transport.ih"

// Constructor for the Land class
Land::Land(LandType type)
    : Transport(LandTransportProperties.at(type).first, LandTransportProperties.at(type).second),
      type(type), roadStages(LandRoutes.at(type)) {

}

// Calculates the time taken to cover a distance at the object's speed.
double Land::calculateDeliveryTime() const {
    return distance / speed;
}

// Calculates the total cost of delivering over a distance.
double Land::calculateDeliveryCost() const {
    return distance * costPerKm;
}

// Converts the OceanType enum value to a readable string.
string Land::getTransportType() const {
    return toString(type);
}

// Returns a string describing the route stages for the specific ocean transport.
string Land::getRouteStages() const {
    return roadStages;
}

// Helper function to convert OceanType enum to string
string toString(LandType type) {
    switch (type) {
        case LandType::Truck: return "Truck";
        case LandType::Car: return "Car";
        case LandType::Pickup: return "Pickup";
        default: return "Unknown";
    }
}
