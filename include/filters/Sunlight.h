#pragma once
#include <string>
#include "Filter.h"

#ifndef SUNLIGHT_H
#define SUNLIGHT_H

class Sunlight : public Filter
{
public:
    Sunlight(Image &img);
    string getName();
    static string getId();
    void apply();
    void getNeeds() override;
};

#endif // SUNLIGHT_H
