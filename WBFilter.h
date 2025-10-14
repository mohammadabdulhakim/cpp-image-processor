#include <iostream>
#include "Filter.h"
using namespace std;

class WBFilter : public Filter
{
public:
    WBFilter(Image& img) : Filter(img) {};
    string getName() { return "White and Black"; };
    static string getId() { return "2"; };
    void apply() override;
    void getNeeds() override;
};