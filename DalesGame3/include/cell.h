#ifndef CELL_H
#define CELL_H

#include <string>
#include <sstream>
#include "allegro.h"
#include "globals.h"

class cell
{
  public:
    cell(int newX, int newY, int newWidth, int newHeight, colour newBackgroundColour, colour newTextColour, std::string newText);

    void update();
    void draw(BITMAP* tempBitmap);

  protected:
  private:
    colour backgroundColour;
    colour textColour;
    int x;
    int y;
    int width;
    int height;
    std::string text;


};

#endif // ITEM_H
