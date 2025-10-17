#pragma once

#include "Filter.h"

class OldPhoto : public Filter
{
public:

    OldPhoto(Image& img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

