#include "Filter.h"

Filter::Filter(Image& img) : image(img) {}

double Filter::computeThreshold()
{
    vector<int> intensities;
    intensities.reserve(image.width * image.height);

    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            int r = image(x, y, 0);
            int g = image(x, y, 1);
            int b = image(x, y, 2);
            intensities.push_back((r + g + b) / 3);
        }
    }

    double sum = 0;
    for (int val : intensities)
        sum += val;

    double mean = sum / intensities.size();

    double variance = 0;
    for (int val : intensities)
        variance += pow(val - mean, 2);

    variance /= intensities.size();

    double standardDeviation = sqrt(variance);
    threshold = mean + 0.6 * standardDeviation;

    return threshold;
}

double Filter::getThreshold()
{
    return threshold;
}

bool Filter::isInBound(int x, int y)
{
    return !(x < 0 || x >= image.width || y < 0 || y >= image.height);
}

void Filter::resizeImage(Image& img, int newW, int newH)
{
    Image resizedImage(newW, newH);

    double xRatio = static_cast<double>(img.width) / newW;
    double yRatio = static_cast<double>(img.height) / newH;

    for (int x = 0; x < newW; x++) {
        for (int y = 0; y < newH; y++) {
            int nearestX = static_cast<int>(x * xRatio);
            int nearestY = static_cast<int>(y * yRatio);

            nearestX = min(nearestX, img.width - 1);
            nearestY = min(nearestY, img.height - 1);

            for (int k = 0; k < img.channels; k++) {
                resizedImage(x, y, k) = img(nearestX, nearestY, k);
            }
        }
    }

    img = resizedImage;
}
