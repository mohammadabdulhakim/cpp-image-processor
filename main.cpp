#include "Image_Class.h"
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

string currentDir = "C:\\Users\\Mohammad\\CLionProjects\\cpp-img-processor\\imgs\\";

Image loadImage () {
  cout << "Enter the image's name: "; string imgName; cin >> imgName;

  string imgPath = currentDir + imgName;
  // try { //TODO: Handle Errors with the User Without Breaking the Program
    Image img(imgPath);
    return img;
  // }catch (invalid_argument error) {
  //   cout << "Invalid filename, There are no images with this name.\n";
  // }

}

int main() {
    string welcomeMsg = "\nWelcome to the ultimate image processor CPP app.";
    cout << welcomeMsg << "\n";
    cout << string(welcomeMsg.length()/5, ' ') << string(welcomeMsg.length()*3/5, '=') << string(welcomeMsg.length()/5, ' ') << "\n \n";

    bool exited = false;
    bool fileLoaded = false; // default false
    while (!exited) {


    cout << "Select by typing the number of the operation:\n";

    cout << "1. Load an image to work on.\n";
    if (fileLoaded) {
      cout << "Filters\n";
      cout << "\t2. Black and White Filter.\n";
      cout << "\t3. Grey Scale Filter.\n";
      cout << "\t4. Invert Filter.\n";
    }
    cout << "0. Exit.\n";
    cout << "-------------------------------\n";


    int res;
    cout << "Enter Your Response:\t";
    cin >> res;
    cout << '\n';


    if (res == 1) {
        Image img = loadImage();
        fileLoaded = true;
    } else {
        exited = true;
    }
  }


  return 0;
}

/*
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
*/