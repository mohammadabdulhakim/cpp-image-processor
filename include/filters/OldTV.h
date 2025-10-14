#pragma once
#include <string>
#include "Filter.h"

#ifndef OLDTV_H
#define OLDTV_H

class OldTV : public Filter
{
public:
    OldTV(Image &img);
    string getName();
    static string getId();
    void apply() override;
    void getNeeds() override;
};

#endif // OLDTV_H
