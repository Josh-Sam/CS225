#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  PNG image, image2;
  image.readFromFile(inputFile);
  image2.readFromFile(inputFile);
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      image2.getPixel((image.width()-1) - x,(image.height()-1) - y) = pixel;
    }
  }
  image2.writeToFile(outputFile);

}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h = (double(x+y)/(png.width() + png.height())) * 360;
      pixel.l = 0.5;
    }
  }

  return png;
}
