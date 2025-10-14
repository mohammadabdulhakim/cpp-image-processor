#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Filter.h"

using namespace std;

class SkewingFilter : public Filter
{
    int angle;
public:
    SkewingFilter(Image& img) : Filter(img) {};
    string getName() { return "Horizontal Skew"; };
    static string getId() { return "18"; };
    void apply() override;
    void getNeeds() override;
};


