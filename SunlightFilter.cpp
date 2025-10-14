#include "SunlightFilter.h"

SunlightFilter::SunlightFilter(Image& img) : Filter(img) {}

string SunlightFilter::getName() 
{
    return "Sunlight";
}
string SunlightFilter::getId() 
{
    return "13";
}

void SunlightFilter::apply() {
    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) 
        {
            double r = 1.1 * image(i, j, 0);
            if (r > 255) r = 255;
            image(i, j, 0) = r;

            double g = 1.2 * image(i, j, 1);
            if (g > 255) g = 255;
            image(i, j, 1) = g;

            double b = 0.7 * image(i, j, 2);
            if (b < 0) b = 0;
            image(i, j, 2) = b;
        }
    }
}

void SunlightFilter::getNeeds() {
}
