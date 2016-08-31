#ifndef GLOBALS_H
#define GLOBALS_H


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

#endif
