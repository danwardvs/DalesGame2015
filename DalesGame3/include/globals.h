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

extern FONT* load_font();
// A color storing object
// Even though you can store colors as an int
// And use color.getR() color.getG() color.getB()
// to get componants where color is int color;  ;)

//\/\/\    You're literally worse than the Flying Spaghetti Monster

struct colour{
  unsigned char r;
  unsigned char g;
  unsigned char b;
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
  FONT* load_font_from_file();
  FONT* size();
  std::string path;

  scalable_font(){}
  scalable_font(std::string newPath){
    path = newPath;
  }
  void set_path(std::string newPath){
    path = newPath;
  }

  FONT* size(int newSize){
    switch(newSize){
      case 8:return pt8;
      case 10:return pt10;
      case 12:return pt12;
      case 14:return pt14;
      case 16:return pt16;
      case 18:return pt18;
      case 20:return pt20;
      case 22:return pt22;
      case 24:return pt24;
      case 26:return pt26;
      case 28:return pt28;
      case 36:return pt36;
      case 48:return pt48;
      case 72:return pt72;
      default:return pt8;


    }


  }

  void load_all_fonts(){
    pt8 = load_font_from_file(path + "_8.pcx");
    pt10 = load_font_from_file(path + "_10.pcx");
    pt12 = load_font_from_file(path + "_12.pcx");
    pt14 = load_font_from_file(path + "_14.pcx");
    pt16 = load_font_from_file(path + "_16.pcx");
    pt18 = load_font_from_file(path + "_18.pcx");
    pt20 = load_font_from_file(path + "_20.pcx");
    pt22 = load_font_from_file(path + "_22.pcx");
    pt24 = load_font_from_file(path + "_24.pcx");
    pt26 = load_font_from_file(path + "_26.pcx");
    pt28 = load_font_from_file(path + "_28.pcx");
    pt36 = load_font_from_file(path + "_36.pcx");
    pt48 = load_font_from_file(path + "_48.pcx");
    pt72 = load_font_from_file(path + "_72.pcx");
  }

  FONT* load_font_from_file( std::string newFontPath){
    // Load fonts
    FONT* font_5;
    FONT* font_1 = load_font(newFontPath.c_str(), NULL, NULL);
    FONT* font_2 = extract_font_range(font_1, ' ', 'A'-1);
    FONT* font_3 = extract_font_range(font_1, 'A', 'Z');
    FONT* font_4 = extract_font_range(font_1, 'Z'+1, 'z');
    FONT* font_final = merge_fonts(font_4,font_5 = merge_fonts(font_2, font_3));

    // Cleanup
    destroy_font(font_1);
    destroy_font(font_2);
    destroy_font(font_3);
    destroy_font(font_4);
    destroy_font(font_5);

    // Return a pointer to our loaded font
    return font_final;
  }


};


#endif
