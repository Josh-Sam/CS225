#include "StickerSheet.h"
#include <cstdint>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <cstdlib>
#include "Image.h"

using namespace cs225;
using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned newMax){
    max = newMax;
    index = 0;
    tempImage = new Image(picture);
    pic = new Image*[max];
    xCoordinate = new int[max];
    yCoordinate = new int[max];
    for(unsigned i = 0; i < max; i++){
      pic[i] = NULL;
  }

}

StickerSheet::~StickerSheet(){
  clear();
}

void StickerSheet::clear(){
  for(unsigned i = 0; i < max; i++){
    if(pic[i] != NULL){
      delete pic[i];
      pic[i] = NULL;
    }
  }
  delete[] pic;
  delete[] xCoordinate;
  delete[] yCoordinate;
  pic = NULL;
  xCoordinate = NULL;
  yCoordinate = NULL;
}

StickerSheet::StickerSheet(const StickerSheet & other){
  copy(other);
}

void StickerSheet::copy(const StickerSheet & other){
  index = other.index;
    max = other.max;
    tempImage = new Image(*other.tempImage);
    pic = new Image*[max];
    xCoordinate = new int[max];
    yCoordinate = new int[max];
    for(unsigned i = 0; i < max; i++){
      if(other.pic[i] != NULL)
        pic[i] = new Image(*(other.pic[i]));
      else
        pic[i] = NULL;
      xCoordinate[i] = other.xCoordinate[i];
      yCoordinate[i] = other.yCoordinate[i];
    }
}

const StickerSheet& StickerSheet::operator= (const StickerSheet & other){
  if (this != &other){
    clear();
    copy(other);
  }
  return *this;
}


void StickerSheet::changeMaxStickers(unsigned newMax){
  if(newMax == max)
      return;
  if(newMax>max){
    Image** newpic = new Image*[newMax];
    for (unsigned i = 0; i < newMax; i++) {
      newpic[i] = NULL;
    }
    int* newxCoordinate = new int[newMax];
    int* newyCoordinate = new int[newMax];
      for(unsigned i = 0; i < index; i++){
        if(pic[i] != NULL){
          newpic[i] = new Image(*pic[i]);
          newxCoordinate[i] = xCoordinate[i];
          newyCoordinate[i] = yCoordinate[i];
        }
      }
    }
    else{
    for(unsigned i = newMax; i < max; i++){
      removeSticker(i);
    }
}
}
int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
  if(index < max){
   for (unsigned i = 0; i < max; i++) {
     if(pic[i] == NULL){
       xCoordinate[i] = x;
       yCoordinate[i] = y;
       pic[i] = new Image(sticker);
       index++;
       return i;
     }
   }
 }
   return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(index < 1 || index >= max || pic[index] == NULL){
    return false;
  }
  else{
    xCoordinate[index] = x;
    yCoordinate[index] = y;
    return true;
  }
}

void StickerSheet::removeSticker(unsigned index){
  if(index >= max || pic[index] == NULL){
    return;
  }
  else{
    delete pic[index];
    pic[index] = NULL;
    xCoordinate[index] = 0;
    yCoordinate[index] = 0;
  }
}

Image* StickerSheet::getSticker(unsigned index) const{
if (index < max) return pic[index];
else return NULL;
}

Image StickerSheet::render() const{
  Image* base = new Image(*tempImage);
    unsigned xMax = base->width();
    unsigned yMax = base->height();
    for (unsigned i = 0; i < index; i++) {
      if(pic[i] != NULL){
      unsigned x = xCoordinate[i] + pic[i]->width();
      unsigned y = yCoordinate[i] + pic[i]->height();
      if(x > xMax)
        xMax = x;
      if(y > yMax)
        yMax = y;
      }
    }
      base->resize(xMax, yMax);

      for(unsigned i = 0; i < index; i++){
        if(pic[i] != NULL){
          for(unsigned x = xCoordinate[i]; x < xCoordinate[i] + pic[i]->width(); x++){
            for (unsigned y = yCoordinate[i]; y < yCoordinate[i] + pic[i]->height(); y++) {
              HSLAPixel basePixel = base->getPixel(x,y);
              HSLAPixel pixel = pic[i]->getPixel(x - xCoordinate[i],y-yCoordinate[i]);
              if(pixel.a != 0){
                basePixel.h = pixel.h;
                basePixel.s = pixel.s;
                basePixel.l = pixel.l;
                basePixel.a = pixel.a;
              }
            }
          }
        }
      }
  Image result = *base;
  return result;
}
