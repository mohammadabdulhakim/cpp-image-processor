#include "Image_Class.h"
#include <stdexcept>
#include "iostream"
#include <vector>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#include <unordered_map>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <filesystem>
namespace fs = std::filesystem;
class Filter {
protected:
    std::string outputFolderPath = "../../output/";
public:
    Filter() {}

    virtual void apply(std::vector<std::shared_ptr<Image>> images, std::unordered_map<std::string, int>& opt) = 0;
    virtual std::string getName() const = 0;
    virtual int getNumberOfImages() const = 0;
    virtual std::vector<std::string> getRequirements() const = 0;

    virtual ~Filter() {}
};

class GreyFilter : public Filter {
public:
    void apply(std::vector<std::shared_ptr<Image>> images, std::unordered_map<std::string, int>& opt) override {
        Image& image = *images[0];
        try {
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    unsigned int avg = 0;
                    for (int k = 0; k < 3; k++) {
                        avg += image(i, j, k);
                    }
                    avg /= image.channels;
                    for (int k = 0; k < image.channels; k++) {
                        image(i, j, k) = avg;
                    }
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }

    std::string getName() const override {
        return "Greyscale";
    }

    int getNumberOfImages() const override {
        return 1;
    }

    std::vector<std::string> getRequirements() const override {
        return {};
    }
};

class BwFilter : public Filter {
public:
    void apply(std::vector<std::shared_ptr<Image>> images, std::unordered_map<std::string, int>& opt) override {

        Image& image = *images[0];
        try {
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {

                    unsigned int avg = 0;
                    bool bw = false;

                    for (int k = 0; k < 3; k++) {
                        avg += image(i, j, k);
                    }

                    avg /= image.channels;
                    avg >= 128 ? bw = true : bw = false;
                    for (int k = 0; k < image.channels; k++) {
                        image(i, j, k) = bw ? 255 : 0;
                    }
                }
            }

        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }
    std::string getName() const override {
        return "Black and white";
    }

    int getNumberOfImages() const override {
        return 1;
    }

    std::vector<std::string> getRequirements() const override {
        return {};
    }

};

class InvertFilter : public Filter {
public:
    void apply(std::vector<std::shared_ptr<Image>> images, std::unordered_map<std::string, int>& opt) override {
        Image& image = *images[0];
        try {
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = 255 - image(i, j, k);
                    }
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }
    std::string getName() const override {
        return "Invert";
    }

    int getNumberOfImages() const override {
        return 1;
    }

    std::vector<std::string> getRequirements() const override {
        return {};
    }

};

class MergeFilter : public Filter {

public:
    void apply(std::vector<std::shared_ptr<Image>> images, std::unordered_map<std::string, int>& opt) override {
        Image& base = *images[0];
        Image& overlay = *images[1];
        try {
            int minHeight = std::min(base.height, overlay.height);
            int minWidth = std::min(base.width, overlay.width);

            for (int i = 0; i < minWidth; i++) {
                for (int j = 0; j < minHeight; j++) {
                    for (int k = 0; k < 3; k++) {
                        base(i, j, k) = (base(i, j, k) + overlay(i, j, k)) / 2;
                    }
                }
            }

        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }

    std::string getName() const override {
        return "Merge Images";
    }

    int getNumberOfImages() const override {
        return 2;
    }

    std::vector<std::string> getRequirements() const override {
        return {};
    }
};

class RotateFilter : public Filter {
public:

    void apply(std::vector<std::shared_ptr<Image>> images, std::unordered_map<std::string, int>& opt) override {
        Image& image = *images[0];
        int angle = opt["angle"];
        try {
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

            int ncx = rotated_image.width / 2;
            int ncy = rotated_image.height / 2;

            for (int x = 0; x < rotated_image.width; x++)
            {
                for (int y = 0; y < rotated_image.height; y++)
                {
                    int X = cx + (x - ncx) * cos_Angle - (y - ncy) * sin_Angle;
                    int Y = cy +(x - ncx) * sin_Angle + (y - ncy) * cos_Angle;

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
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }

    std::string getName() const override {
        return "Rotate";
    }

    int getNumberOfImages() const override {
        return 1;
    }

    std::vector<std::string> getRequirements() const override {
        return { "angle" };
    }
};


void loadImage(std::string& path, int imageNumber, std::vector<std::shared_ptr<Image>>& images) {
    path = "assets/" + path;
    Image img(path);
    images[imageNumber - 1] = std::make_shared<Image>(img);

}

int main() {
    std::vector<std::shared_ptr<Filter>> filters;
    filters.push_back(std::make_shared<GreyFilter>());
    filters.push_back(std::make_shared<BwFilter>());
    filters.push_back(std::make_shared<InvertFilter>());
    filters.push_back(std::make_shared<MergeFilter>());
    filters.push_back(std::make_shared<RotateFilter>());
    std::vector<std::shared_ptr<Image>> images(10);




    std::unordered_map<std::string, int> opt;

    //options default values
    opt["angle"] = 180;


    bool exit = false;

    std::cout << CYAN << "====================\n";
    std::cout << RESET << BOLD << "    Image Filters    \n";
    std::cout << RESET << CYAN << "=====================\n";

    std::cout << RESET << GREEN << "1] Load Image\n";
    std::cout << RESET << CYAN << "2] Exit\n" << RESET;
    int loadExitChoice;
    std::cin >> loadExitChoice;

    if (loadExitChoice != 1) {
        exit = true;
    }
    else {
        std::string imageName;
        std::cout << CYAN << "Please Enter image name you want to apply filter on: ";
        std::cout << RESET << GREEN << BOLD;
        std::cin >> imageName;
        std::cout << RESET;
        Image img("assets/" + imageName);
        images[0] = std::make_shared<Image>(img);
    }




    while (!exit) {
        std::cout << "\n\n";

        std::cout << CYAN << "=====================\n";
        std::cout << RESET << BOLD << "    Choose Filters    \n";
        std::cout << RESET << CYAN << "======================\n" << RESET;

        for (int i = 0; i < 5; i++) {
            std::cout << i + 1 << "] " << filters[i]->getName() << "\n";
        }
        std::cout << "Exit (any key)" << "\n";

        std::cout << BOLD << GREEN << "# " << RESET;
        int choice;
        if (!(std::cin >> choice)) {
            exit = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

        if (filters[choice - 1]->getNumberOfImages() > 1) {
            int temp = 1;
            int x = filters[choice - 1]->getNumberOfImages();
            std::string path;
            std::cout << CYAN << "This filter require " << x << " images:\n" << RESET;
            while (temp < x) {
                std::cout << CYAN << "Enter Image[ " << temp + 1 << " ] name with extention: ";
                std::cout << RESET << GREEN << BOLD;
                std::cin >> path;
                std::cout << RESET;
                loadImage(path, x, images);

                std::cout << '\n';
                temp++;
            }
        }

        std::vector<std::string> requirements = filters[choice - 1]->getRequirements();
        for (int i = 0; i < requirements.size(); i++) {
            std::cout << CYAN << "#Enter " << requirements[i] << ": ";
            std::cout << RESET << GREEN << BOLD;
            std::cin >> opt[requirements[i]];
            std::cout << RESET;
            std::cout << '\n';
        }

        filters[choice - 1]->apply(images, opt);


    }

    std::string outputFileName, folderName;
    bool imageSaved = false;

    std::cout << CYAN << "# Enter folder name to save images: " << GREEN << BOLD;
    std::cin >> folderName;
    std::cout << RESET;

    if (!fs::exists(folderName)) {
        fs::create_directory(folderName);
        std::cout << YELLOW << "Folder created: " << folderName << RESET << std::endl;
    }

    while (!imageSaved) {
        std::cout << CYAN << "# Enter output file name with extension : "
            << GREEN << BOLD;
        std::cin >> outputFileName;
        std::cout << RESET;

        try {
            images[0]->saveImage(folderName + "/" + outputFileName);
            imageSaved = true;
            std::cout << GREEN << "Image saved at: " << folderName + "/" + outputFileName << RESET << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cout << RED << BOLD << "Invalid file name\n";
        }
    }


}

/*
    int main() {
    string welcomeMsg = "\nWelcome to the ultimate image processor CPP app.";
    cout << welcomeMsg << "\n";
    cout << std::string(welcomeMsg.length() / 5, ' ') << std::string(welcomeMsg.length() * 3 / 5, '=') << std::string(welcomeMsg.length() / 5, ' ') << "\n \n";

    Image img;
    bool exited = false;
    bool fileLoaded = false; // default false
    while (!exited) {
        std::cout << "\nSelect by typing the number of the operation:\n";

        cout << "1. Load an image to work on.\n";
        if (fileLoaded) {
            cout << "Filters\n";
            cout << "\t2. Grayscale Conversion Filter.\n";
            cout << "\t3. Black and White Filter.\n";
            cout << "\t4. Invert Filter.\n";
             cout << "\t5.rotate Filter.\n";
            cout << "\t6. Flipping Filter.\n";
            cout << "\t9. Crop Filter.\n";
            cout << "\t-1. Save the Image.\n";
        }
        cout << "0. Exit.\n";
        cout << "-------------------------------\n";


        int res;
        cout << "Enter Your Response:\t";
        cin >> res;
        cout << '\n';

        // Add Filters Applications Here ----------------------------------------------
        if (res == 1) {
            loadImage(img);
            fileLoaded = true;
        }
        else if (res == 2 && fileLoaded) {
            GreyFilter grey(img);
            grey.apply();
        }
        else if (res == 3 && fileLoaded) {
            BWFilter bw(img);
            bw.apply();
        }
        else if (res == 4 && fileLoaded) {
            InvertFilter Inverted_image(img);
            Inverted_image.apply();
        }
        else if (res == 5 && fileLoaded) {
            int angle;
            cout << "Enter rotation angle (90 / 180 / 270): ";
            cin >> angle;
            RotateFilter rotaded_image(img , angle);
            rotaded_image.apply();
        }
        else if (res == 6 && fileLoaded) {
            FlipFilter flipFilter(img);
            flipFilter.getFlippingDirection();
            flipFilter.apply();
        }

        else if (res == 9 && fileLoaded) {
            Crop crop(img);
            crop.getCorner();
            crop.getDimentions();
            crop.apply();
        }
        else if (res == -1 && fileLoaded) {
            saveImage(img);
        }
        else {
            exited = true;
        }
        // -------------------------------------------------------------------
    }


    return 0;
}
*/
