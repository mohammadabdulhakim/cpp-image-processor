#pragma once
#include "Filter.h"

#ifndef ROTATE_H
#define ROTATE_H

class Rotate : public Filter
{
    int angle;

public:
    Rotate(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // ROTATE_H
