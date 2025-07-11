# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Output binary
TARGET = vehicle_inventory_app

# Source files
SRC = \
    DriverCode.cpp \
    Vehicle.cpp \
    BikeVehicle.cpp \
    CarVehicle.cpp \
    StoreController.cpp \
    Reservation.cpp \
    CarRentalSystem.cpp \
    Store.cpp \
    User.cpp \
    VehicleInventoryManagement.cpp\
    Bill.cpp\
    Payment.cpp


# Default build target
all: $(TARGET)

$(TARGET): $(SRC) 
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

# Clean target to delete built binary
clean:
	$(RM) $(TARGET)
