#pragma once
#include <string>
#include "Filter.h"

#ifndef SKEWING_H
#define SKEWING_H

class Skewing : public Filter
{
    int angle;

public:
    Skewing(Image &img);
    string getName();
    static string getId();
    void apply() override;

    void getNeeds() override;
};

#endif // SKEWING_H
