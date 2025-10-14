#pragma once
#include <string>
#include <vector>
#include "Filter.h"

#ifndef BLUR_H
#define BLUR_H

class Blur : public Filter
{
    int radius;

public:
    Blur(Image &img, int r = 10);
    string getName();
    static string getId();

    void Prefix_sum(Image &image, vector<vector<ll>> &prefixR, vector<vector<ll>> &prefixG, vector<vector<ll>> &prefixB);
    void apply() override;
    void getNeeds() override;
};

#endif // BLUR_H
