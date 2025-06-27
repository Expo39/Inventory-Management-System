#include <iostream>
#include <fstream>
#include <memory>
#include "State.h"
#include "Protobufs.pb.h" 

using namespace std;

string shipmentStatusToString(Protobufs::ShipmentStatus status) {
    switch (status) {
        case Protobufs::ShipmentStatus::DISPATCHED: return "Dispatched";
        case Protobufs::ShipmentStatus::CREATED:    return "Created";
        case Protobufs::ShipmentStatus::CANCELLED:  return "Cancelled";
        default:                                    return "Unknown";
    }
}

string transportTypeToString(const Protobufs::Transport& transport) {
    if (transport.has_land()) {
        return "Truck";
    } else if (transport.has_ocean()) {
        return "Freighter";
    } else if (transport.has_air()) {
        return "Plane";
    }
    return "Unknown";
}

void displayProductDetails(const Protobufs::Product& product) {
    cout << "Product ID: " << product.id() 
              << ", Name: " << product.name() 
              << ", Price: " << product.price() 
              << ", Volume: " << product.volume() 
              << ", Supplier: " << product.supplier() << '\n';

    // Stationary Category
    if (product.has_stationary()) {
        const auto& stationary = product.stationary();
        cout << "  Stationary Material: " << stationary.material() << '\n';
        if (stationary.has_notepads()) {
            cout << "  Notepad Pages: " << stationary.notepads().pages() << '\n';
        } else if (stationary.has_pens()) {
            cout << "  Pen Ink Type: " << stationary.pens().inktype() << '\n';
        }
    }

    // PC Games Category
    if (product.has_pc_games()) {
        const auto& pcGames = product.pc_games();
        cout << "  Game Genre: " << pcGames.genre() << '\n';
        cout << "  Age Rating: " << pcGames.agerating() << '\n';
        if (pcGames.has_action()) {
            cout << "  Action Game - Multiplayer: " << (pcGames.action().multiplayer() ? "Yes" : "No") << '\n';
        } else if (pcGames.has_strategy()) {
            cout << "  Strategy Game - Theme: " << pcGames.strategy().theme() << '\n';
        }
    }

    // Guitars Category
    if (product.has_guitars()) {
        const auto& guitars = product.guitars();
        cout << "  Guitar Material: " << guitars.material() << '\n';
        cout << "  String Count: " << guitars.stringcount() << '\n';
        if (guitars.has_electric()) {
            cout << "  Electric Guitar - Pickup Type: " << guitars.electric().pickuptype() << '\n';
        } else if (guitars.has_acoustic()) {
            cout << "  Acoustic Guitar - Has Pickup: " << (guitars.acoustic().haspickup() ? "Yes" : "No") << '\n';
        }
    }

    // Electronics Category
    if (product.has_electronics()) {
        const auto& electronics = product.electronics();
        cout << "  Electronics Brand: " << electronics.brand() << '\n';
        cout << "  Warranty Period: " << electronics.warranty() << '\n';
        if (electronics.has_laptops()) {
            cout << "  Laptop OS: " << electronics.laptops().operatingsystem() << '\n';
        } else if (electronics.has_phones()) {
            cout << "  Phone Year: " << electronics.phones().year() << '\n';
            cout << "  Storage Capacity: " << electronics.phones().storage() << '\n';
        }
    }

    // Clothing Category
    if (product.has_clothing()) {
        const auto& clothing = product.clothing();
        cout << "  Clothing Size: " << clothing.size() << '\n';
        cout << "  Material: " << clothing.material() << '\n';
        if (clothing.has_dresses()) {
            cout << "  Dress Type: " << clothing.dresses().type() << '\n';
        } else if (clothing.has_tshirts()) {
            cout << "  T-Shirt - Can be ironed: " << (clothing.tshirts().can_be_ironed() ? "Yes" : "No") << '\n';
        }
    }

    // Books Category
    if (product.has_books()) {
        const auto& books = product.books();
        cout << "  Author: " << books.author() << '\n';
        cout << "  Publisher: " << books.publisher() << '\n';
        if (books.has_fiction()) {
            cout << "  Fiction Genre: " << books.fiction().genre() << '\n';
        } else if (books.has_nonfiction()) {
            cout << "  Non-Fiction Field: " << books.nonfiction().field() << '\n';
        }
    }

}

void displayShipmentDetails(const Protobufs::Shipment& shipment) {
    cout << "Shipment ID: " << shipment.shipmentid() << '\n';
    cout << "Shipment Status: " << shipmentStatusToString(shipment.status()) << '\n';
    cout << "Total Cost: " << shipment.totalcost() << '\n';
    cout << "Dispatch Time: " << shipment.dispatchtime() << '\n';
    cout << "Estimated Delivery Time: " << shipment.estimateddeliverytime() << '\n';

    // Display Packaging Details
    const Protobufs::Packaging& packaging = shipment.packaging();
    cout << "Packaging - Capacity: " << packaging.capacity() 
              << ", Material: " << packaging.material() 
              << ", Type: " << packaging.type() << '\n';

    // Display Transport Method Details
    if (shipment.has_transportmethod()) {
        const Protobufs::Transport& transport = shipment.transportmethod();
        cout << "Transport Method: " << transportTypeToString(transport);
        if (transport.has_land()) {
            cout << " - Road Stages: " << transport.land().roadstages() << '\n';
        } else if (transport.has_ocean()) {
            cout << " - Sea Routes: " << transport.ocean().searoutes() << '\n';
        } else if (transport.has_air()) {
            cout << " - Air Routes: " << transport.air().airroutes() << '\n';
        }
    }

    // Display Product Details
    cout << "\nProducts in Shipment:" << '\n';
    for (const auto& product : shipment.products()) {
        displayProductDetails(product);

        cout << "\n";
    }
}