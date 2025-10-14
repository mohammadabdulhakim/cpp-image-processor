#include "InvertFilter.h"
using namespace std;

InvertFilter::InvertFilter(Image& img) : Filter(img) {}

void InvertFilter::apply()
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}

string InvertFilter::getName() { return "Invert"; }

string InvertFilter::getId() { return "3"; }

void InvertFilter::getNeeds() {}
