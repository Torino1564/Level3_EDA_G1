#pragma once

#include "nlohmann/json.hpp"
#include "raylib.h"
#include <vector>
#include <map>
#include <string>

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
enum class MajorVesselNum { Zero , One , Two , Three, Four };
enum class Thallasemia { Null , Unfixable , Normal , Fixable };
enum class Output { No , Yes};

enum class Fields {Age , Sex, ChestPain , RestingBloodPressure , Cholestoral , FastingBloodSugar ,
                    RestingElectroCardio , MaxHeartRate , ExerciseAngina , PreviousPeak , Slope ,
                    MajorVesselNum ,Thallasemia , Output};

static std::vector<Fields> vFields = { Fields::Age , Fields::Sex , Fields::ChestPain , Fields::RestingBloodPressure , 
                                Fields::Cholestoral , Fields::FastingBloodSugar , Fields:: RestingElectroCardio,
                                Fields::MaxHeartRate , Fields::ExerciseAngina , Fields::PreviousPeak , 
                                Fields::Slope , Fields::MajorVesselNum , Fields::Thallasemia , Fields::Output };

static std::vector<std::string> fieldText = { std::string("Age") , std::string("Sex") , std::string("Chest Pain") , 
    std::string("Resting Blood Pressure") , std::string("Cholestoral") , std::string("Fasting Blood Sugar") , 
    std::string("Resting Electrocardiographic result") , std::string("Max Heart Rate") , std::string("Exercise Caused Angina"),
    std::string("Old peak") , std::string("Slope") , std::string("Major Blood Vessel Number") , std::string("Thallasemia") , 
    std::string("Output")

};

class HeartDataSet
{
public:
    HeartDataSet();
    void readDatasetData();
    void setEntropy();
    float getEntropy() const;
    float getInformationGain( Fields field );
    HeartDataSet giveFieldChild(int fieldNum, int value);
    std::vector<std::vector<int>> Data;
    int getRemainingFields() const;
    std::map<Fields , std::vector<int>>& getMatrix();
private:
    float entropy;
    std::map<Fields , std::vector<int>> matrix;
    int remainingFields;
};

void makeTree( HeartDataSet &hds , nlohmann::json &j );



