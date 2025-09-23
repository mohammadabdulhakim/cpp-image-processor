#include "Filter_Class.h"
#include "Image_Class.h"

int main() {
  Image img("img.jpg");

  Filter filter(img);

  filter.invertFilter("output/invert_image.jpg");
  filter.greyFilter("output/grey_image.jpg");
  filter.bwFilter("output/bw_image.jpg");

  // MY new commit
  return 0;
}
