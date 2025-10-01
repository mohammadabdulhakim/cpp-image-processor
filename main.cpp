#include <complex>
#include <map>
#include <memory>

#include "Image_Class.h"
#include <stdexcept>
#include <vector>

#define M_PI 3.14159265359
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

#include "iostream"
using namespace std; // This load a lot of files into the project, use  better;

string getImagePath(string imgName) {
    return ("assets/" + imgName);
}

class Filter
{
protected:
    Image &image;
    // static string id;
    //   string outputFolderPath = "../../output/";
public:
    Filter(Image &img) : image(img) {};
    virtual void apply() = 0;
    virtual void getNeeds() = 0;
    virtual string getName() = 0;
    static void resizeImage(Image &img, int newW, int newH)
    {
        Image out(newW, newH);

        double xRatio = static_cast<double>(img.width) / newW;
        double yRatio = static_cast<double>(img.height) / newH;

        for (int y = 0; y < newH; ++y)
        {
            for (int x = 0; x < newW; ++x)
            {
                int nearestX = static_cast<int>(x * xRatio);
                int nearestY = static_cast<int>(y * yRatio);

                for (int c = 0; c < 3; ++c)
                {
                    out(x, y, c) = img(nearestX, nearestY, c);
                }
            }
        }

        img = out;
    }
    // static string getId() {};
};

class GreyFilter : public Filter
{
public:
    GreyFilter(Image &img) : Filter(img) {};
    string getName() {return "Grey Scale";};
    static int getId() {return 2;};
    void apply() override
    {
        try
        {
            for (int i = 0; i < image.width; i++)
            {
                for (int j = 0; j < image.height; j++)
                {

                    unsigned int avg = 0;

                    for (int k = 0; k < 3; k++)
                    {
                        avg += image(i, j, k);
                    }

                    avg /= image.channels; // average
                    for (int k = 0; k < image.channels; k++)
                    {
                        image(i, j, k) = avg;
                    }
                }
            }
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
            throw;
        }
    }
    void getNeeds() override{};
};

class WBFilter : public Filter
{
public:
    WBFilter(Image &img) : Filter(img) {};
    string getName() {return "White and Black";};
    static int getId() {return 3;};
    void apply() override
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                unsigned short avg = 0;
                for (int k = 0; k < image.channels; k++)
                {
                    avg += image(i, j, k);
                }

                avg /= image.channels;

                for (int k = 0; k < image.channels; k++)
                {
                    image(i, j, k) = (avg >= (100) ? 255 : 0);
                }
            }
        }
    };
    void getNeeds() override{};
};

class MergeFilter : public Filter
{
    Image overlay;
    int mergeType = 1;

public:
    MergeFilter(Image &img) : Filter(img) {};
    string getName() {return "Merge";};
    static int getId() {return 5;};

    void getNeeds() override {
        cout << "Enter the image's name: ";
        string imgName;
        cin >> imgName;

        cout << "Enter Merge type (1: Stretch to fit, 2: Common): ";
        cin >> mergeType;
        
        overlay.loadNewImage(getImagePath(imgName));
    };
    void apply() override
    {
        Image &base = image;
        Image &overlay = overlay;
        try
        {
            int height;
            int width;

            if (base.width == overlay.width && base.height == overlay.height)
            {
                height = base.height;
                width = base.width;
                for (int i = 0; i < width; i++)
                {
                    for (int j = 0; j < height; j++)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            base(i, j, k) = (base(i, j, k) + overlay(i, j, k)) / 2;
                        }
                    }
                }
            }
            else
            {
                switch (mergeType)
                {
                case 1:
                { // max
                    /* Max */
                    width = std::max(base.width, overlay.width);
                    height = std::max(base.height, overlay.height);
                    resizeImage(base, width, height);
                    resizeImage(overlay, width, height);
                    for (int i = 0; i < width; i++)
                    {
                        for (int j = 0; j < height; j++)
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                base(i, j, k) = (base(i, j, k) + overlay(i, j, k)) / 2;
                            }
                        }
                    }
                    break;
                }
                case 2:
                { // both
                    Image img(std::max(base.width, overlay.width),
                              std::max(base.height, overlay.height));
                    for (int i = 0; i < base.width; i++)
                    {
                        for (int j = 0; j < base.height; j++)
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                img(i, j, k) = base(i, j, k);
                            }
                        }
                    }
                    for (int i = 0; i < overlay.width; i++)
                    {
                        for (int j = 0; j < overlay.height; j++)
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                if (i < base.width && j < base.height)
                                {
                                    img(i, j, k) = (img(i, j, k) + overlay(i, j, k)) / 2;
                                }
                                else
                                {
                                    img(i, j, k) = overlay(i, j, k);
                                }
                            }
                        }
                    }

                    base = img;
                }
                default:
                    break;
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }
};

class FlipFilter : public Filter
{
    char dir = 'h';
public:
    FlipFilter(Image &img) : Filter(img) {};
    string getName() {return "Flip";};
    static int getId() {return 6;};

    void getNeeds () override
    {
        cout << "Do you want to flip the image (v)ertically or (h)orizontally: ";
        cin >> dir;
    }
    void apply () override
    {
        if (dir == 'h')
        {
            for (int i = 0; i < image.height; i++)
            {
                for (int j = 0; j < image.width / 2; j++)
                {
                    int tempChannels[3] = {0};
                    for (int k = 0; k < image.channels; k++)
                    {
                        tempChannels[k] = image(j, i, k);
                    }

                    for (int k = 0; k < image.channels; k++)
                    {
                        image(j, i, k) = image(image.width - j - 1, i, k);
                    }

                    for (int k = 0; k < image.channels; k++)
                    {
                        image(image.width - j - 1, i, k) = tempChannels[k];
                    }
                }
            }
        }
        else
        {
            for (int j = 0; j < image.width; j++)
            {
                for (int i = 0; i < image.height / 2; i++)
                {
                    int tempChannels[3] = {0};
                    for (int k = 0; k < image.channels; k++)
                    {
                        tempChannels[k] = image(j, i, k);
                    }

                    for (int k = 0; k < image.channels; k++)
                    {
                        image(j, i, k) = image(j, image.height - i - 1, k);
                    }

                    for (int k = 0; k < image.channels; k++)
                    {
                        image(j, image.height - i - 1, k) = tempChannels[k];
                    }
                }
            }
        }
    }

};

class InvertFilter : public Filter {
public:
    InvertFilter(Image &img): Filter(img){};
    void apply() override {
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = 255 - image(i, j, k);
                    }
                }
            }
    }
    string getName() {return "Invert";};
    static int getId() {return 4;};

    void getNeeds() override {};

};

class RotateFilter : public Filter
{
    int angle = 90;
public:
    RotateFilter(Image &img) : Filter(img){};
    string getName() {return "Rotate";};
    static int getId() {return 7;};

    void apply() override
    {
        try
        {
            Image rotated_image;

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

            for (int x = 0; x < rotated_image.width; x++)
            {
                for (int y = 0; y < rotated_image.height; y++)
                {
                    int X = cx + (x - cx) * cos_Angle + (y - cy) * sin_Angle;
                    int Y = cy - (x - cx) * sin_Angle + (y - cy) * cos_Angle;

                    if (X >= 0 && X < image.width && Y >= 0 && Y < image.height)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            rotated_image(x, y, k) = image(X, Y, k);
                        }
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }
    void getNeeds() override {
        cout << "Enter rotation angle (90 / 180 / 270): ";
        cin >> angle;
    }
};

class CropFiter: public Filter {
    int corner[2] {0};
    int dimensions[2] {100};

public:
    CropFiter(Image &img) :Filter(img) {};
    void getNeeds () override {
        cout << "Please enter a point to start cropping from it. (0 0): ";
        cin >> corner[0] >> corner[1];
        cout << "Please enter the dimensions of your cropped image. (100 100): ";
        cin >> dimensions[0] >> dimensions[1];
    }
    string getName() {return "Crop";};
    static int getId() {return 9;};

    void apply() override {
        Image croppedImage(dimensions[0], dimensions[1]);

        for (int i = corner[0], I = 0; i < (corner[0]+dimensions[0]); i++, I++) {
            for (int j = corner[1], J = 0; j < (corner[1]+dimensions[1]); j++, J++) {
                for (int k = 0; k < image.channels; k++) {
                    croppedImage(I,J,k) = image(i,j,k);
                }
            }
        }


        image = croppedImage;
    }
};

class Menu
{
    bool isActive = true;
    int res;
    map<int,shared_ptr<Filter>> &filters;

public:
    Menu(map<int,shared_ptr<Filter>> &filters): filters(filters) {};

    void welcomeMsg()
    {
        // string welcomeMsg = "\nWelcome to the ultimate image processor CPP app.";
        // cout << welcomeMsg << "\n";
        // cout << string(welcomeMsg.length() / 5, ' ') << string(welcomeMsg.length() * 3 / 5, '=') << string(welcomeMsg.length() / 5, ' ') << "\n \n";
        std::cout << CYAN << "====================\n";
        std::cout << RESET << BOLD << "    Image Filters    \n";
        std::cout << RESET << CYAN << "=====================\n";
    }

    void showMenuOptions(bool fileLoaded)
    {
        // cout << "\nSelect by typing the number of the operation:\n";

        // cout << "1. Load an image to work on.\n";
        std::cout << RESET << GREEN << "1] Load Image\n";
        if (fileLoaded)
        {
            // cout << "Filters\n";
            std::cout << "\n\n";
            std::cout << CYAN << "=====================\n";
            std::cout << RESET << BOLD << "    Choose Filters    \n";
            std::cout << RESET << CYAN << "======================\n" << RESET;

            auto it = filters.begin();
            while (it != filters.end()) {
                cout << '\t' << it->first <<"] "<< it->second->getName() <<" Filter.\n";
                ++it;
            }

            cout << "\t-1] Save the Image.\n";
        }
        // cout << "0. Exit.\n";
        std::cout << RESET << CYAN << "0] Exit\n" << RESET;
        cout << "-------------------------------\n";
    }

    bool getIsActive()
    {
        return isActive;
    }
    void setIsActive(bool newIsActive)
    {
        isActive = newIsActive;
    }

    void setResponse()
    {
        // cout << "Enter Your Response:\t";
        std::cout << BOLD << GREEN << "# " << RESET;
        cin >> res;
        cout << '\n';
    }

    int getResponse()
    {
        return res;
    }
};

class CurrentImage
{
    bool isLoaded = false; // default false

public:
    Image img;
    void load()
    {
        string imgName;
        // cout << "Enter the image's name: ";
        // cin >> imgName;
        std::cout << CYAN << "Please Enter image name you want to apply filter on: ";
        std::cout << RESET << GREEN << BOLD;
        std::cin >> imgName;
        std::cout << RESET;

        img.loadNewImage(getImagePath(imgName));
        setIsLoaded(true);
    };


    void save()
    {
        cout << "Enter the name of the new image: ";
        string imgName;
        cin >> imgName;

        img.saveImage(("C:\\Users\\Mohammad\\CLionProjects\\cpp-img-processor\\output\\" + imgName + ".jpg"));
    };

    bool getIsLoaded()
    {
        return isLoaded;
    }

    void setIsLoaded(bool newIsLoaded)
    {
        isLoaded = newIsLoaded;
    }
};

int main()
{
    CurrentImage currentImage;

    map<int,shared_ptr<Filter>> filters = {
        {GreyFilter::getId(),make_shared<GreyFilter>(currentImage.img)},
        {WBFilter::getId(),make_shared<WBFilter>(currentImage.img)},
        {InvertFilter::getId(),make_shared<InvertFilter>(currentImage.img)},
        {MergeFilter::getId(),make_shared<MergeFilter>(currentImage.img)},
        {FlipFilter::getId(),make_shared<FlipFilter>(currentImage.img)},
        {RotateFilter::getId(),make_shared<RotateFilter>(currentImage.img)},
        {CropFiter::getId(),make_shared<CropFiter>(currentImage.img)},
    };

    Menu menu(filters);

    menu.welcomeMsg();
    while (menu.getIsActive())
    {
        menu.showMenuOptions(currentImage.getIsLoaded());
        menu.setResponse();

        if (menu.getResponse() == 1)
        {
            currentImage.load();
        }
        else if (menu.getResponse() == -1 && currentImage.getIsLoaded())
        {
            currentImage.save();
        }
        else if (menu.getResponse() == 0)
        {
            menu.setIsActive(false);
        }
        else {
            filters[menu.getResponse()]->getNeeds();
            filters[menu.getResponse()]->apply();
        }
    }

    return 0;
}