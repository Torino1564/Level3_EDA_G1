#include "Corazones.h"
#include "nlohmann/json.hpp"
#include "raylib.h"
#include <iostream>

using namespace nlohmann;

int main(int, char *[])
{
    HeartDataSet hds;
    hds.readDatasetData();

    std::cout << "The entropy of the loaded DataSet is: " << hds.getEntropy() << std::endl;

    hds.getInformationGain(Fields::MaxHeartRate);

    return 0;
}