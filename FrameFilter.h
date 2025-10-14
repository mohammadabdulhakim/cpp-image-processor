#pragma once
#include "Filter.h"
#include <unordered_map>
#include <iostream>
using namespace std;

struct RGB
{
    int R, G, B;
};

class FrameFilter : public Filter {
    int Thickness;
    int R, G, B;
    bool isDecorative;

public:
    FrameFilter(Image& img);
    string getName();
    static string getId();
    void getNeeds() override;
    void apply() override;
};
