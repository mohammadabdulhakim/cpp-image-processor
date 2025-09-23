#include "Filter_Class.h"
#include "Image_Class.h"
#include "iostream"
using namespace std;

int main() {

  Image img("C:\\Users\\Mohammad\\CLionProjects\\cpp-img-processor\\img.jpg");

  Filter filter(img);

  cout << "\nInvert";
  filter.invertFilter("C:\\Users\\Mohammad\\CLionProjects\\cpp-img-processor\\output\\invert_image.jpg")? (cout << " - (passed)"):(cout << " - (failed)");
  cout << "\ngrey";
  filter.greyFilter("C:\\Users\\Mohammad\\CLionProjects\\cpp-img-processor\\output\\grey_image.jpg")? (cout << " - (passed)"):(cout << " - (failed)");
  cout << "\nbw";
  filter.bwFilter("C:\\Users\\Mohammad\\CLionProjects\\cpp-img-processor\\output\\bw_image.jpg")? (cout << " - (passed)"):(cout << " - (failed)");

  // MY new commit
  return 0;
}
