#include "BrightnessFilter.h"

using namespace std;

BrightnessFilter::BrightnessFilter(Image& img) : Filter(img) {}

string BrightnessFilter::getName() { return "Brightness"; }

string BrightnessFilter::getId() { return "7"; }

void BrightnessFilter::getNeeds()
{
    cout << "Enter the brightness\n"
        << "- 1 normal\n"
        << "- > 1 Brighten\n"
        << "- < 1 Darken\n"
        << "Example: 1.5 will increase brightness by 50%\n==>  ";
    cin >> value;
    cout << "Value is: " << value << '\n';
}

void BrightnessFilter::apply()
{
    cout << "Applying brightness: " << value << '\n';
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int newValue = static_cast<int>(image(i, j, k) * value);
                if (newValue > 255) newValue = 255;
                if (newValue < 0) newValue = 0;
                image(i, j, k) = newValue;
            }
        }
    }
}
