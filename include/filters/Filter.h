#pragma once

#include <string>
#include "../../third_party/Image_Class.h"
using namespace std;

#ifndef FILTER_H
#define FILTER_H

class Filter
{
protected:
    Image &image;
    double threshold = 127;
public:
    Filter(Image &img);
    virtual void apply() = 0;
    virtual void getNeeds() = 0;
    virtual string getName() = 0;
    static string getId() {};

    double computeThreshold();

    double getThreshold();

    bool isInBound(int x, int y);
    static void resizeImage(Image &img, int newW, int newH);
};

#endif // FILTER_H
