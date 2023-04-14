#include "Corazones.h"
#include <string>
#include "CSVData.h"
#include <iostream>
#include <cmath>

#define PATH "Datasets/heart.csv"

HeartDataSet::HeartDataSet()
{
    Data.clear();
    entropy = 0;
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
        Data.emplace_back();

        if (isFirstRow || rowNum == csvData.size())
        {
            isFirstRow = false;
            continue;
        }

        // Age
        if (stoi(b[0]) < 50)
        {
            Data.back().age = Age::Young;
        }
        else if (stoi(b[0]) < 65)
        {
            Data.back().age = Age::Middle;
        }
        else
        {
            Data.back().age = Age::Old;

        }

        // Gender
        if (stoi(b[1]) == 0)
        {
            Data.back().sex = Sex::Male;
        }
        else
        {
            Data.back().sex = Sex::Female;

        }

        // Chest Pain type
        if (stoi(b[2]) == 3)
        {
            Data.back().chestPain = ChestPain::Null;
        }
        else if (stoi(b[2]) == 2)
        {
            Data.back().chestPain = ChestPain::Other;
        }
        else if (stoi(b[2]) == 1)
        {
            Data.back().chestPain = ChestPain::Atypical;
        }
        else if (stoi(b[2]) == 0)
        {
            Data.back().chestPain = ChestPain::Typical;
        }

        // Resting Blood Pressure
        if (stoi(b[3]) < 125)
        {
            Data.back().restingBloodPressure = RestingBloodPressure::Low;
        }
        else
        {
            Data.back().restingBloodPressure = RestingBloodPressure::High;
        }
        
        // Cholestoral
        if (stoi(b[4]) < 240)
        {
            Data.back().cholestoral = Cholestoral::Low;
        }
        else
        {
            Data.back().cholestoral = Cholestoral::High;
        }

        // Fasting Blood Sugar
        if (stoi(b[5]) == 0)
        {
            Data.back().fastingBloodSugar = FastingBloodSugar::Low;
        }
        else
        {
            Data.back().fastingBloodSugar = FastingBloodSugar::High;
        }

        // Resting electrocariographic result
        Data.back().restingElectroCardio = stoi(b[6]);

        // Maximum Heart Rate
        if ( stoi(b[6]) < 150)
        {
            Data.back().maxHeartRate = MaxHeartRate::Low;
        }
        else
        {
            Data.back().maxHeartRate = MaxHeartRate::High;
        }

        // Exercise Induced Angina
        Data.back().exerciseAngina = stoi(b[7]);        

        // Old Peak
        if (stoi(b[8]) < 1)
        {
            Data.back().previousPeak = PreviousPeak::Low;
        }
        else
        {
            Data.back().previousPeak = PreviousPeak::High;
        }
        
        // Slope
        if (stoi(b[9]) == 2)
        {
            Data.back().slope = Slope::Low;
        }
        else if (stoi(b[9]) == 1)
        {
            Data.back().slope = Slope::Plane;
        }
        else
        {
            Data.back().slope = Slope::Null;
        }

        // Thallasemia
        if ( stoi(b[10]) == 3)
        {
            Data.back().thallasemia = Thallasemia::Fixable;
        }
        else if ( stoi(b[10]) == 2)
        {
            Data.back().thallasemia = Thallasemia::Normal;
        }
        else if ( stoi(b[10]) == 1)
        {
            Data.back().thallasemia = Thallasemia::Unfixable;
        }
        else
        {
            Data.back().thallasemia = Thallasemia::Null;
        }

        // Output
        if (stoi(b[11]) == 1)
        {
            Data.back().output = Output::Yes;
        }
        else
        {
            Data.back().output = Output::No;
        }


    }
    
    setEntropy();
}

void HeartDataSet::makeTree()
{

}

void HeartDataSet::setEntropy()
{
    // Calculates the total entropy
    float outputYes = 0.0f;
    float outputNo = 0.0f;
    float dataSize = (float)Data.size();

    
    for (auto b : Data)
    {
        if (b.output == Output::Yes)
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

float HeartDataSet::getEntropy()
{
    return entropy;
}

float HeartDataSet::getInformationGain(Fields field)
{
    setEntropy();

    float totalCases = Data.size();

    switch (field)
    {
    case Fields::Age :
    {
        float casesYoung = 0;
        float casesMiddle = 0;
        float casesOld = 0;

        for (auto b : Data)
        {
            if (b.age == Age::Young) casesYoung++;
            else if (b.age == Age::Middle) casesMiddle++;
            else if (b.age == Age::Old) casesOld++;
        }

        return entropy - (casesYoung / totalCases) * log2(casesYoung / totalCases)
                    - (casesMiddle / totalCases) * log2(casesMiddle / totalCases)
                    - (casesOld / totalCases) * log2(casesOld / totalCases);
    }
    break;

    case Fields::Sex:
    {
        float casesMale = 0;
        float casesFemale = 0;

        for (auto b : Data)
        {
            if (b.sex == Sex::Male) casesMale++;
            else if (b.sex == Sex::Female) casesFemale++;
        }

        return entropy - (casesMale/totalCases) * log2(casesMale/totalCases)
                    - (casesFemale) * log2(casesFemale/totalCases);
    }
    break;

    case Fields::ChestPain:
    {

    }
    
    default:
        break;
    }
}
