#pragma once

#include "nlohmann/json.hpp"
#include "raylib.h"
#include <vector>
#include <map>

enum class Age { Young , Middle , Old };
enum class Sex { Male , Female };
enum class ChestPain {Typical , Atypical , Other , Null};
enum class RestingBloodPressure {Low , High};
enum class Cholestoral { Low , High };
enum class FastingBloodSugar {Low , High};
enum class RestingElectroCardio { Zero , One , Two };
enum class MaxHeartRate { Low , High};
enum class ExerciseAngina { No , Yes };
enum class PreviousPeak { Low , High };
enum class Slope {Null , Plane , Low};
enum class Thallasemia { Null , Unfixable , Normal , Fixable };
enum class Output { No , Yes};

enum class Fields {Age , Sex, ChestPain , RestingBloodPressure , Cholestoral , FastingBloodSugar ,
                    RestingElectroCardio , MaxHeartRate , ExerciseAngina , PreviousPeak , Slope ,
                    Thallasemia , Output};


class HeartDataSet
{
public:
    HeartDataSet();
    void readDatasetData();
    void makeTree();
    void setEntropy();
    float getEntropy();
    float getInformationGain( Fields field );
    std::vector<std::vector<int>> Data;
private:
    float entropy;
    std::map<Fields , std::vector<int>> matrix;
};



