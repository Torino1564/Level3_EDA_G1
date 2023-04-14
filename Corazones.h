#pragma once

#include "nlohmann/json.hpp"
#include "raylib.h"
#include <vector>

enum class Age { Young , Middle , Old };
enum class Sex { Male , Female };
enum class ChestPain {Typical , Atypical , Other , Null};
enum class RestingBloodPressure {Low , High};
enum class Cholestoral { Low , High };
enum class FastingBloodSugar {Low , High};
enum class MaxHeartRate { Low , High};
enum class PreviousPeak { Low , High };
enum class Slope {Null , Plane , Low};
enum class Thallasemia { Null , Unfixable , Normal , Fixable };
enum class Output { No , Yes};
enum class Fields {Age , Sex, ChestPain , RestingBloodPressure , Cholestoral , FastingBloodSugar ,
                    RestingElectroCardio , MaxHeartRate , ExerciseAngina , PreviousPeak , Slope ,
                    Thallasemia , Output};

class HeartDataSetField
{
public:
    HeartDataSetField() = default;

    Age age;
    Sex sex;
    ChestPain chestPain;
    RestingBloodPressure restingBloodPressure;
    Cholestoral cholestoral;
    FastingBloodSugar fastingBloodSugar;
    int restingElectroCardio;
    MaxHeartRate maxHeartRate;
    int exerciseAngina;
    PreviousPeak previousPeak;
    Slope slope;
    Thallasemia thallasemia;
    Output output;
};

class HeartDataSet
{
public:
    HeartDataSet();
    void readDatasetData();
    void makeTree();
    void setEntropy();
    float getEntropy();
    float getInformationGain( Fields field );
    std::vector<HeartDataSetField> Data;
private:
    float entropy;
};



