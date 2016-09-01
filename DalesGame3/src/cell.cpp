#include "cell.h"

// Construct the cell
cell::cell( int newX, int newY, int newWidth, int newHeight, colour newBackgroundColour, colour newTextColour, std::string newText){
  x = newX;
  y = newY;
  width = newWidth;
  height = newHeight;
  backgroundColour =  newBackgroundColour;
  textColour = newTextColour;
  text = newText;
}

// Deconstruct the cell
cell::~cell(){

}

// Run cell updates (nothing here :( )
void cell::update(){

}

// Draw the cell to the screen
void cell::draw( BITMAP* tempBitmap){
    // Draw the cell
    rectfill( tempBitmap, x, y, x + width, y + height, makecol( backgroundColour.r, backgroundColour.g, backgroundColour.b));

    // Draw outline
    rect( tempBitmap, x, y, x + width, y + height, makecol(0,0,0));

    // Draw containing text
    textprintf_ex( tempBitmap, c_8, x, y, makecol(0,0,0), makecol(0,0,-1), "%s", text.c_str());
}
