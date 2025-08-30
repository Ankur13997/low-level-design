# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-pragma-once-outside-header

# Output binary
TARGET = elevator

# Source files
SRC = \
    DriverCode.cpp \
    Display.cpp \
    ElevatorCar.cpp \
    InnerButton.cpp \
    ElevatorController.cpp \
    InnerButtonDispatcher.cpp







    


# Default build target
all: $(TARGET)

$(TARGET): $(SRC) 
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

# Clean target to delete built binary
clean:
	$(RM) $(TARGET)
