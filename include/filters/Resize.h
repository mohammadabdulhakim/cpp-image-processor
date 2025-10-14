#pragma once
#include "Filter.h"

#ifndef RESIZE_H
#define RESIZE_H

class Resize : public Filter
{
    int dimensions[2]{100};

public:
    Resize(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // RESIZE_H
