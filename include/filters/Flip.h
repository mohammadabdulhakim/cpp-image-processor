#pragma once
#include "Filter.h"

#ifndef FLIP_H
#define FLIP_H

class Flip : public Filter
{
    char dir = 'h';

public:
    Flip(Image &img);
    string getName();
    static string getId();
    ;

    void getNeeds() override;
    void apply() override;
};

#endif // FLIP_H
