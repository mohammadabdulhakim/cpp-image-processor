#pragma once
#include "Filter.h"

#ifndef OILPAINTING_H
#define OILPAINTING_H

class OilPainting : public Filter
{
protected:
    int intensityLevels;

public:
    OilPainting(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // OILPAINTING_H
