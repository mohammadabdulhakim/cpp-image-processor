#include "../../include/filters/gama.h"
#include <math.h>
gama::gama(Image& img) : Filter(img) {};

string gama::getName() { return "gama"; };
string gama::getId() { return "25"; }
void gama::getNeeds()
{
	cout << "Enter Value between [0 , 10] : ";cin >> Gama;
};
void gama::apply()
{
	for (int i = 0; i < image.width; i++)
	{
		for (int j = 0; j < image.height;j++)
		{
			float Val = pow(image(i, j, 0) / 255.0f, Gama);
			int Nr = min(int(255 * Val), 255);
			image(i, j, 0) = Nr;
			Val = pow(image(i, j, 1) / 255.0f, Gama);
			int Ng = min(int(255 * Val), 255);
			image(i, j, 1) = Ng;

			Val = pow(image(i, j, 2) / 255.0f, Gama);
			int Nb = min(int(255 * Val), 255);
			image(i, j, 2) = Nb;

		}
	}
};

