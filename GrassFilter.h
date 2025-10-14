#include "Filter.h"
#include "Image_Class.h"
#include <string>
class GrassFilter : public Filter
{
public:
    GrassFilter(Image& img);
    void getNeeds() override;
    std::string getName() override;
    static std::string getId();
    void apply() override;
};

