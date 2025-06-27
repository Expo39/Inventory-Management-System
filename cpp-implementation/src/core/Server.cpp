#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include "Service.grpc.pb.h" 
#include "Protobufs.pb.h"

using namespace std;

//namespaces
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using server::CalculateShipmentPriceRequest; 
using server::CalculateShipmentPriceResponse; 
using server::ShipmentPriceCalculator; 

class Calculator final : public ShipmentPriceCalculator::Service {
    Status CalculateShipmentPrice(ServerContext* context, const CalculateShipmentPriceRequest* request, CalculateShipmentPriceResponse* response) override {
        for (const auto& shipment : request->shipments()) {
            double total_price = 0.0;
            for (const auto& product : shipment.products()) {
                total_price += product.price() * product.volume(); // Add the price of products
            }
            total_price += shipment.packaging().price(); // Add the cost of packaging
            if (shipment.has_transportmethod()) {
                const auto& transport = shipment.transportmethod();
                if (transport.has_land()) {
                    total_price += transport.land().transport_property().price();
                } else if (transport.has_ocean()) {
                    total_price += transport.ocean().transport_property().price();
                } else if (transport.has_air()) {
                    total_price += transport.air().transport_property().price();
                }
                // Add the price of shipment
            }
            (*response->mutable_total_prices())[shipment.shipmentid()] = total_price; //Return total cost
        }
        return Status::OK;
    }
};

void RunServer() {
    string server_address("0.0.0.0:50051");
    Calculator service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Server listening on " << server_address << '\n';

    server->Wait();
}

int main() {
    RunServer();
    return 0;
}
