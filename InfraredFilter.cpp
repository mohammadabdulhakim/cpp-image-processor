#include "InfraredFilter.h"

InfraredFilter::InfraredFilter(Image& img) : Filter(img) {}

void InfraredFilter::getNeeds() {}

std::string InfraredFilter::getName() { return "Infrared"; }

std::string InfraredFilter::getId() { return "17"; }

void InfraredFilter::apply()
{
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int redChannel = 0;
            for (int k = 0; k < image.channels; k++)
            {
                redChannel += image(x, y, k);
            }
            redChannel /= image.channels;

            image(x, y, 0) = 255;
            image(x, y, 1) = 255 - redChannel;
            image(x, y, 2) = 255 - redChannel;
        }
    }
}
