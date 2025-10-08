/*
    This is an image processing app.
    When you start the program it asks you to load an image from the assets folder you write the name and the extention of the image (image.jpg).
    Then a punch of filters appears, you can apply any filter you want, and you can apply filters one by one.
    At any point you can save the image with any extension and in any folder even it does not exist.

    The App is colorful and eyes friendly. it's not only about the look.
    The app follows Object-Oriented Programming paradigm.
    It is scalable, and you can implement any filter smoothly without changing other classes.


    20242110 - Hamza Mohammad Zaki - Filters(Merge, GreyScale)
    20242295 - Mohammad Abdulhakim Ramadan - Filters(White and Black, Flip, Crop)
    20240588 - Mostafa Ahmed Ali - Filters(Invert, Rotate)
*/
#include <complex>
#include <map>
#include<stack>
#include <memory>
#include "Image_Class.h"
#include <stdexcept>
#include <vector>
#include<cmath>
#include<unordered_map>
#define M_PI 3.14159265359
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#include "iostream"
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

string getImagePath(string imgName) {
    return ("assets/" + imgName);
}

class Filter
{
protected:
    Image& image;
    // static string id;
    // string outputFolderPath = "../../output/";
public:
    Filter(Image& img) : image(img) {};
    virtual void apply() = 0;
    virtual void getNeeds() = 0;
    virtual string getName() = 0;
    static void resizeImage(Image &img, int newW, int newH) {
        Image resizedImage(newW, newH);

        double xRatio = static_cast<double>(img.width) / newW;
        double yRatio = static_cast<double>(img.height) / newH;

        for (int x = 0; x < newW; x++) {
            for (int y = 0; y<newH; y++) {
                int nearestX = static_cast<int>(x*xRatio);
                int nearestY = static_cast<int>(y*yRatio);

                nearestX = min(nearestX, img.width - 1);
                nearestY = min(nearestY, img.height - 1);

                for (int k=0; k<img.channels; k++) {
                    resizedImage(x,y,k) = img(nearestX, nearestY, k);
                }
            }
        }

        img = resizedImage;
    }
    // static string getId() {};
};
class SkewingFilter : public Filter
{
    int angle; 
public :
    SkewingFilter(Image& img) : Filter(img) {};
    string getName() { return "Horizontal Skew"; };
    static string getId() { return "18"; };
    void apply()
    {
        try 
        {
            double tan_angle = tan(angle * M_PI / 180 );
            double slope = -tan_angle ; 
            double new_width = image.width + abs(image.height * slope);
            int checker = 0;
            if (slope < 0)
            {
                checker = abs(image.height * slope);
            }

            Image Skewed_image(new_width, image.height); 
            for (int x = 0; x < image.width; x++)
            {
                for (int y = 0; y < image.height; y++)
                {
                    double X = x + (slope * y) + checker ; 
                    /*if (X < 0)  X += abs(image.height * slope); */
                    for (int k = 0; k < 3; k++)
                    {
                        if (X >= 0 && X < new_width)
                        {
                            Skewed_image(X, y, k) = image(x, y, k);
                        }
                    }
                }
            }
            image = Skewed_image; 
        }
        catch (const std::exception& e) {  
            std::cerr << "Error: " << e.what() << std::endl;  
            throw;  
        }
    }
    
    void getNeeds() override {
        cout << "Enter skew angle : "; cin >> angle;
    }
};

class TVFilter : public Filter
{
public : 
    TVFilter(Image& img) : Filter(img) {};
    string getName() { return "Old TV"; };
    static string getId() { return "15"; };
    void apply() override
    {
        try {
            for (int i = 0; i < image.height -1 ; i+=2)
            {
                for (int j = 0; j < image.width ; j++)
                {
                    for (int k = 0; k < 3;k++)
                    {
                        image(j, i, k) = 0.5 * image(j, i, k);
                    }
                }
            }
        }

        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }
    void getNeeds() override {};
};
class GreyFilter : public Filter
{
public:
    GreyFilter(Image& img) : Filter(img) {};
    string getName() { return "Grey Scale"; };
    static string getId() { return "1"; };
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
        catch (const exception& e)
        {
            cerr << "Error: " << e.what() << endl;
            throw;
        }
    }
    void getNeeds() override {};
};

class WBFilter : public Filter
{
public:
    WBFilter(Image& img) : Filter(img) {};
    string getName() { return "White and Black"; };
    static string getId() { return "2"; };
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
    void getNeeds() override {};
};

class MergeFilter : public Filter
{
    Image overlay;
    int mergeType = 1;

public:
    MergeFilter(Image& img) : Filter(img) {};
    string getName() { return "Merge"; };
    static string getId() { return "4"; };

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
        Image& ov = this->overlay;
        Image& base = image;
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
        catch (const std::exception& e)
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
    FlipFilter(Image& img) : Filter(img) {};
    string getName() { return "Flip"; };
    static string getId() { return "5"; };

    void getNeeds() override
    {
        cout << "Do you want to flip the image (v)ertically or (h)orizontally: ";
        cin >> dir;
    }
    void apply() override
    {
        if (dir == 'h')
        {
            for (int i = 0; i < image.height; i++)
            {
                for (int j = 0; j < image.width / 2; j++)
                {
                    int tempChannels[3] = { 0 };
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
                    int tempChannels[3] = { 0 };
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
    InvertFilter(Image& img) : Filter(img) {};
    void apply() override {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    image(i, j, k) = 255 - image(i, j, k);
                }
            }
        }
    }
    string getName() { return "Invert"; };
    static string getId() { return "3"; };

    void getNeeds() override {};

};

class RotateFilter : public Filter
{
    int angle;
public:
    RotateFilter(Image& img) : Filter(img) {};
    string getName() { return "Rotate"; };
    static string getId() { return "6"; };

    void apply() override
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

    void getNeeds() override {
        cout << "Enter rotation angle (90 / 180 / 270): ";
        cin >> angle;
    }
};

class BrightnessFilter : public Filter
{
    double value;
public:
    BrightnessFilter(Image& img) : Filter(img) {};
    string getName() { return "Brightness"; };
    static string getId() { return "7"; };

    void apply() override {
        cout << "here is: " << value << '\n';
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    int newValue = image(i, j, k) * value;
                    if (newValue > 255) newValue = 255;
                    if (newValue < 0) newValue = 0;
                    image(i, j, k) = newValue;
                }
            }
        }
    }

    void getNeeds() override {
        cout << "Enter the brightness\n- 1 normal\n- > 1 Brightup\n- < 1 Darkup\n ex: 1.5 will light the image up by 50%  \n==>  ";
        cin >> value;
        cout << "Value is: " << value << '\n';
    }
};

class CropFiter : public Filter {
    int corner[2]{ 0 };
    int dimensions[2]{ 100 };

public:
    CropFiter(Image& img) :Filter(img) {};
    void getNeeds() override {
        cout << "Please enter a point to start cropping from it. (0 0): ";
        cin >> corner[0] >> corner[1];
        cout << "Please enter the dimensions of your cropped image. (100 100): ";
        cin >> dimensions[0] >> dimensions[1];
    }
    string getName() { return "Crop"; };
    static string getId() { return "8"; };

    void apply() override {
        Image croppedImage(dimensions[0], dimensions[1]);

        for (int i = corner[0], I = 0; i < (corner[0] + dimensions[0]); i++, I++) {
            for (int j = corner[1], J = 0; j < (corner[1] + dimensions[1]); j++, J++) {
                for (int k = 0; k < image.channels; k++) {
                    croppedImage(I, J, k) = image(i, j, k);
                }
            }
        }


        image = croppedImage;
    }
};

class ResizeFiter : public Filter {
    int dimensions[2]{ 100 };

public:
    ResizeFiter(Image& img) :Filter(img) {};
    void getNeeds() override {
        cout << "Please enter the new dimensions of the image. (100 100): ";
        cin >> dimensions[0] >> dimensions[1];
    }
    string getName() { return "Resizing"; };
    static string getId() { return "11"; };

    void apply() override {
        resizeImage(image, dimensions[0], dimensions[1]);
    }
};

struct RGB {
    int R, G, B;
};

class FrameFilter : public Filter {
    int Thickness;
    int R, G, B;
    bool isDecorative;
public:
    FrameFilter(Image& img) : Filter(img), R(0), G(0), B(0), Thickness(1), isDecorative(false) {};

    string getName() { return "Frame"; }
    static string getId() { return "9"; }

    void getNeeds() override {
        cout << "Choose frame type:\n";
        cout << "1. Normal Frame\n";
        cout << "2. Decorative Frame\n";
        int choice;
        cin >> choice;
        if (choice == 2) 
        {
            isDecorative = true;
            cout << CYAN << "Decorative frame selected!\n" << RESET;
        }
        else 
        {
            isDecorative = false;
            cout << "Choose how to enter color:\n";
            cout << "1. By color name\n";
            cout << "2. By RGB values\n";
            int colorChoice; cin >> colorChoice;
            

            if (colorChoice == 1) {
                cout << "Enter frame color name (red, blue, gold...): with small letters\n";
                string colorName;
                cin >> colorName;

                static unordered_map<string, RGB> colors = 
                {
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

                if (colors.find(colorName) != colors.end()) {
                    RGB c = colors[colorName];
                    R = c.R;
                    G = c.G;
                    B = c.B;
                }
                else {
                    cout << RED << "Unknown color name.\n" << RESET;
                    cout << YELLOW << "Defaulting to black.\n" << RESET;
                    R = G = B = 0;
                }
            }
            else {
                cout << "Enter R value (0-255): ";
                cin >> R;
                cout << "Enter G value (0-255): ";
                cin >> G;
                cout << "Enter B value (0-255): ";
                cin >> B;
            }
        }

        cout << "Enter frame thickness: ";
        cin >> Thickness;
    }

    void apply() override 
    {
        int width = image.width;
        int height = image.height;

        if (isDecorative == false) 
        {
            for (int i = 0; i < width; i++) 
            {
                for (int t = 0; t < Thickness; t++) 
                {
                    image(i, t, 0) = R;
                    image(i, t, 1) = G;
                    image(i, t, 2) = B;
                }
            }
            for (int i = 0; i < width; i++) 
            {
                for (int t = 0; t < Thickness; t++) 
                {
                    image(i, height - 1 - t, 0) = R;
                    image(i, height - 1 - t, 1) = G;
                    image(i, height - 1 - t, 2) = B;
                }
            }
            for (int i = 0; i < height; i++) 
            {
                for (int t = 0; t < Thickness; t++) 
                {
                    image(t, i, 0) = R;
                    image(t, i, 1) = G;
                    image(t, i, 2) = B;
                }
            }
            for (int i = 0; i < height; i++) 
            {
                for (int t = 0; t < Thickness; t++) 
                {
                    image(width - 1 - t, i, 0) = R;
                    image(width - 1 - t, i, 1) = G;
                    image(width - 1 - t, i, 2) = B;
                }
            }
        }
        else 
        {
            // Decorative frame 
        }
    }
};


// ======================================================================================================
class Menu
{
    bool isActive = true;
    string res;
    unordered_map<string, shared_ptr<Filter>>& filters;

public:
    Menu(unordered_map<string, shared_ptr<Filter>>& filters) : filters(filters) {};

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
        std::cout << RESET << GREEN << "[L] Load Image\n";
        if (fileLoaded)
        {
            // cout << "Filters\n";
            // std::cout << "\n\n";
            std::cout << CYAN << "=====================\n";
            std::cout << RESET << BOLD << "    Choose Filters    \n";
            std::cout << RESET << CYAN << "======================\n" << RESET;

            auto it = filters.begin();
            while (it != filters.end()) {
                cout << "\t [" << it->first << "] " << it->second->getName() << " Filter.\n";
                ++it;
            }

            cout << "\t[s] Save the Image.\n";
            cout << "\t[u] Undo \t [r] Redo\n"  ;
        }
        // cout << "0. Exit.\n";
        std::cout << RESET << RED << "[0] Exit\n" << RESET;
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

    string getResponse()
    {
        return res;
    }
};

class CurrentImage
{
    bool isLoaded = false; // default false
    stack<Image> memory;

public:
    Image img;
    void currennt_img()
    {
        memory.push(img);
    }
    void load()
    {
        string imgName;
        // cout << "Enter the image's name: ";
        // cin >> imgName;
        std::cout << CYAN << "Please Enter image name you want to apply filter on: ";
        std::cout << RESET << GREEN << BOLD;
        std::cin >> imgName;
        std::cout << "\n\n" << RESET;

        img.loadNewImage(getImagePath(imgName));
        setIsLoaded(true);
        memory = stack<Image>();
        memory.push(img);
    };


    void save()
    {
        cout << YELLOW << "Enter the name of the new image : " << RESET;
        string imgName;
        cin >> imgName;

        if (!fs::exists("output")) fs::create_directory("output");
        img.saveImage(("output/"+imgName));
        cout << GREEN << "Your image has been saved successfully!";

        /*
        cout << CYAN << "Enter folder name to save image : " << RESET;
        string folderPath;
        cin >> folderPath;

        if (!fs::exists(folderPath))
        {
            try {
                fs::create_directories(folderPath);
                cout << GREEN << "Folder created successfully: " << RESET << folderPath << endl;
            }
            catch (const exception& e) {
                cerr << RED << "Error creating folder: " << e.what() << RESET << endl;
                return;
            }
        }
        string fullPath = folderPath + "/" + imgName;
        try {
            bool fileExists = fs::exists(fullPath);
            img.saveImage(fullPath);

            if (fileExists) {
                cout << GREEN << "Image saved successfully in existing file: "
                    << RESET << fullPath << endl;
            }
            else {
                cout << GREEN << "File created successfully: "
                    << RESET << fullPath << endl;
            }
        }
        catch (const exception& e) {
            cerr << RED << "Error saving file: " << e.what() << RESET << endl;
        }
        */
    }
    void undo()
    {
        if (memory.size() > 1)
        {
            memory.pop();
            img = memory.top();
        }
        else
        {
            cout << RED << "No more steps to undo." << RESET << endl;
        }
    }
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

    unordered_map<string, shared_ptr<Filter>> filters = {
        {GreyFilter::getId(),make_shared<GreyFilter>(currentImage.img)},
        {WBFilter::getId(),make_shared<WBFilter>(currentImage.img)},
        {InvertFilter::getId(),make_shared<InvertFilter>(currentImage.img)},
        {MergeFilter::getId(),make_shared<MergeFilter>(currentImage.img)},
        {FlipFilter::getId(),make_shared<FlipFilter>(currentImage.img)},
        {RotateFilter::getId(),make_shared<RotateFilter>(currentImage.img)},
        {BrightnessFilter::getId(),make_shared<BrightnessFilter>(currentImage.img)},
        {CropFiter::getId(),make_shared<CropFiter>(currentImage.img)},
        {FrameFilter::getId(),make_shared<FrameFilter>(currentImage.img)},
        {TVFilter::getId(),make_shared<TVFilter>(currentImage.img) } ,
        {SkewingFilter::getId(),make_shared<SkewingFilter>(currentImage.img)},
        {ResizeFiter::getId(),make_shared<ResizeFiter>(currentImage.img)},
    };

    Menu menu(filters);

    menu.welcomeMsg();
    while (menu.getIsActive())
    {
        menu.showMenuOptions(currentImage.getIsLoaded());
        menu.setResponse();

        if (menu.getResponse() == "l")
        {
            currentImage.load();
        }
        else if (menu.getResponse() == "s" && currentImage.getIsLoaded())
        {
            currentImage.save();
        }
        else if (menu.getResponse() == "u" && currentImage.getIsLoaded())
        {
            currentImage.undo();
        }
        else if (menu.getResponse() == "0")
        {
            menu.setIsActive(false);
        }
        else {
            filters[menu.getResponse()]->getNeeds();
            filters[menu.getResponse()]->apply();
            currentImage.currennt_img();
        }
    }

    return 0;
}