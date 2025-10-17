#include "../../include/filters/Filter.h"
#include "../../include/filters/OldPhoto.h"
#include <algorithm>
OldPhoto::OldPhoto(Image& img) :Filter(img) {};
string OldPhoto::getName() { return "OldPhoto"; };
string OldPhoto::getId() { return "24"; }
void OldPhoto::apply()
{
	for (int i = 0; i < image.width; i++)
	{
		for (int j = 0; j < image.height; j++)
		{

			int Nr = 0.4 * image(i, j, 0 ) + 0.75 * image(i, j, 1) + 0.2 * image(i, j, 2);
			Nr = min(255, Nr);
			int Ng = 0.35* image(i, j, 0)  + 0.7 * image(i, j, 1) + 0.15*image(i, j, 2);
			Ng = min(255, Ng);
			int Nb = 0.2 * image(i, j, 0) +  0.55*image(i, j, 1)  + 0.13* image(i, j, 2);
			Nb = min(255, Nb);
			image(i, j, 0) = Nr; 
			image(i, j, 1) = Ng;
			image(i, j, 2) = Nb;
		}
	}
}
void OldPhoto::getNeeds()
{
};

