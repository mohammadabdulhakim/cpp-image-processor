#include "GreyFilter.h"

void GreyFilter::apply()
{
    try
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                unsigned int avg = 0;

                for (int k = 0; k < 3; k++)
                {
                    avg += image(i, j, k);
                }

                avg /= image.channels; // average
                for (int k = 0; k < image.channels; k++)
                {
                    image(i, j, k) = avg;
                }
            }
        }
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        throw;
    }
}

void GreyFilter::getNeeds()
{
    // No input needed
}
