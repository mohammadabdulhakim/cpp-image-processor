#include "Filter.h"
#include <string>

using namespace std;

class SunlightFilter : public Filter
{
public:
    SunlightFilter(Image& img);

    string getName() override;
    static string getId();
    void apply() override;
    void getNeeds() override;
};

