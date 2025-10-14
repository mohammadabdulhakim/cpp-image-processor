#include "OilPaintingFilter.h"
#include <iostream>

using namespace std;

OilPaintingFilter::OilPaintingFilter(Image& img)
    : Filter(img), intensityLevels() 
{

}

void OilPaintingFilter::getNeeds()
{
    cout << "How detailed should the painting look? (10–30): ";
    cin >> intensityLevels;
}

string OilPaintingFilter::getName()
{
    return "Oil Painting";
}

string OilPaintingFilter::getId()
{
    return "14";
}

void OilPaintingFilter::apply()
{
    Image output(image.width, image.height);

    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            for (int k = 0; k < image.channels; k++)
            {
                int intensity = image(x, y, k);
                int binIndex = (intensity * intensityLevels) / 255;
                if (binIndex >= intensityLevels)
                    binIndex = intensityLevels - 1;

                int newIntensity = (binIndex * 255) / (intensityLevels - 1);
                output(x, y, k) = newIntensity;
            }
        }
    }

    image = output;
}
