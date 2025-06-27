#include "Others.ih"

// Constructor for the Packaging class
Packaging::Packaging(int capacity, string material, string type)
    : capacity(capacity), material(move(material)), type(move(type)) {

}

// Calculate and return the total cost of this packaging
double Packaging::calculateCost() const {
    double materialCost = materialCosts.at(material); // Cost based on the material
    double typeCost = typeCosts.at(type); // Cost based on the type
    return materialCost + typeCost; // Total cost is the sum of material and type costs
}

// Map definitions for the costs of materials
const map<string, double> Packaging::materialCosts = {
    {"paper", 0.10},
    {"cardboard", 0.25},
    {"plastic", 0.15}
};

// Map definitions for the costs of packaging types
const map<string, double> Packaging::typeCosts = {
    {"box", 0.50},
    {"envelope", 0.20},
    {"crate", 0.75}
};

// Get the type of the packaging
string Packaging::getType() const {
    return type;
}

// Get the material of the packaging
string Packaging::getMaterial() const {
    return material;
}

// Get the capacity of the packaging
int Packaging::getCapacity() const {
    return capacity;
}
