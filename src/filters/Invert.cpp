#include "../../include/filters/Filter.h"
#include "../../include/filters/Invert.h"



    Invert::Invert(Image& img) : Filter(img) {};
    void Invert::apply() {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    image(i, j, k) = 255 - image(i, j, k);
                }
            }
        }
    }
    string Invert::getName() { return "Invert"; };
    string Invert::getId() { return "3"; };

    void Invert::getNeeds() {};