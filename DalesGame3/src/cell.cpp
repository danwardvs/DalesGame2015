#include "cell.h"

// Construct the cell
cell::cell( int newX, int newY, int newWidth, int newHeight, colour newBackgroundColour, colour newTextColour, scalable_font newFont,int newTextSize, std::string newText){
  x = newX;
  y = newY;
  width = newWidth;
  height = newHeight;
  backgroundColour =  newBackgroundColour;
  textColour = newTextColour;
  text = newText;
  font = newFont;
  text_size = newTextSize;
}

// Deconstruct the cell
cell::~cell(){

}

void cell::set_width(int newWidth){
  width = newWidth;
}
void cell::set_height(int newHeight){
  height = newHeight;
}
void cell::set_text(std::string newText){
  text = newText;
}



// Run cell updates (nothing here :( )
void cell::update(){

}
bool cell::test_size(int newSize){
  if(text_height(font.size(newSize))<height && text_length(font.size(newSize),text.c_str())<width-4 )
    return true;
  return false;

}

// Draw the cell to the screen
void cell::draw( BITMAP* tempBitmap){
    // Draw the cell
    rectfill( tempBitmap, x, y, x + width, y + height, makecol( backgroundColour.r, backgroundColour.g, backgroundColour.b));

    // Draw outline
    rect( tempBitmap, x, y, x + width, y + height, makecol(0,0,0));

    // Draw containing text
    if(text_size!=0){
      textprintf_ex( tempBitmap, font.size(text_size), x+4, y, makecol(textColour.r,textColour.g,textColour.b), makecol(0,0,-1), "%s", text.c_str());

    }else{
      int newSize;
      if(test_size(100)){
        newSize=100;
      }else if(test_size(72)){
        newSize=72;
      }else if(test_size(48)){
        newSize=48;

      }else if(test_size(36)){
        newSize=36;

      }else if(test_size(28)){
        newSize=28;

      }else if(test_size(26)){
        newSize=26;

      }else if(test_size(24)){
        newSize=24;

      }else if(test_size(22)){
        newSize=22;

      }else if(test_size(20)){
        newSize=20;

      }else if(test_size(18)){
        newSize=18;

      }else if(test_size(16)){
        newSize=16;

      }else if(test_size(14)){
        newSize=14;

      }else if(test_size(12)){
        newSize=12;

      }else if(test_size(10)){
        newSize=10;

      }else if(test_size(8)){
        newSize=8;
      }else{
        newSize=0;
      }
      if(newSize!=0)
        textprintf_ex( tempBitmap, font.size(newSize), x+4, y,makecol(textColour.r,textColour.g,textColour.b), makecol(0,0,-1), "%s", text.c_str());
      else
       textprintf_ex( tempBitmap, font.size(newSize), x+4, y, makecol(textColour.r,textColour.g,textColour.b), makecol(0,0,-1), "```");
    }

}
