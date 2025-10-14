#include "Filter.h"
#include "Image_Class.h"
#include <string>
#include <iostream>

class FlipFilter : public Filter
{
private:
    char dir = 'h';

public:
    FlipFilter(Image& img);
    std::string getName() override;
    static std::string getId();
    void getNeeds() override;
    void apply() override;
};
