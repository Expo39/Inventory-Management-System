#include <iostream>
#include <fstream>
#include <memory>
#include "State.h"
#include "Server.h"
#include "Protobufs.pb.h"

using namespace std;


int main() {
    Protobufs::Stock stock;
    Protobufs::AllShipments allShipments;

    // Load previous state
    Facade::load(stock, allShipments, "app_state.bin");

    createProducts(stock);  
    createAndDispatchShipment(stock, allShipments); 

    // Displaying details of each shipment
    for (const auto& shipmentPair : allShipments.shipments()) {
        displayShipmentDetails(shipmentPair.second);
        cout << "\n";
    }

    // Save current state
    Facade::save(stock, allShipments, "app_state.bin");
}


void createProducts(Protobufs::Stock& stock) {
    // Create a Pen product and add it to the map
    Protobufs::Product penProduct;
    penProduct.set_id(1);
    penProduct.set_name("Fancy Pen");
    penProduct.set_price(9.99);
    penProduct.set_volume(100);
    penProduct.set_supplier("PenSupplier");
    Protobufs::Pens* penDetails = penProduct.mutable_stationary()->mutable_pens();
    penDetails->set_inktype("Blue Ink");
    penProduct.mutable_stationary()->set_material("Plastic");

    // Add the Pen product to the stock map
    (*stock.mutable_products())[penProduct.id()] = penProduct;

    // Create a Dress product and add it to the map
    Protobufs::Product dressProduct;
    dressProduct.set_id(2);
    dressProduct.set_name("Elegant Dress");
    dressProduct.set_price(59.99);
    dressProduct.set_volume(50);
    dressProduct.set_supplier("DressSupplier");
    Protobufs::Dresses* dressDetails = dressProduct.mutable_clothing()->mutable_dresses();
    dressDetails->set_type("Evening Wear");
    dressProduct.mutable_clothing()->set_size("Medium");
    dressProduct.mutable_clothing()->set_material("Cotton");

    // Add the Dress product to the stock map
    (*stock.mutable_products())[dressProduct.id()] = dressProduct;

    Protobufs::Product guitarProduct;
    guitarProduct.set_id(3); 
    guitarProduct.set_name("Classic Acoustic Guitar");
    guitarProduct.set_price(199.99);
    guitarProduct.set_volume(20);
    guitarProduct.set_supplier("GuitarSupplier");
    Protobufs::Guitars* guitarDetails = guitarProduct.mutable_guitars();
    guitarDetails->set_material("Wood");
    guitarDetails->set_stringcount(6);
    Protobufs::Acoustic* acousticDetails = guitarDetails->mutable_acoustic();
    acousticDetails->set_haspickup(true);

    // Add the Acoustic Guitar product to the stock map
    (*stock.mutable_products())[guitarProduct.id()] = guitarProduct;
}

void createAndDispatchShipment(Protobufs::Stock& stock, Protobufs::AllShipments& allShipments) {
    // Create a protobuf Packaging message
    Protobufs::Packaging firstPackaging;
    firstPackaging.set_capacity(10);        
    firstPackaging.set_material("cardboard");
    firstPackaging.set_type("box");          
    firstPackaging.set_matcost(5);
    firstPackaging.set_typecost(7);
    firstPackaging.set_price(firstPackaging.matcost() + firstPackaging.typecost());

    // Create a protobuf Transport message for land transport
    Protobufs::Transport firstTransport;
    Protobufs::Land* landTransport = firstTransport.mutable_land();
    landTransport->set_type(Protobufs::LandType::TRUCK);
    landTransport->set_roadstages("Highway A1 -> Highway B2 -> Local Road C3");

    Protobufs::TransportProperty* landTransportProperty = landTransport->mutable_transport_property();
    landTransportProperty->set_distance(100); 
    landTransportProperty->set_cost(2.0); 
    landTransportProperty->set_price(landTransportProperty->distance() * landTransportProperty->cost());

    // Create a protobuf Shipment message
    Protobufs::Shipment firstShipment;
    firstShipment.set_shipmentid(1);
    firstShipment.set_allocated_packaging(&firstPackaging);
    *firstShipment.mutable_transportmethod() = firstTransport;

    // Add specific products to the shipment from the Stock map
    for (int productId : {1, 2}) {  
        auto it = stock.products().find(productId);
        if (it != stock.products().end()) {
            *firstShipment.add_products() = it->second;
        }
    }

    // Set the status of the shipment
    firstShipment.set_status(Protobufs::ShipmentStatus::DISPATCHED);
    firstShipment.set_dispatchtime("5th January");
    firstShipment.set_estimateddeliverytime("6th January");


    // Add the first shipment to AllShipments
    (*allShipments.mutable_shipments())[firstShipment.shipmentid()] = firstShipment;
    firstShipment.release_packaging();



    // Create another protobuf Packaging message for the second shipment
    Protobufs::Packaging secondPackaging;
    secondPackaging.set_capacity(15);  
    secondPackaging.set_material("plastic"); 
    secondPackaging.set_type("crate"); 
    secondPackaging.set_matcost(3);
    secondPackaging.set_typecost(1);
    secondPackaging.set_price(secondPackaging.matcost() + secondPackaging.typecost());

    // Create another protobuf Transport message for the second shipment
    Protobufs::Transport secondTransport;
    Protobufs::Ocean* oceanTransport = secondTransport.mutable_ocean();
    oceanTransport->set_type(Protobufs::OceanType::FREIGHTER);
    oceanTransport->set_searoutes("Sea Lane M -> Sea Lane N -> Port O");

    Protobufs::TransportProperty* OceanTransportProperty = oceanTransport->mutable_transport_property();
    OceanTransportProperty->set_distance(230); 
    OceanTransportProperty->set_cost(5.2); 
    OceanTransportProperty->set_price(OceanTransportProperty->distance() * OceanTransportProperty->cost());


    // Create another Shipment for the new product
    Protobufs::Shipment secondShipment;
    secondShipment.set_shipmentid(2); 
    secondShipment.set_allocated_packaging(&secondPackaging);
    *secondShipment.mutable_transportmethod() = secondTransport; 

    // Add the new product (book) to the shipment
    auto it = stock.products().find(3); 
    if (it != stock.products().end()) {
        *secondShipment.add_products() = it->second;
    }

    // Set the status of the second shipment
    secondShipment.set_status(Protobufs::ShipmentStatus::CREATED);
    secondShipment.set_dispatchtime("Not Dispatched");
    secondShipment.set_estimateddeliverytime("Not Dispatched");

    // Add the second shipment to AllShipments
    (*allShipments.mutable_shipments())[secondShipment.shipmentid()] = secondShipment;
    secondShipment.release_packaging(); 
    
    Client shippingClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    // Declare the variables to store the total costs of the shipments
    double totalcost1 = 0.0;
    double totalcost2 = 0.0;

    // Calculate total cost for the first shipment using gRPC
    totalcost1 = shippingClient.CalculateShipmentPrice(firstShipment);
    firstShipment.set_totalcost(totalcost1);
    (*allShipments.mutable_shipments())[firstShipment.shipmentid()] = firstShipment;
    firstShipment.release_packaging();

    // Calculate total cost for the second shipment using gRPC
    totalcost2 = shippingClient.CalculateShipmentPrice(secondShipment);
    secondShipment.set_totalcost(totalcost2);
    (*allShipments.mutable_shipments())[secondShipment.shipmentid()] = secondShipment;
    secondShipment.release_packaging();
}

// Serialisation
void Facade::save(const Protobufs::Stock& stock, const Protobufs::AllShipments& allShipments, const string& filename) {
    // Create a combined message to hold both stock and shipments
    Protobufs::InventoryState inventoryState;
    *inventoryState.mutable_stock() = stock;
    *inventoryState.mutable_allshipments() = allShipments;
    
    ofstream out(filename, ios::binary);
    if (!out) {
        cerr << "Cannot open file for saving: " << filename << '\n';
        return;
    }
    
    if (!inventoryState.SerializeToOstream(&out)) {
        cerr << "Failed to serialize inventory state to " << filename << '\n';
    } else {
        cout << "State saved successfully to " << filename << '\n';
    }
}
    
// Deserialisation
void Facade::load(Protobufs::Stock& stock, Protobufs::AllShipments& allShipments, const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        cerr << "Cannot open file for loading: " << filename << '\n';
        return;
    }
    
    Protobufs::InventoryState inventoryState;
    if (!inventoryState.ParseFromIstream(&in)) {
        cerr << "Failed to parse inventory state from " << filename << '\n';
        return;
    }
    
    stock = inventoryState.stock();
    allShipments = inventoryState.allshipments();
    cout << "State loaded successfully from " << filename << '\n';
}
