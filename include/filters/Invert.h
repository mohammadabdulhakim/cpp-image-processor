#pragma once
#include "Filter.h"

#ifndef INVERT_H
#define INVERT_H

class Invert : public Filter
{
public:
    Invert(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // INVERT_H
