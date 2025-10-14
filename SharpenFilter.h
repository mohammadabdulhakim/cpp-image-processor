#pragma once
#include "ConvolutionFilter.h"

class SharpenFilter : public ConvolutionFilter {

public:
    SharpenFilter(Image& img);
    void getNeeds() override;
    string getName() override;
    static string getId();
};
