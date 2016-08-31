#ifndef GLOBALS_H
#define GLOBALS_H

FONT *c_8,*c_10,*c_12,*c_14,*c_16,*c_18,*c_20,*c_22,*c_24,*c_26,*c_28,*c_36,*c_48,*c_72;

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
/*
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
*/

#endif
