#include "Filter.h"
#include "Image_Class.h"
#include <string>
class InvertFilter : public Filter
{
public:
    InvertFilter(Image& img);
    void apply() override;
    std::string getName() override;
    static std::string getId();
    void getNeeds() override;
};

