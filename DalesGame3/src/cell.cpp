
#include "cell.h"

cell::cell(int newX, int newY, int newWidth, int newHeight, colour newBackgroundColour, colour newTextColour, std::string newText){
  x = newX;
  y = newY;
  width = newWidth;
  height = newHeight;
  backgroundColour =  newBackgroundColour;
  textColour = newTextColour;
  text = newText;

}
void cell::update(){

}

void cell::draw(BITMAP* tempBitmap){
    //rect(tempBitmap,x,y,x+width,y+height,makecol(0,0,0));
    rect(tempBitmap,0,0,10,10,makecol(0,0,0));
    int a;
}
