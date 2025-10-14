#include "OilPaintingFilter.h"
#include "Image_CLass.h"
#include <vector>
#include <string>
#include <iostream>

class PaintingFilter : public OilPaintingFilter
{
private:
    int radius;

public:
    PaintingFilter(Image& img);
    void getNeeds() override;
    std::string getName() override;
    static std::string getId();
    void apply() override;

private:
    bool isInBound(int x, int y);
};
