#include "SharpenFilter.h"

SharpenFilter::SharpenFilter(Image& img)
    : ConvolutionFilter(img, { {-1,-1,-1}, {-1,8,-1}, {-1,-1,-1} }) {
}

void SharpenFilter::getNeeds() {}

string SharpenFilter::getName() {
    return "Sharpen";
}

string SharpenFilter::getId() {
    return "40";
}
