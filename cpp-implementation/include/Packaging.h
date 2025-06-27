#ifndef PACKAGING_H
#define PACKAGING_H

#include <string>
#include <map>

using namespace std;

// Packaging class represents the packaging details for a product or a shipment.
class Packaging {
private:
    int capacity; // The capacity of the packaging
    string material; // The material of the packaging
    string type; // The type of the packaging

    // Maps to hold the cost of different materials and types of packaging
    static const map<string, double> materialCosts;
    static const map<string, double> typeCosts;

public:
    // Constructor to initialise packaging with capacity, material, and type
    Packaging(int capacity, string material, string type);

    // Calculate the total cost of the packaging based on its material and type
    double calculateCost() const;

    // Getters for packaging properties
    string getType() const;
    string getMaterial() const;
    int getCapacity() const;
};

#endif 
