#include "Filter.h"
#include <string>
using namespace std;

class NightFilter : public Filter
{
public:
    NightFilter(Image& img);

    string getName() override;
    static string getId();
    void apply() override;
    void getNeeds() override;
};

