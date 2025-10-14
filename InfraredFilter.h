#include "Filter.h"
#include "Image_Class.h"
#include <string>

class InfraredFilter : public Filter
{
public:
    InfraredFilter(Image& img);
    void getNeeds() override;
    std::string getName() override;
    static std::string getId();
    void apply() override;
};
