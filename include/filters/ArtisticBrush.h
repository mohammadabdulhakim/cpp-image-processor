#pragma once
#include "OilPainting.h"

#ifndef ARTISTICBRUSH_H
#define ARTISTICBRUSH_H

class ArtisticBrush : public OilPainting
{
    int radius;

public:
    ArtisticBrush(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // ARTISTICBRUSH_H
