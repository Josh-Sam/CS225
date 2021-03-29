#include "Image.h"
using namespace cs225;

void Image::lighten(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l + 0.1 > 1) {
        pixel.l = 1;
      } else {
        pixel.l = pixel.l + 0.1;
      }
    }
  }
}

void Image::lighten(double amount){

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l + amount > 1) {
        pixel.l = 1;
      } else {
        pixel.l = pixel.l + amount;
      }
    }
  }
}

void Image::darken(){

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l - 0.1 < 0) {
        pixel.l = 0;
      } else {
        pixel.l = pixel.l - 0.1;
      }
    }
  }
}

void Image::darken(double amount){

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.l - amount < 0) {
        pixel.l = 0;
      } else {
        pixel.l = pixel.l - amount;
      }
    }
  }
}

void Image::saturate(){

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s + 0.1 > 1) {
        pixel.s = 1;
      } else {
        pixel.s = pixel.s + 0.1;
      }
    }
  }
}

void Image::saturate(double amount){

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s + amount > 1) {
        pixel.s = 1;
      } else {
        pixel.s = pixel.s + amount;
      }
    }
  }
}

void Image::desaturate(){

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s - 0.1 < 0) {
        pixel.s = 0;
      } else {
        pixel.s = pixel.s - 0.1;
      }
    }
  }
}

void Image::desaturate(double amount){

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.s - amount < 0) {
        pixel.s = 0;
      } else {
        pixel.s = pixel.s - amount;
      }
    }
  }
}

void Image::grayscale(){

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      int result = pixel.h + degrees;

      while (result < 0) {
        result += 360;
      }
      pixel.h = result%360;
    }
  }
}

void Image::illinify(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.h >= 113.5 && pixel.h <= 293.5) {
        pixel.h = 216;
      } else {
        pixel.h = 11;
      }
    }
  }
}

void Image::scale(double factor){
  if (factor > 1) {
    resize(width() * factor, height() * factor);
      for (int x = width() - 1; x >= 0; x--) {
        for (int y = height() - 1; y >= 0; y--) {
          HSLAPixel & p = getPixel((unsigned)x, (unsigned)y);
          HSLAPixel & p2 = getPixel((unsigned)x / factor, (unsigned)y / factor);
          p = p2;
        }
      }
  }
  if (factor < 1) {
    for (unsigned x = 0; x < width() * factor; x++) {
      for (unsigned y = 0; y < height() * factor; y++) {
        HSLAPixel & p = getPixel(x, y);
        HSLAPixel & p2 = getPixel(x / factor, y / factor);
        p = p2;
      }
    }
    resize(width() * factor, height() * factor);
  }
}

void Image::scale(unsigned w, unsigned h){
  double widthFactor = (double) w / (double) width();
  double heightFactor = (double) h / (double) height();
  double factor = std::min(widthFactor, heightFactor);
  scale(factor);
}
