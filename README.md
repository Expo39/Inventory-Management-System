# Inventory Management System

An inventory management system implemented in both **C++** and **Java**, demonstrating design patterns, protocol buffer serialisation, and gRPC communication.

## Run the Applications

### C++ Version
```bash
cd cpp-implementation
mkdir build && cd build
cmake .. && make
./inventory_system
```

### Java Version
```bash
cd java-implementation
mvn compile
mvn exec:java -Dexec.mainClass="com.inventory.core.InventoryManagementSystem"
```

## What You'll See

Both applications show:
- **Product Creation**: Books, Clothing, Electronics, Guitars, PC Games, Stationery
- **Stock Management**: Adding products to inventory
- **Shipment Processing**: Creating and managing shipments
- **Transport Costing**: Air, Land, Ocean shipping calculations
- **State Persistence**: Saving data with Protocol Buffers

## Advanced Features

### Protocol Buffer Demo
**C++:** `cd cpp-implementation/build && ./state_demo`  
**Java:** `cd java-implementation && mvn exec:java -Dexec.mainClass="com.inventory.core.ProtobufTest"`

### gRPC Client-Server Demo
**Server:** `cd java-implementation && mvn exec:java -Dexec.mainClass="com.inventory.core.GrpcServer"`  
**Client:** `cd java-implementation && mvn exec:java -Dexec.mainClass="com.inventory.core.GrpcClient"`
