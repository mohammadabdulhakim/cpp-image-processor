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


class MergeFilter : public Filter {
  Image &base;
  Image &overlay;
public:
  MergeFilter(Image base, Image overlay) : base(base), overlay(overlay) {}
  void apply() override {
      int minHeight = min(base.height, overlay.height);
      int minWidth  = min(base.width, overlay.width);

      for (int i = 0; i < minWidth; i++) {
          for (int j = 0; j < minHeight; j++) {
              for (int k = 0; k < 3; k++) {
                  base(i, j, k) = (base(i, j, k) + overlay(i, j, k)) / 2;
              }
          }
      }
  }
};


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

    cout << "1. Load an image to work on.\n";
    if (fileLoaded) {
      cout << "Filters\n";
      cout << "\t2. Grayscale Conversion Filter.\n";
      cout << "\t3. Black and White Filter.\n";
      cout << "\t4. Invert Filter.\n";
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
    // -------------------------------------------------------------------
  }


  return 0;
}

