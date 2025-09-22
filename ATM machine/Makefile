# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-pragma-once-outside-header

# Output binary
TARGET = ATMmachine

# Source files
SRC = \
    DriverCode.cpp \
    Atm.cpp \
	AtmStates/States.cpp \
	AtmStates/CashWithDraw.cpp \
	AtmStates/DisplayAmount.cpp \
	AtmStates/IdleState.cpp \
	AtmStates/HasCardState.cpp \
	AtmStates/SelectionState.cpp \


# Default build target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

# Clean target to delete built binary
clean:
	$(RM) $(TARGET)
