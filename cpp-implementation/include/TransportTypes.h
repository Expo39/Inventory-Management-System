#ifndef TRANSPORT_TYPES_H
#define TRANSPORT_TYPES_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// Enumerations for different types of land, ocean, and air transport
enum class LandType {
    Truck,
    Car,
    Pickup
};

enum class OceanType {
    Freighter,
    SmallShip,
    Boat
};

enum class AirType {
    CargoPlane,
    CommercialPlane,
    Helicopter
};

// Forward declarations for toString functions
string toString(LandType type);
string toString(OceanType type);
string toString(AirType type);

// Map for land transport properties
inline const map<LandType, pair<double, double>> LandTransportProperties = {
    {LandType::Truck, {60, 0.8}}, // Speed in km/h, Cost per km
    {LandType::Car, {90, 0.5}},
    {LandType::Pickup, {70, 0.7}}
};

// Map for ocean transport properties
inline const map<OceanType, pair<double, double>> OceanTransportProperties = {
    {OceanType::Freighter, {30, 2.0}},
    {OceanType::SmallShip, {40, 1.5}},
    {OceanType::Boat, {20, 1.0}}
};

// Map for air transport properties
inline const map<AirType, pair<double, double>> AirTransportProperties = {
    {AirType::CargoPlane, {800, 10.0}},
    {AirType::CommercialPlane, {900, 12.0}},
    {AirType::Helicopter, {300, 15.0}}
};

// Map for transport routes
inline const map<LandType, string> LandRoutes = {
    {LandType::Truck, "Highway A1 -> Highway B2 -> Local Road C3"},
    {LandType::Car, "Main Street -> Bridge D4 -> Avenue E5"},
    {LandType::Pickup, "Dirt Track F6 -> Mountain Pass G7 -> Valley Road H8"}
};

// Map for ocean routes
inline const map<OceanType, string> OceanRoutes = {
    {OceanType::Freighter, "Sea Lane M -> Sea Lane N -> Port O"},
    {OceanType::SmallShip, "Coastal Path P -> Island Q -> Dock R"},
    {OceanType::Boat, "River S -> Canal T -> Marina U"}
};

// Map for air routes
inline const map<AirType, string> AirRoutes = {
    {AirType::CargoPlane, "Airspace X -> Airspace Y -> Airspace Z"},
    {AirType::CommercialPlane, "Flight Path V -> Flight Path W -> Airport AA"},
    {AirType::Helicopter, "Heli Route BB -> Heli Route CC -> Heliport DD"}
};

#endif
