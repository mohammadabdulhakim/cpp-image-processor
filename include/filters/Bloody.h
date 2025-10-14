#pragma once
#include "Filter.h"

#ifndef BLOODY_H
#define BLOODY_H

class Bloody : public Filter
{
public:
    Bloody(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // BLOODY_H
