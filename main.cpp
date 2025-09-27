#include "Image_Class.h"
#include <stdexcept>
#include "iostream"
//using namespace std; // This load a lot of files into the project, use std:: better;

class Filter {
protected:
  std::string outputFolderPath = "../../output/";
public:
  Filter() {}
  virtual void apply(std::string outputFilendame) = 0;
};

class GreyFilter : public Filter {
  Image image;
public:
  GreyFilter(Image image) : image(image) {}
  void apply(std::string outputFilename) override {
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

        image.saveImage(outputFolderPath + outputFilename);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
  }
};

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


int main() {

  Image img("assets/img.jpg");
  Image toy1("assets/toy1.jpg");
  Image toy2("assets/toy2.jpg");


  GreyFilter grey(img);
  grey.apply("img.grey.jpg");
  BwFilter bw(img);
  bw.apply("img.bw.jpg");
  InvertFilter invert(img);
  invert.apply("img.invert.jpg");
  MergeFilter merge(toy1, toy2);  
  merge.apply("toy1,toy2.jpg");


  return 0;
}
