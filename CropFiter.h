#include "Filter.h"
#include "Image_CLass.h"
#include <iostream>
#include <string>

class CropFilter : public Filter
{
private:
    int corner[2]{ 0, 0 };
    int dimensions[2]{ 100, 100 };

public:
    CropFilter(Image& img);
    std::string getName() override;
    static std::string getId();
    void getNeeds() override;
    void apply() override;
};
