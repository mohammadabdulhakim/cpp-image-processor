#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include "Image_Class.h"  // تأكد إنك عامل كلاس Image وموجود في ملف الهيدر ده

using namespace std;

class Filter
{
protected:
    Image& image;
    double threshold = 127;

public:
    Filter(Image& img);
    virtual ~Filter() = default;

    virtual void apply() = 0;
    virtual void getNeeds() = 0;
    virtual string getName() = 0;

    double computeThreshold();
    double getThreshold();

    bool isInBound(int x = 0, int y = 0);

    static void resizeImage(Image& img, int newW, int newH);
};

#endif // FILTER_H
