#pragma once
#include "Filter.h"

#ifndef SKY_H
#define SKY_H

class Sky : public Filter
{
public:
    Sky(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // SKY_H
