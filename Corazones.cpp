#include "Corazones.h"
#include <string>
#include "CSVData.h"
#include <iostream>
#include <cmath>
#include "nlohmann/json.hpp"
#include <fstream>

#define PATH "Datasets/heart.csv"

HeartDataSet::HeartDataSet()
{
    Data.clear();
    entropy = 0;

    matrix.emplace(Fields::Age , std::vector<int>{ (int)Age::Young , (int)Age::Middle , (int)Age::Old } );
    matrix.emplace(Fields::Sex , std::vector<int>{ (int)Sex::Male , (int)Sex::Female});
    matrix.emplace(Fields::ChestPain , std::vector<int>{ (int)ChestPain::Typical , (int)ChestPain::Atypical , (int)ChestPain::Other , (int)ChestPain::Null } );
    matrix.emplace(Fields::RestingBloodPressure , std::vector<int>{ (int)RestingBloodPressure::Low , (int)RestingBloodPressure::High } );
    matrix.emplace(Fields::Cholestoral , std::vector<int>{ (int)Cholestoral::Low , (int)Cholestoral::High } );
    matrix.emplace(Fields::FastingBloodSugar , std::vector<int>{ (int)FastingBloodSugar::Low , (int)FastingBloodSugar::High } );
    matrix.emplace(Fields::RestingElectroCardio , std::vector<int>{ (int)RestingElectroCardio::Zero , (int)RestingElectroCardio::One , (int)RestingElectroCardio::Two} );
    matrix.emplace(Fields::MaxHeartRate , std::vector<int>{ (int)MaxHeartRate::Low , (int)MaxHeartRate::High} );
    matrix.emplace(Fields::ExerciseAngina , std::vector<int>{ (int)ExerciseAngina::No , (int)ExerciseAngina::Yes } );
    matrix.emplace(Fields::PreviousPeak , std::vector<int>{ (int)PreviousPeak::Low , (int)PreviousPeak::High} );
    matrix.emplace(Fields::Slope , std::vector<int>{ (int)Slope::Null , (int)Slope::Plane , (int)Slope::Low} );
    matrix.emplace(Fields::MajorVesselNum , std::vector<int>{ (int)MajorVesselNum::Zero , (int)MajorVesselNum::One ,(int)MajorVesselNum::Two , (int)MajorVesselNum::Three, (int)MajorVesselNum::Four } );
    matrix.emplace(Fields::Thallasemia , std::vector<int>{ (int)Thallasemia::Null , (int)Thallasemia::Unfixable , (int)Thallasemia::Normal , (int)Thallasemia::Fixable } );
    matrix.emplace(Fields::Output , std::vector<int>{ (int)Output::No , (int)Output::Yes });

    remainingFields = (int)(vFields.size() - 1);
}

void HeartDataSet::readDatasetData()
{
    
    CSVData csvData;

    readCSV( std::string(PATH) , csvData);

    bool isFirstRow = true;
    int rowNum = 0;

    Data.clear();
    // Fills the data vector
    for(auto b : csvData)
    {
        rowNum++;

        if (isFirstRow || rowNum == csvData.size())
        {
            isFirstRow = false;
            continue;
        }

        Data.emplace_back();
        Data.back().resize( (int)Fields::Output + 1);

        

        // Age
        if (stoi(b[0]) < 50)
        {
            Data.back()[(int)Fields::Age] = (int)Age::Young;
        }
        else if (stoi(b[0]) < 65)
        {
            Data.back()[0] = (int)Age::Middle;
            Data.back()[(int)Fields::Age] = (int)Age::Middle;
        }
        else
        {
            Data.back()[(int)Fields::Age] = (int)Age::Old;

        }

        // Gender
        if (stoi(b[1]) == 0)
        {
            Data.back()[(int)Fields::Sex] = (int)Sex::Male;
        }
        else
        {
            Data.back()[(int)Fields::Sex] = (int)Sex::Female;

        }

        // Chest Pain type
        if (stoi(b[2]) == 3)
        {
            Data.back()[(int)Fields::ChestPain] = (int)ChestPain::Null;
        }
        else if (stoi(b[2]) == 2)
        {
            Data.back()[(int)Fields::ChestPain] = (int)ChestPain::Other;
        }
        else if (stoi(b[2]) == 1)
        {
            Data.back()[(int)Fields::ChestPain] = (int)ChestPain::Atypical;
        }
        else if (stoi(b[2]) == 0)
        {
            Data.back()[(int)Fields::ChestPain] = (int)ChestPain::Typical;
        }

        // Resting Blood Pressure
        if (stoi(b[3]) < 125)
        {
            Data.back()[(int)Fields::RestingBloodPressure] = (int)RestingBloodPressure::Low;
        }
        else
        {
            Data.back()[(int)Fields::RestingBloodPressure] = (int)RestingBloodPressure::High;
        }
        
        // Cholestoral
        if (stoi(b[4]) < 240)
        {
            Data.back()[(int)Fields::Cholestoral] = (int)Cholestoral::Low;
        }
        else
        {
            Data.back()[(int)Fields::Cholestoral] = (int)Cholestoral::High;
        }

        // Fasting Blood Sugar
        if (stoi(b[5]) == 0)
        {
            Data.back()[(int)Fields::FastingBloodSugar] = (int)FastingBloodSugar::Low;
        }
        else
        {
            Data.back()[(int)Fields::FastingBloodSugar] = (int)FastingBloodSugar::High;
        }

        // Resting electrocariographic result
        if (stoi(b[6]) == 0)
        {
            Data.back()[(int)Fields::RestingElectroCardio] = (int)RestingElectroCardio::Zero;
        }
        else if (stoi(b[6]) == 1)
        {
            Data.back()[(int)Fields::RestingElectroCardio] = (int)RestingElectroCardio::One;
        }
        else if (stoi(b[6]) == 2)
        {
            Data.back()[(int)Fields::RestingElectroCardio] = (int)RestingElectroCardio::Two;
        }

        // Maximum Heart Rate
        if ( stoi(b[7]) < 150)
        {
            Data.back()[(int)Fields::MaxHeartRate] = (int)MaxHeartRate::Low;
        }
        else
        {
            Data.back()[(int)Fields::MaxHeartRate] = (int)MaxHeartRate::High;
        }

        // Exercise Induced Angina
        if (stoi(b[8]) == 0)
        {
            Data.back()[(int)Fields::ExerciseAngina] = (int)ExerciseAngina::No;
        }
        else if (stoi(b[8]) == 1)
        {
            Data.back()[(int)Fields::ExerciseAngina] = (int)ExerciseAngina::Yes;
        }


        // Old Peak
        if (stoi(b[9]) < 1)
        {
            Data.back()[(int)Fields::PreviousPeak] = (int)PreviousPeak::Low;
        }
        else
        {
            Data.back()[(int)Fields::PreviousPeak] = (int)PreviousPeak::High;
        }
        
        // Slope
        if (stoi(b[10]) == 2)
        {
            Data.back()[(int)Fields::Slope] = (int)Slope::Low;
        }
        else if (stoi(b[10]) == 1)
        {
            Data.back()[(int)Fields::Slope] = (int)Slope::Plane;
        }
        else
        {
            Data.back()[(int)Fields::Slope] = (int)Slope::Null;
        }

        // Number of Major Vessels
        if (stoi(b[11]) == 0)
        {
            Data.back()[(int)Fields::MajorVesselNum] = (int)MajorVesselNum::Zero;
        }
        else if (stoi(b[11]) == 1)
        {
            Data.back()[(int)Fields::MajorVesselNum] = (int)MajorVesselNum::One;
        }
        else if (stoi(b[11]) == 2)
        {
            Data.back()[(int)Fields::MajorVesselNum] = (int)MajorVesselNum::Two;
        }
        else if (stoi(b[11]) == 3)
        {
            Data.back()[(int)Fields::MajorVesselNum] = (int)MajorVesselNum::Three;
        }
        else if (stoi(b[11]) == 4)
        {
            Data.back()[(int)Fields::MajorVesselNum] = (int)MajorVesselNum::Four;
        }

        // Thallasemia
        if ( stoi(b[12]) == 3)
        {
            Data.back()[(int)Fields::Thallasemia] = (int)Thallasemia::Fixable;
        }
        else if ( stoi(b[12]) == 2)
        {
            Data.back()[(int)Fields::Thallasemia] = (int)Thallasemia::Normal;
        }
        else if ( stoi(b[12]) == 1)
        {
            Data.back()[(int)Fields::Thallasemia] = (int)Thallasemia::Unfixable;
        }
        else
        {
            Data.back()[(int)Fields::Thallasemia] = (int)Thallasemia::Null;
        }

        // Output
        if (stoi(b[13]) == 1)
        {
            Data.back()[(int)Fields::Output] = (int)Output::Yes;
        }
        else
        {
            Data.back()[(int)Fields::Output] = (int)Output::No;
        }


    }
    
    setEntropy();
}

void HeartDataSet::setEntropy()
{
    // Calculates the total entropy
    float outputYes = 0.0f;
    float outputNo = 0.0f;
    float dataSize = (float)Data.size();

    
    for (auto b : Data)
    {
        if (b[(int)Fields::Output] == (int)Output::Yes)
        {
            outputYes++;
        }
        else
        {
            outputNo++;
        }
    }

    entropy = (float)(-((float)(outputNo / dataSize) * log2(outputNo / dataSize)) - ((outputYes / dataSize) * log2(outputYes / dataSize)));
}

float HeartDataSet::getEntropy() const
{
    return entropy;
}

float HeartDataSet::getInformationGain(Fields field)
{
    setEntropy();
    float informationGain = entropy;
    float totalCases = (float)Data.size();

    if (field == Fields::Output)
    {
        return 0.0f;
    }

    for (auto b : matrix.at(field))
    {
        float totalBCases = 0;
        float positiveBCases = 0;
        float negativeBCases = 0;
        for (auto c : Data)
        {
            if ( c[(int)field] == b )
            {
                totalBCases++;
                if ( c[(int)Fields::Output] == (int)Output::Yes )
                {
                    positiveBCases++;
                }
                else
                {
                    negativeBCases++;
                }
            }
        }

        // In case this member is called on a field that has already been split
        if ( positiveBCases == totalBCases || negativeBCases == totalBCases)
        {
            return 0.0f;
        }

        float bTerm = - (positiveBCases/totalBCases) * log2(positiveBCases/totalBCases) 
                        - (negativeBCases/totalBCases) * log2(negativeBCases/totalBCases);
        
        informationGain -= (totalBCases/totalCases) * bTerm;

        // std::cout << "bTerm: " << bTerm << std::endl;
    }

    return informationGain;
}

HeartDataSet HeartDataSet::giveFieldChild(int fieldNum, int value)
{
    HeartDataSet child;

    for (auto b : Data)
    {
        if ( b[fieldNum] == value)
        {
            child.Data.push_back(b);
        }
    }

    child.remainingFields = remainingFields - 1;

    return child;
}

int HeartDataSet::getRemainingFields() const
{
    return remainingFields;
}

std::map<Fields, std::vector<int>>& HeartDataSet::getMatrix()
{
    return matrix;
}

void makeTree(HeartDataSet &hds , nlohmann::json &j)
{

    if (hds.getRemainingFields() == 0)
    {
        return;
    }

    if (hds.getRemainingFields() > 0)
    {
        // Finds the field with the highest information gain

        int highestInformationGainField = 0;
        float highestInformationGain = 0.0f;
        float tempInformationGain = 0.0f;

        int fieldIndex = 0;
        Fields maxInformationGainField = Fields::Output;
        for (auto b : vFields)
        {
            tempInformationGain = hds.getInformationGain(b);
            if ( tempInformationGain > highestInformationGain )
            {
                highestInformationGain = tempInformationGain;
                maxInformationGainField = b;
            }
        }
        if (maxInformationGainField == Fields::Output)
        {
            j["values"]["label"] = "Yes";
            j["values"]["label"] = "No";
            return;
        }

        fieldIndex = (int)maxInformationGainField;
        // Creates a node from the highest information gain field

        j["Field"] = fieldText[fieldIndex].c_str();
        j["values"] = {};

        for ( auto v : hds.getMatrix().at(maxInformationGainField) )
        {

            j["values"]["Field"] = std::to_string(v);
            makeTree(hds.giveFieldChild(fieldIndex , v) , j);
        }
    }

    std::ofstream file("tree.json");
    file << j;
    return;
}
