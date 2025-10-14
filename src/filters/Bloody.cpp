#include "../../include/filters/Filter.h"
#include "../../include/filters/Bloody.h"



    Bloody::Bloody(Image& img) : Filter(img) {};
    void Bloody::getNeeds() {};
    string Bloody::getName() { return "Bloody"; };
    string Bloody::getId() { return "19"; };

    void Bloody::apply() {
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height; y++) {
                int redChannel = 0;
                for (int k = 0; k < image.channels; k++) {
                    redChannel += image(x, y, k);
                }
                redChannel /= image.channels;

                image(x, y, 0) = redChannel;
                image(x, y, 1) = 0;
                image(x, y, 2) = 0;
            }
        }
    }
