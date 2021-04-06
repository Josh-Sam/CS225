#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  t=NULL;

  unsigned int width = 0;
  unsigned int height = 0;
  unsigned int aw= base_.width();
  unsigned int ah = base_.height();

  pointsV.resize(aw,std::vector<bool>(ah));
  while(width<aw)
  {
    while(height<ah)
    {
      pointsV[width][height]=false;
      height++;
    }
    width++;
  }
}


bool ImageTraversal::Iterator::isAllowed(Point p)
{
  Point temp  = p;
  if(temp.y>=base_.height() || temp.x>=base_.width()) return false;
  if(temp.y<base_.height() && temp.x<base_.width())
  {
    HSLAPixel & begin = base_.getPixel(start_.x,start_.y);
    HSLAPixel & position = base_.getPixel(temp.x,temp.y);
    if(calculateDelta(begin,position)<tol_)
    {
      if(pointsV[temp.x][temp.y]==false)
      {
        return true;
      }
    }
  }
  return false;

}

ImageTraversal::Iterator::Iterator(ImageTraversal* imaget,PNG png, Point p, double d)
{
  t = imaget;
  base_ = png;
  start_=p;
  pos_= p;
  tol_ = d;
  unsigned int width = 0;
  unsigned int height = 0;
  unsigned int aw= base_.width();
  unsigned int ah = base_.height();
  pointsV.resize(aw,std::vector<bool>(ah));
  while(width<aw)
  {
    height = 0;
    while(height<ah)
    {
      pointsV[width][height]=false;
      height++;
    }
    width++;
  }

  if(!isAllowed(pos_)==false)
  {
    pointsV[pos_.x][pos_.y]=true;
  }

}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  pointsV[pos_.x][pos_.y]=true;
  Point right, left, above, below;
  right = Point(pos_.x+1,pos_.y);
  left = Point(pos_.x-1,pos_.y);
  above = Point(pos_.x,pos_.y-1);
  below = Point(pos_.x,pos_.y+1);
  if(isAllowed(right)){ t->add(right);}
  if(isAllowed(below)){ t->add(below);}
  if(isAllowed(left)) {t->add(left);}
  if(isAllowed(above)) {t->add(above);}
  while(t->empty()!=true && isAllowed(t->peek())!=true)
  {
    t->pop();
    if(t->empty())
    {
      return *this;
    }
  }
  if(t->empty()==false)
  {
    pos_ = t->peek();
    return *this;
  }
  else
  {
    t = NULL;
    return *this;
  }
  return *this;
}


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return pos_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  bool thisEmpty = false;
  bool otherEmpty = false;

  if (t == NULL) { thisEmpty = true; }
  if (other.t == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = t->empty(); }
  if (!otherEmpty) { otherEmpty = other.t->empty(); }

  if (thisEmpty && otherEmpty) return false;
  else if ((!thisEmpty)&&(!otherEmpty)) return (t != other.t);
  else return true;
}
