#include "Shipments.ih"

int Shipment::nextShipmentId = 0; // Initialise shipment ID counter
map<int, Shipment*> Shipment::allShipments; // Map to store all shipment instances

// Constructor for Shipment class
Shipment::Shipment(const Packaging& packaging, unique_ptr<Transport> transportMethod)
    : packaging(packaging), transportMethod(move(transportMethod)), status(ShipmentStatus::Created) {
    shipmentId = nextShipmentId++; // Assign a unique ID to this shipment
    allShipments[shipmentId] = this; // Add this shipment to the map
}

void Shipment::addProduct(Stock& stock, int productId) {
    if (status == ShipmentStatus::Created) {
        auto product = stock.retrieveAndRemoveProduct(productId);
        if (product) {
            products.push_back(std::move(product)); // Add the product to the shipment
            cout << "Product with ID " << productId << " added to shipment.\n";
        } else {
            cerr << "Product with ID " << productId << " not found in stock or already added to another shipment.\n";
        }
    } else {
        cerr << "Cannot add product. Shipment already dispatched or canceled.\n";
    }
}


void Shipment::removeProduct(int productId) {
    if (status == ShipmentStatus::Created) {
        // Remove the product based on productId
        auto remove = remove_if(
            products.begin(), products.end(),
            [productId](const unique_ptr<Product>& product) {
                return product->getId() == productId;
            });
        if (remove != products.end()) {
            products.erase(remove, products.end()); // Erase the product if found
        } else {
            cerr << "Product with ID " << productId << " not found in shipment.\n";
        }
    } else {
        cerr << "Cannot remove product. Shipment already dispatched or canceled.\n";
    }
}

void Shipment::updateTransportMethod(unique_ptr<Transport> newTransportMethod) {
    if (status == ShipmentStatus::Created) {
        transportMethod = move(newTransportMethod); // Update if shipment is not yet dispatched or canceled
    } else {
        cerr << "Cannot update transport method. Shipment already dispatched or canceled.\n";
    }
}

void Shipment::dispatch() {
    if (status == ShipmentStatus::Created) {
        status = ShipmentStatus::Dispatched;
        dispatchTime = chrono::system_clock::now(); // Set dispatch time to current time

        // Determine dispatch month from the current time
        time_t now_c = chrono::system_clock::to_time_t(dispatchTime);
        struct tm *parts = localtime(&now_c);
        dispatchMonth = parts->tm_mon + 1;

        // Calculate the estimated delivery time
        if (transportMethod) {
            double deliveryTimeInHours = transportMethod->calculateDeliveryTime();
            auto deliveryTime = chrono::duration<double, ratio<3600>>(deliveryTimeInHours);
            estimatedDeliveryTime = dispatchTime + chrono::duration_cast<chrono::system_clock::duration>(deliveryTime);
        } else {
            cerr << "Transport method not set. Cannot calculate estimated delivery time.\n";
        }
    } else {
        cerr << "Cannot dispatch. Shipment already dispatched or canceled.\n";
    }
}

void Shipment::cancel() {
    if (status == ShipmentStatus::Created) {
        status = ShipmentStatus::Cancelled; // Change status to canceled if not yet dispatched
    } else {
        cerr << "Cannot cancel. Shipment already dispatched or canceled.\n";
    }
}

// Method to calculate the total cost of the shipment
double Shipment::calculateTotalCost() const {
    double totalCost = 0;
    // Add the cost of each product in the shipment
    for (const auto& product : products) {
        int volume = product->getVolume();
        double discount = product->calculateDiscount(volume, dispatchMonth);
        totalCost += (product->getPrice() * volume - discount);
    }
    totalCost += packaging.calculateCost(); // Add packaging cost
    if (transportMethod) {
        totalCost += transportMethod->calculateDeliveryCost(); // Add transport cost
    }
    return totalCost;
}

// Method to display products in a specific shipment
void Shipment::displayProductsInShipment(int shipmentId) {
    auto prod = allShipments.find(shipmentId);
    if (prod != allShipments.end()) {
        Shipment* shipment = prod->second;
        cout << "Products in Shipment ID " << shipmentId << ":\n";
        for (const auto& product : shipment->products) {
            cout << product->displayProductInfo() << "\n";
        }
    } else {
        cout << "Shipment with ID " << shipmentId << " not found.\n";
    }
}

// Method to display shipment details
void Shipment::displayShipmentDetails() const {
    cout << "Shipment ID: " << shipmentId << '\n';
    cout << "Status: " << shipmentStatusToString(status) << '\n';
    cout << "Packaging: " << packaging.getType() << ", " << packaging.getMaterial();
    cout << "\nTotal Packaged: " << packaging.getCapacity() << '\n';
    cout << "Transport Method: " << (transportMethod ? transportMethod->getTransportType() : "None") << '\n';
    cout << "Route: " << (transportMethod ? transportMethod->getRouteStages() : "None") << '\n';
    cout << "Total Cost: €" << calculateTotalCost() << '\n';
    cout << "Dispatch Time: " << getDispatchTime() << '\n';
    cout << "Estimated Delivery Time: " << getEstimatedDeliveryTime() << '\n' << '\n';
}

// Method to list all shipments with their statuses
void Shipment::listAllShipments() {
    for (const auto& pair : allShipments) {
        string statusStr = shipmentStatusToString(pair.second->getStatus());
        cout << "Shipment ID: " << pair.first << " - Status: " << statusStr << '\n';
    }
}


// Method to get the current status of the shipment
ShipmentStatus Shipment::getStatus() const {
    return status;
}

// Method to get the unique ID of the shipment
int Shipment::getShipmentId() const {
    return shipmentId;
}

// Method to get the dispatch time as a string
string Shipment::getDispatchTime() const {
    if (status == ShipmentStatus::Created || status == ShipmentStatus::Cancelled) {
        return "Not dispatched";
    }
    return convertTimePointToString(dispatchTime);
}

// Method to get the estimated delivery time as a string
string Shipment::getEstimatedDeliveryTime() const {
    if (status == ShipmentStatus::Created or status == ShipmentStatus::Cancelled) {
        return "Not dispatched";
    }
    return convertTimePointToString(estimatedDeliveryTime);
}

string Shipment::convertTimePointToString(const chrono::system_clock::time_point& timePoint) const {
    time_t time_c = chrono::system_clock::to_time_t(timePoint);
    ostringstream oss;
    oss << ctime(&time_c); // Convert time to string using ctime
    return oss.str();
}


// Method to convert shipment status to a string
string Shipment::shipmentStatusToString(ShipmentStatus status) {
    switch (status) {
        case ShipmentStatus::Created: return "Created";
        case ShipmentStatus::Dispatched: return "Dispatched";
        case ShipmentStatus::Cancelled: return "Cancelled";
        default: return "Unknown";
    }
}