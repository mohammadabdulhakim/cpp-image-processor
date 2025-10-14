#include "Filter.h"
#include "Image_Class.h"
#include <string>
#include <iostream>

class BrightnessFilter : public Filter
{
private:
    double value;

public:
    BrightnessFilter(Image& img);
    std::string getName() override;
    static std::string getId();
    void getNeeds() override;
    void apply() override;
};