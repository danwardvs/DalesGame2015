/*
 * Globals
 * Stores global program variables
 * 31/08/16
 * Allan Legemaate
 */


#ifndef GLOBALS_H
#define GLOBALS_H

#include <allegro.h>
#include <string>

// Fonts
extern FONT *c_8, *c_10, *c_12, *c_14, *c_16, *c_18, *c_20, *c_22, *c_24, *c_26, *c_28, *c_36, *c_48,*c_72;

// A color storing object
// Even though you can store colors as an int
// And use color.getR() color.getG() color.getB()
// to get componants where color is int color;  ;)
struct colour{
  int r;
  int g;
  int b;
  colour(){}
  colour(unsigned char newR, unsigned char newG, unsigned char newB){
    r = newR;
    g = newG;
    b = newB;
  }
};

// Scalable font!
struct scalable_font{
  FONT* pt8;
  FONT* pt10;
  FONT* pt12;
  FONT* pt14;
  FONT* pt16;
  FONT* pt18;
  FONT* pt20;
  FONT* pt22;
  FONT* pt24;
  FONT* pt26;
  FONT* pt28;
  FONT* pt36;
  FONT* pt48;
  FONT* pt72;
  std::string path;

  scalable_font(){}
  scalable_font(std::string newPath){
    path = newPath;
  }

};

#endif
