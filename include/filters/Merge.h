#pragma once
#include <string>
#include "Filter.h"

#ifndef MERGE_H
#define MERGE_H

class Merge : public Filter
{
    Image overlay;
    int mergeType = 1;

public:
    Merge(Image &img);
    string getName();
    static string getId();

    void getNeeds() override;
    void apply() override;
};

#endif // MERGE_H
