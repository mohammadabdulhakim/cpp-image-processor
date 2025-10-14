#include "PaintingFilter.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

PaintingFilter::PaintingFilter(Image& img)
    : OilPaintingFilter(img), radius(2)
{
}

void PaintingFilter::getNeeds()
{
    cout << "How wide should the brush strokes be? (3–7 recommended 2): ";
    cin >> radius;
    OilPaintingFilter::getNeeds();
}

string PaintingFilter::getName()
{
    return "Painting";
}

string PaintingFilter::getId()
{
    return "22";
}

bool PaintingFilter::isInBound(int x, int y)
{
    return x >= 0 && x < image.width && y >= 0 && y < image.height;
}

void PaintingFilter::apply()
{
    Image output(image.width, image.height);

    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            vector<int> intensityCount(intensityLevels, 0);
            vector<int> avgR(intensityLevels, 0);
            vector<int> avgG(intensityLevels, 0);
            vector<int> avgB(intensityLevels, 0);

            for (int ny = y - radius; ny <= y + radius; ny++)
            {
                for (int nx = x - radius; nx <= x + radius; nx++)
                {
                    if (isInBound(nx, ny))
                    {
                        int r = image(nx, ny, 0);
                        int g = image(nx, ny, 1);
                        int b = image(nx, ny, 2);

                        int intensity = (r + g + b) / 3;
                        int binIndex = (intensity * (intensityLevels - 1)) / 255;

                        intensityCount[binIndex]++;
                        avgR[binIndex] += r;
                        avgG[binIndex] += g;
                        avgB[binIndex] += b;
                    }
                }
            }

            int maxBin = 0;
            int maxCount = 0;
            for (int i = 0; i < intensityLevels; i++)
            {
                if (intensityCount[i] > maxCount)
                {
                    maxCount = intensityCount[i];
                    maxBin = i;
                }
            }

            if (maxCount > 0)
            {
                output(x, y, 0) = avgR[maxBin] / maxCount;
                output(x, y, 1) = avgG[maxBin] / maxCount;
                output(x, y, 2) = avgB[maxBin] / maxCount;
            }
        }
    }

    image = output;
}
