#include <cmath>
#include "../../include/filters/Filter.h"
#include "../../include/filters/GreyScale.h"
#include "../../include/filters/Blur.h"
#include "../../include/filters/EdgeDetection.h"



    EdgeDetection::EdgeDetection(Image& img) : Filter(img){}

    string EdgeDetection::getName() { return "Edge Detection"; }
    string EdgeDetection::getId() { return "10"; }
    map<string,vector<vector<int>>> EdgeDetection::sobelKernels () {
        return {
                {"Gx",{
                    {-1,0,1},
                    {-2,0,2},
                    {-1,0,1}
                }},
            {"Gy", {
                    {-1,-2,-1},
                    {0,0,0},
                    {1,2,1}
            }}
        };
    }
    void EdgeDetection::getNeeds() {};
    void EdgeDetection::apply() {
        GreyScale grey(image);
        grey.apply();
        Blur blur(image, 2);
        blur.apply();

        Image output(image.width, image.height);
        map<string,vector<vector<int>>> kernels = sobelKernels();
        computeThreshold();
        for (int x = 1; x < image.width-1; x++) {
            for (int y = 1; y < image.height-1; y++) {
                int sumX = 0;
                int sumY = 0;
                for (int i = -1; i <= 1; i++ ) {
                    for (int j = -1; j <= 1; j++ ) {
                        int intensity = image(x+i,y+j,0);
                        sumX += intensity * kernels["Gx"][i+1][j+1];
                        sumY += intensity * kernels["Gy"][i+1][j+1];
                    }
                }
                int magnitude = sqrt((sumX*sumX)+(sumY*sumY));
                if (magnitude > threshold) magnitude = 0;
                else magnitude = 255;
                output(x,y,0) = output(x,y,1) = output(x,y,2) = magnitude;
            }
        }

        image = output;
    }