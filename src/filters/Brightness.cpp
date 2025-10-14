#include "../../include/filters/Filter.h"
#include "../../include/filters/Brightness.h"




    Brightness::Brightness(Image& img) : Filter(img) {};
    string Brightness::getName() { return "Brightness"; };
    string Brightness::getId() { return "7"; };

    void Brightness::apply() {
        cout << "here is: " << value << '\n';
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    int newValue = image(i, j, k) * value;
                    if (newValue > 255) newValue = 255;
                    if (newValue < 0) newValue = 0;
                    image(i, j, k) = newValue;
                }
            }
        }
    }

    void Brightness::getNeeds() {
        cout << "Enter the brightness\n- 1 normal\n- > 1 Brightup\n- < 1 Darkup\n ex: 1.5 will light the image up by 50%  \n==>  ";
        cin >> value;
        cout << "Value is: " << value << '\n';
    }
