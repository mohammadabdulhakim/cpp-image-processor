#include <string>

#include "../../include/filters/Filter.h"
#include "../../include/filters/Sunlight.h"
using namespace std;


    Sunlight::Sunlight(Image& img) : Filter(img) {};
    string Sunlight::getName() { return "Sunlight"; };
     string Sunlight::getId() { return "13"; };
    void Sunlight::apply()
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                double r = 1.1 * image(i, j, 0);
                if (r > 255)
                {
                    r = 255;
                }
                image(i, j, 0) = r;
                double g = 1.2 * image(i, j, 1);
                if (g > 255)
                {
                    g = 255;
                }
                image(i, j, 1) = g;
                double b = 0.7 * image(i, j, 2);
                if (b < 0)
                {
                    b = 0;
                }
                image(i, j, 2) = b;
            }
        }
    }
    void Sunlight::getNeeds() {};