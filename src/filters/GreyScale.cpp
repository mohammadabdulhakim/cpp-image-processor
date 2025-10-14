#include "../../include/filters/Filter.h"
#include "../../include/filters/GreyScale.h"


    GreyScale::GreyScale(Image& img) : Filter(img) {};
    string GreyScale::getName() { return "Grey Scale"; };
    string GreyScale::getId() { return "1"; };
    void GreyScale::apply()
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
    void GreyScale::getNeeds() {};