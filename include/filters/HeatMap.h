#pragma once
#include "Filter.h"


class HeatMap : public Filter
{
public:
    HeatMap(Image& img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};