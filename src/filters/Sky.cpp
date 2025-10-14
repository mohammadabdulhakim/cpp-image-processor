#include "../../include/filters/Filter.h"
#include "../../include/filters/Sky.h"



    Sky::Sky(Image& img) : Filter(img) {};
    void Sky::getNeeds() {};
    string Sky::getName() { return "Sky"; };
    string Sky::getId() { return "21"; };

    void Sky::apply() {
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height; y++) {
                int blueChannel = 0;
                for (int k = 0; k < image.channels; k++) {
                    blueChannel += image(x, y, k);
                }
                blueChannel /= image.channels;

                image(x, y, 0) = 0;
                image(x, y, 1) = blueChannel / 2;
                image(x, y, 2) = blueChannel;
            }
        }
    }
