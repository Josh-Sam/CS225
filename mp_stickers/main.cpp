#include <iostream>
#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image sky;
  sky.readFromFile("sky.png");
  Image star;
  star.readFromFile("star.png");
  Image ufo;
  ufo.readFromFile("ufo.png");

  StickerSheet sheet(sky,2);
  sheet.addSticker(ufo,250,250);
  sheet.addSticker(star,10,10);

  Image picture = sheet.render();
  picture.writeToFile("myImage.png");


  return 0;
}
