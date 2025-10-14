#include "GrassFilter.h"

GrassFilter::GrassFilter(Image& img) : Filter(img) {}

void GrassFilter::getNeeds() {}

std::string GrassFilter::getName() { return "Grass"; }

std::string GrassFilter::getId() { return "20"; }

void GrassFilter::apply()
{
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int intensity = 0;
            for (int k = 0; k < image.channels; k++)
            {
                intensity += image(x, y, k);
            }
            intensity /= image.channels;

            image(x, y, 0) = 0;
            image(x, y, 1) = intensity;
            image(x, y, 2) = 0;
        }
    }
}
