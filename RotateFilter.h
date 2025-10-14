#include "Filter.h"
#include "Image_Class.h"
#include <string>
#include <iostream>
#include <cmath>

class RotateFilter : public Filter
{
private:
    int angle;

public:
    RotateFilter(Image& img);
    std::string getName() override;
    static std::string getId();
    void getNeeds() override;
    void apply() override;
};
