#ifndef TRANSPORT_FACTORY_H
#define TRANSPORT_FACTORY_H

#include "TransportTypes.h"
#include "Transport.h"
#include <memory>
#include <stdexcept>
#include <vector>
#include <string>

// Enumeration for different transport types: Land, Ocean, and Air.
enum class TransportType {
    Land,
    Ocean,
    Air
};

// Factory Pattern Class for Transport Objects
class TransportFP {
public:
    // Static function to create unique transport objects based on the type and properties.
    static std::unique_ptr<Transport> createTransport(TransportType type, const std::vector<std::string>& properties) {
        switch (type) {
            case TransportType::Land: {
                // Convert string to LandType enum and create a Land transport object.
                LandType landType = stringToLandType(properties.at(0));
                return std::make_unique<Land>(landType);
            }

            case TransportType::Ocean: {
                // Convert string to OceanType enum and create an Ocean transport object.
                OceanType oceanType = stringToOceanType(properties.at(0));
                return std::make_unique<Ocean>(oceanType);
            }

            case TransportType::Air: {
                // Convert string to AirType enum and create an Air transport object.
                AirType airType = stringToAirType(properties.at(0));
                return std::make_unique<Air>(airType);
            }

            default:
                // Throw an exception if the transport type is unknown.
                throw std::invalid_argument("Unknown transport type");
        }
    }

private:
    // Helper function to convert a string to a LandType enum value.
    static LandType stringToLandType(const std::string& type) {
        if (type == "Truck") return LandType::Truck;
        if (type == "Car") return LandType::Car;
        if (type == "Pickup") return LandType::Pickup;
        throw std::invalid_argument("Unknown LandType: " + type);
    }

    // Helper function to convert a string to an OceanType enum value.
    static OceanType stringToOceanType(const std::string& type) {
        if (type == "Freighter") return OceanType::Freighter;
        if (type == "SmallShip") return OceanType::SmallShip;
        if (type == "Boat") return OceanType::Boat;
        throw std::invalid_argument("Unknown OceanType: " + type);
    }

    // Helper function to convert a string to an AirType enum value.
    static AirType stringToAirType(const std::string& type) {
        if (type == "CargoPlane") return AirType::CargoPlane;
        if (type == "CommercialPlane") return AirType::CommercialPlane;
        if (type == "Helicopter") return AirType::Helicopter;
        throw std::invalid_argument("Unknown AirType: " + type);
    }
};

#endif 
