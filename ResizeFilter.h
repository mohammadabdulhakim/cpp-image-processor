
#include "Filter.h"
#include "Image_Class.h"
#include <iostream>
#include <string>

class ResizeFilter : public Filter
{
private:
    int dimensions[2]{ 100, 100 };

public:
    ResizeFilter(Image& img);
    std::string getName() override;
    static std::string getId();
    void getNeeds() override;
    void apply() override;
};

