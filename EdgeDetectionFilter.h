#pragma once
#include "Filter.h"
#include "GreyFilter.h"
#include "BlurFilter.h"
#include <map>
#include <vector>
#include <cmath>
using namespace std;

class EdgeDetectionFilter : public Filter {

public:
    EdgeDetectionFilter(Image& img);

    string getName();
    static string getId();
    static map<string, vector<vector<int>>> sobelKernels();
    void getNeeds() override;
    void apply() override;
};
