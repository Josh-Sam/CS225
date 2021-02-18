#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max){
  maximum = max;
  base = picture;
  positionX = new unsigned[maximum];
  positionY = new unsigned[maximum];
  imageSheet = new Image[maximum];
  for(unsigned i = 0; i < maximum; i++){
    imageSheet[i] = nullptr;
  }
}
