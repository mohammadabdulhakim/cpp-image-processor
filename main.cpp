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

class FlipFilter : public Filter {
    Image &image;
    char dir = 'h';
public:
    FlipFilter(Image &img) : image(img) {}
    void getFlippingDirection () {
        cout << "Do you want to flip the image (v)ertically or (h)orizontally: "; cin >> dir;
    }

    void apply() override {
        if (dir == 'h') {
            for (int i = 0; i < image.height; i++) {
                for (int j = 0; j<image.width/2; j++) {
                    int tempChannels[3] = {0};
                    for (int k = 0; k<image.channels; k++) {
                        tempChannels[k] = image(j,i,k);
                    }

                    for (int k = 0; k<image.channels; k++) {
                        image(j,i,k) = image(image.width-j, i, k);
                    }

                    for (int k = 0; k<image.channels; k++) {
                        image(image.width-j, i, k) = tempChannels[k];
                    }
                }
            }
        }
        else {
            for (int j = 0; j < image.width; j++) {
                for (int i = 0; i<image.height/2; i++) {
                    int tempChannels[3] = {0};
                    for (int k = 0; k<image.channels; k++) {
                        tempChannels[k] = image(j,i,k);
                    }

                    // for (int k = 0; k<image.channels; k++) {
                    //     image(j,i,k) = image(j, image.height-i, k);
                    // }

                    // for (int k = 0; k<image.channels; k++) {
                    //     image(j, image.height-i, k) = tempChannels[k];
                    // }
                }
            }
        }
    }
};

class RotateFilter : public Filter {
    Image image;
    int angle;
public:
    RotateFilter(Image image, int angle) : image(image), angle(angle) {}
    void apply() override {
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

        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
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
      // cout << "\t4. Invert Filter.\n";
      // cout << "\t5. Filter.\n";
      cout << "\t6. Flipping Filter.\n";
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

    else if (res == 6 && fileLoaded) {
        FlipFilter flipFilter(img);
        flipFilter.getFlippingDirection();
        flipFilter.apply();
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

