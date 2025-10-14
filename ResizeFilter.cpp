#include "ResizeFilter.h"
#include <iostream>

using namespace std;

ResizeFilter::ResizeFilter(Image& img) : Filter(img) {}

string ResizeFilter::getName() { return "Resizing"; }

string ResizeFilter::getId() { return "11"; }

void ResizeFilter::getNeeds()
{
    cout << "Please enter the new dimensions of the image. (width height): ";
    cin >> dimensions[0] >> dimensions[1];
}

void ResizeFilter::apply()
{
    resizeImage(image, dimensions[0], dimensions[1]);
}
