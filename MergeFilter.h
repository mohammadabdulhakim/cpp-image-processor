#include "Filter.h"
#include "Image_Class.h"
#include <iostream>
#include <string>

class MergeFilter : public Filter
{
private:
    Image overlay;
    int mergeType = 1;

public:
    MergeFilter(Image& img);
    std::string getName() override;
    static std::string getId();
    void getNeeds() override;
    void apply() override;
};