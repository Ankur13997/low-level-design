#pragma once
#include <iostream>

enum class Coin {
    FIVE   = 5,
    TEN    = 10,
    TWENTY = 20
};

inline int getValue(Coin c) {
    return static_cast<int>(c);
}