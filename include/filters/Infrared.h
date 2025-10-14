#pragma once
#include "Filter.h"

#ifndef INFRARED_H
#define INFRARED_H

class Infrared : public Filter
{
public:
    Infrared(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // INFRARED_H
