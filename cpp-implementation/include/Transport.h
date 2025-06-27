#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "TransportTypes.h"
#include <string>

using namespace std;

// Abstract base class representing properties of all transport modes
class Transport {
protected:
    double speed; // Transportation speed in km/h
    double costPerKm; // Transportation cost per kilometer
    static inline const double distance = 100.0;

public:
    Transport(double speed, double costPerKm) : speed(speed), costPerKm(costPerKm) {}
    virtual ~Transport() = default;

    // Virtual functions to be implemented by derived classes
    virtual string getTransportType() const = 0;
    virtual string getRouteStages() const = 0;
    virtual double calculateDeliveryTime() const = 0;
    virtual double calculateDeliveryCost() const = 0;
};

// Derived class for Ocean transport
class Ocean : public Transport {
private:
    OceanType type; // Specific ocean transport type
    string seaRoutes; // String representing the sea routes
   
public:
    Ocean(OceanType type);
     
    // Overridden methods from the base class
    string getRouteStages() const override;
    double calculateDeliveryTime() const override;
    double calculateDeliveryCost() const override;
    string getTransportType() const override;
};

// Derived class for Land transport
class Land : public Transport {
private:
    LandType type; // Specific land transport type
    string roadStages; // String representing the road stages

public:
    Land(LandType type);
    string getTransportType() const override;

    // Overridden methods from the base class
    string getRouteStages() const override;
    double calculateDeliveryTime() const override;
    double calculateDeliveryCost() const override;
};

// Derived class for Air transport
class Air : public Transport {
private:
    AirType type; // Specific air transport type
    string airRoutes; // String representing the air routes

public:
    Air(AirType type);
    string getTransportType() const override;

    // Overridden methods from the base class
    string getRouteStages() const override;
    double calculateDeliveryTime() const override;
    double calculateDeliveryCost() const override;
};

#endif
