#include <complex>

#include "Image_Class.h"
#include <stdexcept>
#include "iostream"
using namespace std; // This load a lot of files into the project, use std:: better;


class Filter {
protected:
  std::string outputFolderPath = "../../output/";
public:
  Filter() {}
  virtual void apply() = 0;
};

class GreyFilter : public Filter {
  Image &image;
public:
  GreyFilter(Image &image) : image(image) {}
  void apply() override {
    try {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {

                unsigned int avg = 0;

                for (int k = 0; k < 3; k++) {
                    avg += image(i, j, k);
                }

                avg /= image.channels; // average
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
};

class BWFilter : public Filter {
    Image &image;
    public:
        BWFilter (Image &img) :image(img) {};
        void apply() override {
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j<image.height; j++) {
                    unsigned short avg = 0;
                    for (int k =0; k< image.channels; k++) {
                        avg += image(i, j, k);
                    }

                    avg /= image.channels;

                    for (int k =0; k< image.channels; k++) {
                        image(i, j, k) = (avg >= (100)? 255:0);
                    }
                }
            }
        };
};




/*
class BwFilter : public Filter {
  Image image;
public:
  BwFilter(Image image) : image(image) {}
  void apply(std::string outputFilename) override {
     try {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {

                unsigned int avg = 0;
                bool bw = false;

                for (int k = 0; k < 3; k++) {
                    avg += image(i, j, k);
                }

                avg /= image.channels; // average
                avg >= 128 ? bw = true : bw = false;
                for (int k = 0; k < image.channels; k++) {
                    image(i, j, k) = bw ? 255 : 0;
                }
            }
        }

        image.saveImage(outputFolderPath + outputFilename);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
  }
};

class InvertFilter : public Filter {
  Image image;
public:
  InvertFilter(Image image) : image(image) {}
  void apply(std::string outputFilename) override {
    try {
      for (int i = 0; i < image.width; i++) {
          for (int j = 0; j < image.height; j++) {
              for (int k = 0; k < 3; k++) {
                  image(i, j, k) = 255 - image(i, j, k);
              }
          }
      }
      image.saveImage(outputFolderPath + outputFilename);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
  }
};

class MergeFilter : public Filter {
  Image base;
  Image overlay;
public:
  MergeFilter(Image base, Image overlay) : base(base), overlay(overlay) {}
  void apply(std::string outputFilename) override {
    try {
      int minHeight = std::min(base.height, overlay.height);
      int minWidth  = std::min(base.width, overlay.width);

      for (int i = 0; i < minWidth; i++) {
          for (int j = 0; j < minHeight; j++) {
              for (int k = 0; k < 3; k++) {
                  base(i, j, k) = (base(i, j, k) + overlay(i, j, k)) / 2;
              }
          }
      }

      base.saveImage(outputFolderPath + outputFilename);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
  }
};
*/

void loadImage (Image &img) {
  cout << "Enter the image's name: "; std::string imgName; std::cin >> imgName;

  string imgPath = "assets/" + imgName;
  img.loadNewImage(imgPath);
}

void saveImage (Image &img) {
  cout << "Enter the name of the new image: "; string imgName; cin >> imgName;

  img.saveImage(("C:\\Users\\Mohammad\\CLionProjects\\cpp-img-processor\\output\\"+imgName+".jpg"));
}


int main() {
    string welcomeMsg = "\nWelcome to the ultimate image processor CPP app.";
    cout << welcomeMsg << "\n";
    cout << std::string(welcomeMsg.length()/5, ' ') << std::string(welcomeMsg.length()*3/5, '=') << std::string(welcomeMsg.length()/5, ' ') << "\n \n";

    Image img;
    bool exited = false;
    bool fileLoaded = false; // default false
    while (!exited) {
    std::cout << "\nSelect by typing the number of the operation:\n";

    std::cout << "1. Load an image to work on.\n";
    if (fileLoaded) {
      std::cout << "Filters\n";
      std::cout << "\t2. Grayscale Conversion Filter.\n";
      std::cout << "\t3. Black and White Filter.\n";
      std::cout << "\t4. Invert Filter.\n";
      std::cout << "\t-1. Save the Image.\n";
    }
    std::cout << "0. Exit.\n";
    std::cout << "-------------------------------\n";


    int res;
    std::cout << "Enter Your Response:\t";
    std::cin >> res;
    std::cout << '\n';

    if (res == 1) {
         loadImage(img);
        fileLoaded = true;
    } else if (res == 2 && fileLoaded) {
        GreyFilter grey(img);
        grey.apply();
    }
    else if (res == 3 && fileLoaded) {
        BWFilter bw(img);
        bw.apply();
    }

        else if (res == -1 && fileLoaded) {
        saveImage(img);
    }
    else {
        exited = true;
    }
  }


  return 0;
}

