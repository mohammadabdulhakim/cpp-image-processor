
#include "../../include/filters/Filter.h"
#include "../../include/filters/Crop.h"



    Crop::Crop(Image& img) :Filter(img) {};
    void Crop::getNeeds() {
        cout << "Please enter a point to start cropping from it. (0 0): ";
        cin >> corner[0] >> corner[1];
        cout << "Please enter the dimensions of your cropped image. (100 100): ";
        cin >> dimensions[0] >> dimensions[1];
    }
    string Crop::getName() { return "Crop"; };
    string Crop::getId() { return "8"; };

    void Crop::apply() {
        Image croppedImage(dimensions[0], dimensions[1]);

        for (int i = corner[0], I = 0; i < (corner[0] + dimensions[0]); i++, I++) {
            for (int j = corner[1], J = 0; j < (corner[1] + dimensions[1]); j++, J++) {
                for (int k = 0; k < image.channels; k++) {
                    croppedImage(I, J, k) = image(i, j, k);
                }
            }
        }


        image = croppedImage;
    }
