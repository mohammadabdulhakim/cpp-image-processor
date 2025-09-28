#include "Image_Class.h"
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

class Filter {
private:
  Image img;

public:
  Filter() {}

  Filter(Image &mImg) { this->img = mImg; }

  bool greyFilter(std::string outputFilename) {

    try {
      for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

          unsigned int avg = 0;

          for (int k = 0; k < 3; k++) {
            avg += img(i, j, k);
          }

          avg /= img.channels; // average
          for (int k = 0; k < img.channels; k++) {
            img(i, j, k) = avg;
          }
        }
      }

      img.saveImage(outputFilename);
    } catch (std::invalid_argument e) {
      throw std::invalid_argument(e);
      return false;
    }
    return true;
  }

  bool bwFilter(std::string outputFilename) {

    try {
      for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

          unsigned int avg = 0;
          bool bw = false;

          for (int k = 0; k < 3; k++) {
            avg += img(i, j, k);
          }

          avg /= img.channels; // average
          avg >= 128 ? bw = true : bw = false;
          for (int k = 0; k < img.channels; k++) {
            img(i, j, k) = bw ? 255 : 0;
          }
        }
      }

      img.saveImage(outputFilename);
    } catch (std::invalid_argument e) {
      throw std::invalid_argument(e);
      return false;
    }
    return true;
  }

  bool invertFilter(std::string outputFilename) {

    try {
      for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
          for (int k = 0; k < 3; k++) {
            img(i, j, k) = 255 - img(i, j, k);
          }
        }
      }

      img.saveImage(outputFilename);
    } catch (std::invalid_argument e) {
      throw std::invalid_argument(e);
      return false;
    }
    return true;
  }
};


class Menu {

};

int main() {

  string currentDir = "C:\\Users\\Mohammad\\CLionProjects\\cpp-img-processor\\";
  Image img((currentDir+"imgs\\img.jpg"));


  string welcomeMsg = "Welcome to the ultimate image processor CPP app.";
  cout << welcomeMsg << "\n";
  cout << string(welcomeMsg.length()/5, ' ') << string(welcomeMsg.length()*3/5, '=') << string(welcomeMsg.length()/5, ' ');



  return 0;
}
