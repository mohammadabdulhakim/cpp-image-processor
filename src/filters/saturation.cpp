#include "../../include/filters/Filter.h"
#include "../../include/filters/saturation.h"
#include "../../include/filters/STRUCT.h"
#include <algorithm>
#include <cmath>

using namespace std;

saturation::saturation(Image& img) : Filter(img) {}

string saturation::getName() { return "saturation"; }
string saturation::getId() { return "23"; }

HSV saturation::rgbToHsv(const RGB& rgb) {
    float r = rgb.r / 255.0f;
    float g = rgb.g / 255.0f;
    float b = rgb.b / 255.0f;

    float maxVal = max({ r, g, b });
    float minVal = min({ r, g, b });
    float diff = maxVal - minVal;

    HSV hsv;
    hsv.v = maxVal;

    if (maxVal == 0)
        hsv.s = 0;
    else
        hsv.s = diff / maxVal;

    if (diff == 0)
        hsv.h = 0;
    else if (maxVal == r)
        hsv.h = 60 * fmod(((g - b) / diff), 6.0);
    else if (maxVal == g)
        hsv.h = 60 * (((b - r) / diff) + 2);
    else
        hsv.h = 60 * (((r - g) / diff) + 4);

    if (hsv.h < 0) hsv.h += 360;

    return hsv;
}

RGB saturation::hsvToRgb(const HSV& hsv) {
    double C = hsv.v * hsv.s;
    double X = C * (1 - fabs(fmod(hsv.h / 60.0, 2) - 1));
    double m = hsv.v - C;

    double rPrime, gPrime, bPrime;

    if (hsv.h >= 0 && hsv.h < 60)
        rPrime = C, gPrime = X, bPrime = 0;
    else if (hsv.h >= 60 && hsv.h < 120)
        rPrime = X, gPrime = C, bPrime = 0;
    else if (hsv.h >= 120 && hsv.h < 180)
        rPrime = 0, gPrime = C, bPrime = X;
    else if (hsv.h >= 180 && hsv.h < 240)
        rPrime = 0, gPrime = X, bPrime = C;
    else if (hsv.h >= 240 && hsv.h < 300)
        rPrime = X, gPrime = 0, bPrime = C;
    else
        rPrime = C, gPrime = 0, bPrime = X;

    RGB out;
    out.r = (rPrime + m) * 255;
    out.g = (gPrime + m) * 255;
    out.b = (bPrime + m) * 255;

    return out;
}

void saturation::apply() {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            RGB color = { image(i, j, 0), image(i, j, 1), image(i, j, 2) };
            HSV hsv = rgbToHsv(color);

            hsv.s *= (p / 100.0f);
            hsv.s = min(max(hsv.s, 0.0f), 1.0f);

            RGB newColor = hsvToRgb(hsv);

            image(i, j, 0) = static_cast<unsigned char>(newColor.r);
            image(i, j, 1) = static_cast<unsigned char>(newColor.g);
            image(i, j, 2) = static_cast<unsigned char>(newColor.b);
        }
    }
}

void saturation::getNeeds() {
    cout << "Enter saturation percentage (100 = normal, >100 = more color, <100 = less color): ";
    cin >> p;
}
