#pragma once
#include<string>
#include <chrono>
#include <ctime>
#include <iostream>
using namespace std;

class TimeStamp
{
    /* data */
public: 
    static string getCurrentTimeStamp() {
        auto now = chrono::system_clock::now();
        auto time = chrono::system_clock::to_time_t(now);
        string ts=string(ctime(&time)); // Ends with \n
        ts.pop_back();
        return ts;
    }   

};


