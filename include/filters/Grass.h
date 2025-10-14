#pragma once
#include "Filter.h"

#ifndef GRASS_H
#define GRASS_H

class Grass : public Filter
{
public:
    Grass(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // GRASS_H
