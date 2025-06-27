#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include "Service.grpc.pb.h"

using namespace std;

// namespaces
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using server::CalculateShipmentPriceRequest;
using server::CalculateShipmentPriceResponse;
using server::ShipmentPriceCalculator;

class Client {
public:
    Client(shared_ptr<Channel> channel)
        : stub_(ShipmentPriceCalculator::NewStub(channel)) {}

    // calculate the total price of a shipment
    double CalculateShipmentPrice(const Protobufs::Shipment& shipment) {
        // Prepare the request
        CalculateShipmentPriceRequest request;
        *request.add_shipments() = shipment;

        // Prepare the response
        CalculateShipmentPriceResponse response;

        // Context for the client
        ClientContext context;

        // The actual RPC
        Status status = stub_->CalculateShipmentPrice(&context, request, &response);

        // Act upon its status
        if (status.ok()) {
            return response.total_prices().at(shipment.shipmentid());
        } else {
            cout << status.error_code() << ": " << status.error_message() << '\n';
            return -1;  // An error occurred
        }
    }

private:
    unique_ptr<ShipmentPriceCalculator::Stub> stub_;
};

#endif 