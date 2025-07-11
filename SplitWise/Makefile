# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-pragma-once-outside-header

# Output binary
TARGET = splitwise

# Source files
SRC = \
    DriverCode.cpp \
    User.cpp \
    Balance.cpp \
    UserBalanceSheet.cpp \
    Splitwise.cpp \
    Split.cpp \
    SplitExpense.cpp \
    EqualSplit.cpp \
    PercentageSplit.cpp \
    ExactSplit.cpp \
    SplitFactory.cpp \
    Expense.cpp \
    TimeStamp.cpp \
    BalanceSheet.cpp \
    ExpenseController.cpp \
    Group.cpp \
    GroupController.cpp \
    SplitType.cpp \
    UserController.cpp




    


# Default build target
all: $(TARGET)

$(TARGET): $(SRC) 
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

# Clean target to delete built binary
clean:
	$(RM) $(TARGET)
