#include "../../include/filters/Filter.h"
#include "../../include/filters/Flip.h"


    Flip::Flip(Image& img) : Filter(img) {};
    string Flip::getName() { return "Flip"; };
    string Flip::getId() { return "5"; };

    void Flip::getNeeds()
    {
        cout << "Do you want to flip the image (v)ertically or (h)orizontally: ";
        cin >> dir;
    }
    void Flip::apply()
    {
        if (dir == 'h')
        {
            for (int i = 0; i < image.height; i++)
            {
                for (int j = 0; j < image.width / 2; j++)
                {
                    int tempChannels[3] = { 0 };
                    for (int k = 0; k < image.channels; k++)
                    {
                        tempChannels[k] = image(j, i, k);
                    }

                    for (int k = 0; k < image.channels; k++)
                    {
                        image(j, i, k) = image(image.width - j - 1, i, k);
                    }

                    for (int k = 0; k < image.channels; k++)
                    {
                        image(image.width - j - 1, i, k) = tempChannels[k];
                    }
                }
            }
        }
        else
        {
            for (int j = 0; j < image.width; j++)
            {
                for (int i = 0; i < image.height / 2; i++)
                {
                    int tempChannels[3] = { 0 };
                    for (int k = 0; k < image.channels; k++)
                    {
                        tempChannels[k] = image(j, i, k);
                    }

                    for (int k = 0; k < image.channels; k++)
                    {
                        image(j, i, k) = image(j, image.height - i - 1, k);
                    }

                    for (int k = 0; k < image.channels; k++)
                    {
                        image(j, image.height - i - 1, k) = tempChannels[k];
                    }
                }
            }
        }
    }
