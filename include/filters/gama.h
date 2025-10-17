#pragma once 
#include "../../include/filters/Filter.h"


class gama : public Filter
{
    double Gama;
public:
    gama(Image& img);
    string getName();
    static string getId();
    void apply();
    void getNeeds() override;
};
