#include "../../include/filters/Filter.h"
#include "../../include/filters/Resize.h"


    Resize::Resize(Image& img) :Filter(img) {};
    void Resize::getNeeds() {
        cout << "Please enter the new dimensions of the image. (100 100): ";
        cin >> dimensions[0] >> dimensions[1];
    }
    string Resize::getName() { return "Resizing"; };
    string Resize::getId() { return "11"; };

    void Resize::apply() {
        resizeImage(image, dimensions[0], dimensions[1]);
    }