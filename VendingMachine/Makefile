# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-pragma-once-outside-header

# Output binary
TARGET = vendingMachine

# Source files
SRC = \
    DriverCode.cpp \
    Item.cpp \
    ItemShelf.cpp \
    Inventory.cpp \
    VendingMachine.cpp \
    VendingStates/States.cpp \
    VendingStates/Impl/IdleState.cpp \
    VendingStates/Impl/HasMoneyState.cpp \
    VendingStates/Impl/SelectionState.cpp \
    VendingStates/Impl/DispenseState.cpp

# Default build target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

# Clean target to delete built binary
clean:
	$(RM) $(TARGET)
