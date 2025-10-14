#include "../../include/filters/Filter.h"
#include "../../include/filters/Frame.h"
#include "../../include/utils/Colors.h"
#include <unordered_map>




    Frame::Frame(Image& img) : Filter(img), R(0), G(0), B(0), Thickness(1), isDecorative(false) {}

    string Frame::getName() { return "Frame"; }
    string Frame::getId() { return "9"; }

    void Frame::getNeeds() {
        static unordered_map<string, RGB> colors = {
            {"red", {255, 0, 0}},
            {"green", {0, 255, 0}},
            {"blue", {0, 0, 255}},
            {"yellow", {255, 255, 0}},
            {"cyan", {0, 255, 255}},
            {"magenta", {255, 0, 255}},
            {"white", {255, 255, 255}},
            {"black", {0, 0, 0}},
            {"gray", {128, 128, 128}},
            {"orange", {255, 165, 0}},
            {"purple", {128, 0, 128}},
            {"pink", {255, 105, 180}},
            {"gold", {255, 215, 0}},
            {"brown", {165, 42, 42}}
        };

        cout << "Choose frame type:\n";
        cout << "1. Normal Frame\n";
        cout << "2. Decorative Frame\n";
        int choice;
        cin >> choice;

        if (choice == 2)
        {
            isDecorative = true;
            cout << CYAN << "Decorative frame selected!\n" << RESET;
            cout << "Enter frame color name with small letters\n";
            string colorName;
            cin >> colorName;

            if (colors.find(colorName) != colors.end())
            {
                RGB c = colors[colorName];
                R = c.R;
                G = c.G;
                B = c.B;
            }
            else
            {
                cout << RED << "Unknown color name.\n" << RESET;
                cout << YELLOW << "Enter color with R G B values: \n" << RESET;
                cin >> R >> G >> B;
            }
        }
        else
        {
            isDecorative = false;
            cout << "Enter frame color name with small letters\n";
            string colorName;
            cin >> colorName;

            if (colors.find(colorName) != colors.end()) {
                RGB c = colors[colorName];
                R = c.R;
                G = c.G;
                B = c.B;
            }
            else {
                cout << RED << "Unknown color name.\n" << RESET;
                cout << YELLOW << "Enter color with R G B values: \n" << RESET;
                cin >> R >> G >> B;
            }
        }

        cout << "Enter frame thickness: ";
        cin >> Thickness;
    }

    void Frame::apply()     {
        int width = image.width;
        int height = image.height;

        if (!isDecorative) {
            for (int i = 0; i < width; i++) {
                for (int t = 0; t < Thickness; t++) {
                    image(i, t, 0) = R;
                    image(i, t, 1) = G;
                    image(i, t, 2) = B;
                }
            }
            for (int i = 0; i < width; i++) {
                for (int t = 0; t < Thickness; t++) {
                    image(i, height - 1 - t, 0) = R;
                    image(i, height - 1 - t, 1) = G;
                    image(i, height - 1 - t, 2) = B;
                }
            }
            for (int i = 0; i < height; i++) {
                for (int t = 0; t < Thickness; t++) {
                    image(t, i, 0) = R;
                    image(t, i, 1) = G;
                    image(t, i, 2) = B;
                }
            }
            for (int i = 0; i < height; i++) {
                for (int t = 0; t < Thickness; t++) {
                    image(width - 1 - t, i, 0) = R;
                    image(width - 1 - t, i, 1) = G;
                    image(width - 1 - t, i, 2) = B;
                }
            }
        }

        else
        {
            RGB inner = { 255, 255, 255 };
            int outerThickness = Thickness;
            int innerThickness = Thickness / 2;
            for (int i = 0; i < width; i++) {
                for (int t = 0; t < outerThickness; t++) {
                    image(i, t, 0) = R;
                    image(i, t, 1) = G;
                    image(i, t, 2) = B;
                }
            }
            for (int i = 0; i < width; i++)
            {
                for (int t = 0; t < outerThickness; t++)
                {
                    image(i, height - 1 - t, 0) = R;
                    image(i, height - 1 - t, 1) = G;
                    image(i, height - 1 - t, 2) = B;
                }
            }
            for (int i = 0; i < height; i++)
            {
                for (int t = 0; t < outerThickness; t++) {
                    image(t, i, 0) = R;
                    image(t, i, 1) = G;
                    image(t, i, 2) = B;
                }
            }
            for (int i = 0; i < height; i++)
            {
                for (int t = 0; t < outerThickness; t++) {
                    image(width - 1 - t, i, 0) = R;
                    image(width - 1 - t, i, 1) = G;
                    image(width - 1 - t, i, 2) = B;
                }
            }
            for (int i = outerThickness; i < width - outerThickness; i++)
            {
                for (int t = 0; t < innerThickness; t++) {
                    image(i, outerThickness + t, 0) = inner.R;
                    image(i, outerThickness + t, 1) = inner.G;
                    image(i, outerThickness + t, 2) = inner.B;
                }
            }
            for (int i = outerThickness; i < width - outerThickness; i++)
            {
                for (int t = 0; t < innerThickness; t++) {
                    image(i, height - outerThickness - 1 - t, 0) = inner.R;
                    image(i, height - outerThickness - 1 - t, 1) = inner.G;
                    image(i, height - outerThickness - 1 - t, 2) = inner.B;
                }
            }
            for (int i = outerThickness; i < height - outerThickness; i++)
            {
                for (int t = 0; t < innerThickness; t++)
                {
                    image(outerThickness + t, i, 0) = inner.R;
                    image(outerThickness + t, i, 1) = inner.G;
                    image(outerThickness + t, i, 2) = inner.B;
                }
            }
            for (int i = outerThickness; i < height - outerThickness; i++)
            {
                for (int t = 0; t < innerThickness; t++)
                {
                    image(width - outerThickness - 1 - t, i, 0) = inner.R;
                    image(width - outerThickness - 1 - t, i, 1) = inner.G;
                    image(width - outerThickness - 1 - t, i, 2) = inner.B;
                }
            }
        }


    }