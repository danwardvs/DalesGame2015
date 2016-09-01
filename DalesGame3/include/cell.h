/*
 * Cell
 * A versitile scalable coloured rectangle
 * 31/08/16
 * Daniel Vanstemp
 */

#ifndef CELL_H
#define CELL_H

#include <string>
#include <sstream>
#include "allegro.h"
#include "globals.h"


class cell{
  public:
    // Csr
    cell( int newX, int newY, int newWidth, int newHeight, colour newBackgroundColour, colour newTextColour,scalable_font newFont, int newTextSize, std::string newText);

    // Dcsr
    ~cell();

    // Updates cell
    void update();

    bool test_size(int newSize);

    void set_width(int newWidth);
    void set_height(int newHeight);
    void set_text(std::string newText);

    // Draws the cell
    void draw(BITMAP* tempBitmap);

  protected:
  private:
    // Colors
    colour backgroundColour;
    colour textColour;

    // Coordinates
    int x;
    int y;

    // Size
    int width;
    int height;
    int text_size;


    // Text, if it contains any
    std::string text;
    scalable_font font;

};

#endif // ITEM_H
