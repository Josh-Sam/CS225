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
      if (pixel.h + degrees > 360.0) {
        pixel.h = (pixel.h + degrees) - 360.0;
      } else {
        pixel.h = pixel.h + degrees;
      }
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
void Image::scale(unsigned w, unsigned h){
  PNG* scaled = new PNG(w, h);

  for (unsigned int x = 0; x < w; x++){
    for (unsigned int y = 0; y < h; y++){
      HSLAPixel & pixel = scaled->getPixel(x, y);
      unsigned int newX = (unsigned int) (width() * x / w);
      unsigned int newY = (unsigned int) (height() * y / h);
      pixel = getPixel(newX, newY);
    }
  }

  resize(w, h);
  for (unsigned int x = 0; x < w; x++){
    for (unsigned int y = 0; y < h; y++){
      HSLAPixel & pixel2 = scaled->getPixel(x, y);
      HSLAPixel & pixel = getPixel(x, y);
      pixel = pixel2;
    }
  }
delete scaled;
}

void Image::scale(double factor){
  scale(width()*factor, height()*factor);

}
