#include "../../include/filters/Filter.h"
#include "../../include/filters/Rotate.h"
#include<cmath>



    Rotate::Rotate(Image& img) : Filter(img) {};
    string Rotate::getName() { return "Rotate"; };
    string Rotate::getId() { return "6"; };

    void Rotate::apply()
    {
        try
        {
            Image rotated_image;
            /*angle = 360 - angle; */
            switch (angle)
            {
                case 90:
                case 270:
                    rotated_image = Image(image.height, image.width);
                break;

                case 180:
                    rotated_image = Image(image.width, image.height);
                break;
            }

            double radian = angle * M_PI / 180.0;
            double cos_Angle = cos(radian);
            double sin_Angle = sin(radian);

            int cx = image.width / 2;
            int cy = image.height / 2;

            int ncx = rotated_image.width / 2;
            int ncy = rotated_image.height / 2;

            for (int x = 0; x < rotated_image.width; x++)
            {
                for (int y = 0; y < rotated_image.height; y++)
                {
                    int X = cx + (x - ncx) * cos_Angle + (y - ncy) * sin_Angle;
                    int Y = cy - (x - ncx) * sin_Angle + (y - ncy) * cos_Angle;

                    if (X >= 0 && X < image.width && Y >= 0 && Y < image.height)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            rotated_image(x, y, k) = image(X, Y, k);
                        }
                    }
                }
            }

            image = rotated_image;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }

    void Rotate::getNeeds() {
        cout << "Enter rotation angle (90 / 180 / 270): ";
        cin >> angle;
    }