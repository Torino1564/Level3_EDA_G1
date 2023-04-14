#pragma once

#include "nlohmann/json.hpp"
#include "raylib.h"
#include <vector>

class HeartDataSetField
{
public:
    int age;
    bool sex;
    float chestPain;
    float restingBloodPressure;
    float cholestoral;
    float fastingBloodSugar;
    float restingElectroCardio;
    float maxHeartRate;
    bool exerciseAngina;
    float previousPeak;
};

class HeartDataSet
{
public:
    HeartDataSet() = default;
    static std::vector<HeartDataSetField> csvData;
};



