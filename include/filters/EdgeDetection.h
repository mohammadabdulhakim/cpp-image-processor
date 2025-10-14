#pragma once
#include "Filter.h"

#include <map>
#include <vector>

#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

class EdgeDetection : public Filter
{
public:
    EdgeDetection(Image &img);
    string getName();
    map<string, vector<vector<int>>> sobelKernels();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // EDGEDETECTION_H
