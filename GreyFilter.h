#ifndef GRAYFILTER_H
#define GRAYFILTER_H
#include <iostream>
#include "Filter.h"
using namespace std;

class GreyFilter : public Filter
{
public:
    GreyFilter(Image& img) : Filter(img) {};
    string getName() { return "Grey Scale"; };
    static string getId() { return "1"; };
    void apply() override;
    void getNeeds() override;
};
#endif