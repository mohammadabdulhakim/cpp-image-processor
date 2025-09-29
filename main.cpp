#include "Image_Class.h"
#include <stdexcept>
#include "iostream"
#include <corecrt_math_defines.h>


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
  GreyFilter(Image image) {
    this->image = image;
  }
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
class RotateFilter : public Filter {
  Image image;
  int angle;
  int w, h;
public:
  RotateFilter(Image image, int angle) : image(image), angle(angle) {}
  void apply(std::string outputFilename) override {
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
    rotated_image.saveImage(outputFolderPath + outputFilename);
  }
};

Image loadImage () {
  std::cout << "Enter the image's name: "; std::string imgName; std::cin >> imgName;

  std::string imgPath = "assets/" + imgName;
  Image img(imgPath);
  return img;

}

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

  RotateFilter rotate_90(toy1, 90);
  rotate_90.apply("rotated_90.jpg");

  
  RotateFilter rotate_180(toy1, 180);
  rotate_180.apply("rotated_180.jpg");


  std::string welcomeMsg = "\nWelcome to the ultimate image processor CPP app.";
  std::cout << welcomeMsg << "\n";
  std::cout << std::string(welcomeMsg.length()/5, ' ') << std::string(welcomeMsg.length()*3/5, '=') << std::string(welcomeMsg.length()/5, ' ') << "\n \n";

  bool exited = false;
  bool fileLoaded = false; // default false


  while (!exited) {
  std::cout << "Select by typing the number of the operation:\n";

  std::cout << "1. Load an image to work on.\n";
  if (fileLoaded) {
    std::cout << "Filters\n";
    std::cout << "\t2. Black and White Filter.\n";
    std::cout << "\t3. Grey Scale Filter.\n";
    std::cout << "\t4. Invert Filter.\n";
  }
  std::cout << "0. Exit.\n";
  std::cout << "-------------------------------\n";


  int res;
  std::cout << "Enter Your Response:\t";
  std::cin >> res;
  std::cout << '\n';


  if (res == 1) {
      Image img = loadImage();
      fileLoaded = true;
  } else {
      exited = true;
  }
}


  return 0;
}