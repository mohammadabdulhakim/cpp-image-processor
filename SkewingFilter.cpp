#include "SkewingFilter.h"

void SkewingFilter::apply()
{
    try
    {
        double tan_angle = tan(angle * M_PI / 180);
        double slope = -tan_angle;
        int new_width = image.width + abs(image.height * slope);
        int checker = 0;
        if (slope < 0)
        {
            checker = abs(image.height * slope);
        }

        Image Skewed_image(new_width, image.height);
        for (int x = 0; x < image.width; x++)
        {
            for (int y = 0; y < image.height; y++)
            {
                double X = x + (slope * y) + checker;
                for (int k = 0; k < 3; k++)
                {
                    if (X >= 0 && X < new_width)
                    {
                        Skewed_image((int)X, y, k) = image(x, y, k);
                    }
                }
            }
        }
        image = Skewed_image;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

void SkewingFilter::getNeeds() 
{
    cout << "Enter skew angle : "; cin >> angle;
}
