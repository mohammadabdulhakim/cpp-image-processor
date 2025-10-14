#ifndef OILPAINTINGFILTER_H
#define OILPAINTINGFILTER_H

#include "Filter.h"
#include "Image_Class.h"
#include <string>
#include <iostream>

class OilPaintingFilter : public Filter
{
protected:
    int intensityLevels;

public:
    OilPaintingFilter(Image& img);
    void getNeeds() override;
    std::string getName() override;
    static std::string getId();
    void apply() override;
};
#endif