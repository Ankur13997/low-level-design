#pragma once

#include<unordered_map>
#include<mutex>

using namespace std;

/*
In C++17 and later, using inline with global variables like inline std::mutex consoleMutex; allows them to be defined in header files without causing multiple definition errors during linking. This ensures a single shared instance across all translation units. It's especially useful when you need global mutexes accessible in multiple .cpp files.
*/
inline unordered_map<int,mutex>vehiclelock;
inline mutex consoleMutex;