#pragma once
#include "Filter.h"

#ifndef CROP_H
#define CROP_H

class Crop : public Filter
{
    int corner[2]{0};
    int dimensions[2]{100};

public:
    Crop(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // CROP_H
