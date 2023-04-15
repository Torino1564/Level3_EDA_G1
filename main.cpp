#include "Corazones.h"
#include "nlohmann/json.hpp"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace nlohmann;

int main(int, char *[])
{
    HeartDataSet hds;
    hds.readDatasetData();
    json j;
    makeTree(hds , j);

    return 0;
}