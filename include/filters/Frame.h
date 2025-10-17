#pragma once
#include "Filter.h"
#include"../../include/filters/STRUCT.h",

#ifndef FRAME_H
#define FRAME_H

class Frame : public Filter
{
    int Thickness;
    int R, G, B;
    bool isDecorative;

public:
    Frame(Image &img);

    string getName();
    static string getId();

    void getNeeds() override;
    void apply() override;
};

#endif // FRAME_H
