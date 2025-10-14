#pragma once
#include "Filter.h"
#include <vector>
#include <algorithm>

using namespace std;

#ifndef CONVOLUTIONFILTER_H
#define CONVOLUTIONFILTER_H

class ConvolutionFilter : public Filter
{
    vector<vector<int>> kernel;
    int divisor;

public:
    ConvolutionFilter(Image &img, vector<vector<int>> kernel, int divisor = 1) : Filter(img), kernel(kernel), divisor(divisor) {};
    void apply() override
    {
        Image output(image.width, image.height);

        for (int x = 1; x < image.width - 1; x++)
        {
            for (int y = 1; y < image.height - 1; y++)
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;

                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        sumR += image(x + i, y + j, 0) * kernel[i + 1][j + 1];
                        sumG += image(x + i, y + j, 1) * kernel[i + 1][j + 1];
                        sumB += image(x + i, y + j, 2) * kernel[i + 1][j + 1];
                    }
                }

                output(x, y, 0) = clamp(sumR / divisor, 0, 255);
                output(x, y, 1) = clamp(sumG / divisor, 0, 255);
                output(x, y, 2) = clamp(sumB / divisor, 0, 255);
            }
        }

        image = output;
    }
};
class SharpenFilter : public ConvolutionFilter
{

public:
    SharpenFilter(Image &img) : ConvolutionFilter(img, {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}}) {};
    void getNeeds() override {};
    string getName() override { return "Sharpen"; }
    static string getId() { return "40"; }
};

#endif // CONVOLUTIONFILTER_H
