cmake_minimum_required(VERSION 3.15.0)
project(InventoryManagementSystem VERSION 1.0.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Find required packages
find_package(Protobuf REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GRPC REQUIRED grpc++ grpc)

# Include directories
include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Generate protobuf and gRPC files
set(PROTO_FILES
    proto/Protobufs.proto
    proto/Service.proto
)

# Generate protobuf files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# Generate gRPC files
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)
if(NOT GRPC_CPP_PLUGIN)
    message(FATAL_ERROR "grpc_cpp_plugin not found!")
endif()

set(GRPC_SRCS)
set(GRPC_HDRS)
foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
    set(GRPC_SRC ${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.cc)
    set(GRPC_HDR ${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.h)
    
    add_custom_command(
        OUTPUT ${GRPC_SRC} ${GRPC_HDR}
        COMMAND ${Protobuf_PROTOC_EXECUTABLE}
        ARGS --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
             --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
             --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
             --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/proto
             ${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
    )
    list(APPEND GRPC_SRCS ${GRPC_SRC})
    list(APPEND GRPC_HDRS ${GRPC_HDR})
endforeach()

# Add source files (common files without main functions)
file(GLOB_RECURSE COMMON_SOURCES
    src/others/*.cpp
    src/products/**/*.cpp
    src/shipment/*.cpp
    src/transport/*.cpp
)

# Create the main CLI executable
add_executable(inventory_system 
    src/core/CLI.cpp 
    ${COMMON_SOURCES}
    ${PROTO_SRCS} 
    ${GRPC_SRCS}
)

# Link libraries
target_link_libraries(inventory_system 
    ${Protobuf_LIBRARIES}
    ${GRPC_LIBRARIES}
    pthread
)

# Create gRPC server executable
add_executable(grpc_server 
    src/core/Server.cpp 
    ${COMMON_SOURCES}
    ${PROTO_SRCS} 
    ${GRPC_SRCS}
)

target_link_libraries(grpc_server 
    ${Protobuf_LIBRARIES}
    ${GRPC_LIBRARIES}
    pthread
)

# Create state demo with protobuf
add_executable(state_demo 
    src/core/State.cpp 
    src/core/DisplayState.cpp
    ${COMMON_SOURCES}
    ${PROTO_SRCS} 
    ${GRPC_SRCS}
)

target_link_libraries(state_demo 
    ${Protobuf_LIBRARIES}
    ${GRPC_LIBRARIES}
    pthread
)
