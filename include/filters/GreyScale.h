#pragma once
#include "Filter.h"

#ifndef GREYSCALE_H
#define GREYSCALE_H

class GreyScale : public Filter
{
public:
    GreyScale(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // GREYSCALE_H
