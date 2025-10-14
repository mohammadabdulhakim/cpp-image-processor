#include <string>

#include "../../include/filters/Filter.h"
#include "../../include/filters/Night.h"
using namespace std;


    Night::Night(Image& img) : Filter(img) {};
    string Night::getName() { return "Night"; };
    string Night::getId() { return "16"; };
    void Night::apply()
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                double r = 1.4 * image(i, j, 0);
                if (r > 255)
                {
                    r = 255;
                }
                image(i, j, 0) = r;
                double g = 0.7 * image(i, j, 1);
                if (g < 0)
                {
                    g = 0;
                }
                image(i, j, 1) = g;
                double b = 1.6 * image(i, j, 2);
                if (b > 255)
                {
                    b = 255;
                }
                image(i, j, 2) = b;
            }
        }

    }
    void Night::getNeeds() {};