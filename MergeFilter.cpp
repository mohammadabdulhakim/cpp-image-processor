#include "MergeFilter.h"
#include <algorithm>
#include <exception>

using namespace std;

MergeFilter::MergeFilter(Image& img) : Filter(img) {}

string MergeFilter::getName() { return "Merge"; }

string MergeFilter::getId() { return "4"; }
string getImagePath(string imgName) {
    return ("assets/" + imgName);
}
void MergeFilter::getNeeds()
{
    cout << "Enter the image's name: ";
    string imgName;
    cin >> imgName;

    cout << "Enter Merge type (1: Stretch to fit, 2: Common): ";
    cin >> mergeType;

    overlay.loadNewImage(getImagePath(imgName));
}

void MergeFilter::apply()
{
    Image& ov = this->overlay;
    Image& base = image;

    try
    {
        int height;
        int width;

        if (base.width == overlay.width && base.height == overlay.height)
        {
            height = base.height;
            width = base.width;
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        base(i, j, k) = (base(i, j, k) + overlay(i, j, k)) / 2;
                    }
                }
            }
        }
        else
        {
            switch (mergeType)
            {
            case 1: // Stretch to fit
            {
                width = max(base.width, overlay.width);
                height = max(base.height, overlay.height);
                resizeImage(base, width, height);
                resizeImage(overlay, width, height);
                for (int i = 0; i < width; i++)
                {
                    for (int j = 0; j < height; j++)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            base(i, j, k) = (base(i, j, k) + overlay(i, j, k)) / 2;
                        }
                    }
                }
                break;
            }
            case 2: // Common area
            {
                Image img(max(base.width, overlay.width),
                    max(base.height, overlay.height));

                for (int i = 0; i < base.width; i++)
                {
                    for (int j = 0; j < base.height; j++)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            img(i, j, k) = base(i, j, k);
                        }
                    }
                }

                for (int i = 0; i < overlay.width; i++)
                {
                    for (int j = 0; j < overlay.height; j++)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            if (i < base.width && j < base.height)
                            {
                                img(i, j, k) = (img(i, j, k) + overlay(i, j, k)) / 2;
                            }
                            else
                            {
                                img(i, j, k) = overlay(i, j, k);
                            }
                        }
                    }
                }

                base = img;
                break;
            }
            default:
                break;
            }
        }
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        throw;
    }
}
