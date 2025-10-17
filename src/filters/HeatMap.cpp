#include "../../include/filters/HeatMap.h"
#include <math.h>
HeatMap::HeatMap(Image& img) : Filter(img) {};

string HeatMap::getName() { return "HeatMap"; };
string HeatMap::getId() { return "26"; }
void HeatMap::getNeeds()
{
};
void HeatMap::apply()
{
	for (int i = 0; i < image.width; i++){
		for (int j = 0;j < image.height;j++)
		{
			float R = static_cast<float>(image(i, j, 0));
			float G = static_cast<float>(image(i, j, 1));
			float B = static_cast<float>(image(i, j, 2));
			float mean_ntensity = (R + G + B) / 3.0f;
		
			if (mean_ntensity < 64)
			{
				image(i , j , 0 ) = 0 ; 
				image(i, j, 1) = 0;
				image(i, j, 2) = 255;
			}
			else if (mean_ntensity < 128)
			{
				image(i, j, 0) = 0;
				image(i, j, 1) = 255;
				image(i, j, 2) =0;
			}
			else if (mean_ntensity < 192)
			{
				image(i, j, 0) = 255;
				image(i, j, 1) = 255;
				image(i, j, 2) = 0;
			}
			else
			{
				image(i, j, 0) = 255;
				image(i, j, 1) = 0;
				image(i, j, 2) = 0;
			}

		}
	}
};

