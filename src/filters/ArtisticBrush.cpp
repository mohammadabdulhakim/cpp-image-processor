#include <vector>

#include "../../include/filters/OilPainting.h"
#include "../../include/filters/ArtisticBrush.h"



    ArtisticBrush::ArtisticBrush(Image& img) : OilPainting(img) {};
    void ArtisticBrush::getNeeds() {
        cout << "How wide should the brush strokes be? (3-7) (2 is recommended): ";
        cin >> radius;
        OilPainting::getNeeds();
    }
    string ArtisticBrush::getName() { return "Painting"; };
    string ArtisticBrush::getId() { return "22"; };

    void ArtisticBrush::apply() {
        Image output(image.width, image.height);

        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height; y++) {
                vector<int> intensityCount(intensityLevels, 0);
                vector<int> avgR(intensityLevels, 0);
                vector<int> avgG(intensityLevels, 0);
                vector<int> avgB(intensityLevels, 0);

                int count = 0;
                for (int ny = y - radius; ny <= (y + radius); ny++) {
                    for (int nx = x - radius; nx <= (x + radius); nx++) {
                        if (isInBound(nx, ny)) {
                            count++;
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
                for (int i = 0; i < intensityLevels; i++) {
                    if (maxCount < intensityCount[i]) {
                        maxBin = i;
                        maxCount = intensityCount[i];
                    }
                }

                if (maxCount) { // I mean maxCount > 0; but logically if maxCount was not zero then it is a true value;
                    output(x, y, 0) = avgR[maxBin] / maxCount;
                    output(x, y, 1) = avgG[maxBin] / maxCount;
                    output(x, y, 2) = avgB[maxBin] / maxCount;
                }
            }
        }
        image = output;
    }
