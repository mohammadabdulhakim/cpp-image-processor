#include <string>

#include "../../include/filters/Filter.h"
#include "../../include/filters/WhiteAndBlack.h"
using namespace std;



    WhiteAndBlack::WhiteAndBlack(Image& img) : Filter(img) {};
    string WhiteAndBlack::getName() { return "White and Black"; };
    string WhiteAndBlack::getId() { return "2"; };
    void WhiteAndBlack::apply()
    {
        computeThreshold();
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                unsigned short avg = 0;
                for (int k = 0; k < image.channels; k++)
                {
                    avg += image(i, j, k);
                }

                avg /= image.channels;

                for (int k = 0; k < image.channels; k++)
                {
                    image(i, j, k) = (avg >= (threshold) ? 255 : 0);
                }
            }
        }
    };
    void WhiteAndBlack::getNeeds() {};