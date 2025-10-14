#include "SkyFilter.h"

SkyFilter::SkyFilter(Image& img) : Filter(img) {}

void SkyFilter::getNeeds() {}

std::string SkyFilter::getName() { return "Sky"; }

std::string SkyFilter::getId() { return "21"; }

void SkyFilter::apply()
{
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int blueChannel = 0;
            for (int k = 0; k < image.channels; k++)
            {
                blueChannel += image(x, y, k);
            }
            blueChannel /= image.channels;

            image(x, y, 0) = 0;
            image(x, y, 1) = blueChannel / 2;
            image(x, y, 2) = blueChannel;
        }
    }
}
