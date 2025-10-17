#pragma once
#include "Filter.h"
#include <algorithm>
#include <cmath>
#include"../../include/filters/STRUCT.h",
class saturation : public Filter
{
    double p; 
public:
    saturation(Image& img);
    string getName();
    static string getId();
    void apply() override;
private:
    HSV saturation::rgbToHsv(const RGB& rgb);
    RGB saturation::hsvToRgb(const HSV& hsv); void getNeeds() override;
};

