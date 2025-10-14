#pragma once
#include <string>
#include "Filter.h"

#ifndef NIGHT_H
#define NIGHT_H

class Night : public Filter
{
public:
    Night(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // NIGHT_H
