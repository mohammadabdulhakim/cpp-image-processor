#include <string>

#include "../../include/filters/Filter.h"
#include "../../include/filters/Blur.h"
using namespace std;


    Blur::Blur(Image& img, int r) : Filter(img), radius(r) {};
    string Blur::getName() { return "Blur"; };
    string Blur::getId() { return "12"; };

    void Blur::Prefix_sum(Image& image, vector<vector<ll>>& prefixR, vector<vector<ll>>& prefixG, vector<vector<ll>>& prefixB)
    {
        for (int i = 1; i <= image.width; i++)
        {
            for (int j = 1; j <= image.height; j++)
            {
                ll r = image(i - 1, j - 1, 0);
                ll g = image(i - 1, j - 1, 1);
                ll b = image(i - 1, j - 1, 2);
                prefixR[i][j] = r + prefixR[i - 1][j] + prefixR[i][j - 1] - prefixR[i - 1][j - 1];
                prefixG[i][j] = g + prefixG[i - 1][j] + prefixG[i][j - 1] - prefixG[i - 1][j - 1];
                prefixB[i][j] = b + prefixB[i - 1][j] + prefixB[i][j - 1] - prefixB[i - 1][j - 1];
            }
        }
    }
    void Blur::apply()
    {
        try
        {
            Image Blured_image(image.width, image.height);
            vector<vector<ll>> PrefixR(image.width + 1, vector<ll>(image.height + 1, 0));
            vector<vector<ll>> PrefixG(image.width + 1, vector<ll>(image.height + 1, 0));
            vector<vector<ll>> PrefixB(image.width + 1, vector<ll>(image.height + 1, 0));
            Prefix_sum(image, PrefixR, PrefixG, PrefixB);
            for (int i = 0; i < image.width; i++)
            {
                for (int j = 0; j < image.height; j++)
                {
                    int x1, x2, y1, y2;

                    x1 = max(0, i - radius);
                    x2 = min(image.width - 1, i + radius);
                    y1 = max(0, j - radius);
                    y2 = min(image.height - 1, j + radius);

                    x1++, x2++, y1++, y2++;


                    ll SUM_R, SUM_G, SUM_B;
                    SUM_R = PrefixR[x2][y2] + PrefixR[x1 - 1][y1 - 1] - PrefixR[x2][y1 - 1] - PrefixR[x1 - 1][y2];
                    SUM_G = PrefixG[x2][y2] + PrefixG[x1 - 1][y1 - 1] - PrefixG[x2][y1 - 1] - PrefixG[x1 - 1][y2];
                    SUM_B = PrefixB[x2][y2] + PrefixB[x1 - 1][y1 - 1] - PrefixB[x2][y1 - 1] - PrefixB[x1 - 1][y2];


                    ll A = (2 * radius + 1) * (2 * radius + 1);


                    Blured_image(i, j, 0) = static_cast<unsigned char>(SUM_R / A);
                    Blured_image(i, j, 1) = static_cast<unsigned char>(SUM_G / A);
                    Blured_image(i, j, 2) = static_cast<unsigned char>(SUM_B / A);
                }
            }
            image = Blured_image;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    void Blur::getNeeds()
    {
        cout << "Enter strenght of blur : "; cin >> radius;
    }