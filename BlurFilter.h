#ifndef BLURFILTER_H
#define BLURFILTER_H
#include "Filter.h"
#include <vector>
#include <iostream>
using namespace std;
#define ll long long 
class BlurFilter : public Filter {
    int radius;

public:
    BlurFilter(Image& img, int r = 10);
    string getName() override;
    static string getId();
    void Prefix_sum(Image& image, vector<vector<ll>>& prefixR, vector<vector<ll>>& prefixG, vector<vector<ll>>& prefixB);
    void apply() override;
    void getNeeds() override;
};

#endif