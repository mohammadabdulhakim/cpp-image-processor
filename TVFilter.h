#pragma once
#include<iostream>
#include<string>
#include"Filter.h"
using namespace std; 

class TVFilter : public Filter
{
public:
    TVFilter(Image& img);
    string getName() override;
    static string getId();
    void apply() override;
    void getNeeds() override;
};

