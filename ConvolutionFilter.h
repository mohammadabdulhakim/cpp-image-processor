#pragma once
#include "Filter.h"
#include <vector>
using namespace std;

class ConvolutionFilter : public Filter {
    vector<vector<int>> kernel;
    int divisor;

public:
    ConvolutionFilter(Image& img, vector<vector<int>> kernel, int divisor = 1);
    void apply() override;
};
