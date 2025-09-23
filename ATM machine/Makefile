# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-pragma-once-outside-header

# Source files
SRC = \
    DriverCode.cpp \
    Atm.cpp \
    AtmStates/States.cpp \
    AtmStates/CashWithDraw.cpp \
    AtmStates/DisplayAmount.cpp \
    AtmStates/IdleState.cpp \
    AtmStates/HasCardState.cpp \
    AtmStates/SelectionState.cpp

# Target for ATM application
TARGET = ATMmachine

# Target for unit tests
TEST_TARGET = test_atm.exe
TEST_SRC = test_atm.cpp \
    Atm.cpp \
    AtmStates/States.cpp \
    AtmStates/CashWithDraw.cpp \
    AtmStates/DisplayAmount.cpp \
    AtmStates/IdleState.cpp \
    AtmStates/HasCardState.cpp \
    AtmStates/SelectionState.cpp

# Default build target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

# Unit test build
test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) -lgtest -lgtest_main -pthread -I C:/msys64/ucrt64/include -L C:/msys64/ucrt64/lib

# Clean target
clean:
	$(RM) $(TARGET) $(TEST_TARGET)
