#include<allegro.h>
#include<alpng.h>
#include<time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include<string>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

BITMAP* buffer;

int step;

// Fonts
FONT* f1;
FONT* f2;
FONT* f3;
FONT* f4;
FONT* f5;
FONT* ptsans;
FONT* ptsans_big;

bool close_button_pressed;

// FPS System
volatile int ticks = 0;
const int updates_per_second = 60;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

int random_number;

string pitcher1;
string pitcher2;
string pitcher3;
string pitcher4;
string pitcher5;
string pitcher6;

void ticker(){
  ticks++;
}
END_OF_FUNCTION(ticker)

void game_time_ticker(){
  game_time++;
}
END_OF_FUNCTION(ticker)

void close_button_handler(void){
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

// Random number generator. Use int random(highest,lowest);
int random(int newLowest, int newHighest)
{
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest+int(range*rand()/(RAND_MAX + 1.0));
  return randomNumber;
}


//A function to streamline error reporting in file loading
void abort_on_error(const char *message){
	 set_window_title("Error!");
	 if (screen != NULL){
	    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	 }
	 allegro_message("%s.\n %s\n", message, allegro_error);
	 exit(-1);
}



void load_xml(){


    random_number=random(1,122);
    xml_document<> doc;
    xml_node<> * root_node;
    // Read the xml file into a vector
    ifstream theFile ("2b.xml");
    vector<char> xml_buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    xml_buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&xml_buffer[0]);
    // Find our root node
    root_node = doc.first_node("data");
    // Iterate over the brewerys

    for (xml_node<> * brewery_node = root_node->first_node("GeneratedNumber"); brewery_node; brewery_node = brewery_node->next_sibling())
    {

            // Interate over the beers
      int generatedNumberResult = atoi(brewery_node->first_attribute("number")->value());
      if(generatedNumberResult==random_number){

        for(xml_node<> * beer_node = brewery_node->first_node("batResult"); beer_node; beer_node = beer_node->next_sibling())
        {
          pitcher1 = beer_node->first_attribute("pitcher1")->value();
          pitcher2 = beer_node->first_attribute("pitcher2")->value();
          pitcher3 = beer_node->first_attribute("pitcher3")->value();
          pitcher4 = beer_node->first_attribute("pitcher4")->value();
          pitcher5 = beer_node->first_attribute("pitcher5")->value();
          pitcher6 = beer_node->first_attribute("pitcher6")->value();
        }

      }
    }

}
void update(){

    if(key[KEY_ENTER] && step>9){
        load_xml();
        step=0;
    }
    step++;
}

void draw(){
    rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(255,255,255));

    rectfill(buffer,200,20,340,120,makecol(0,0,0));
    textprintf_ex(buffer,ptsans_big,210,10,makecol(255,0,0),makecol(0,0,-1),"%i",random_number);

    rect(buffer,0,148,190,172,makecol(0,0,0));
    rect(buffer,190,148,390,172,makecol(0,0,0));
    rect(buffer,390,148,590,172,makecol(0,0,0));
    rect(buffer,590,148,790,172,makecol(0,0,0));
    rect(buffer,790,148,990,172,makecol(0,0,0));
    rect(buffer,990,148,1200,172,makecol(0,0,0));

    textprintf_ex(buffer,ptsans,10,150,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher1.c_str());
    textprintf_ex(buffer,ptsans,200,150,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher2.c_str());
    textprintf_ex(buffer,ptsans,400,150,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher3.c_str());
    textprintf_ex(buffer,ptsans,600,150,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher4.c_str());
    textprintf_ex(buffer,ptsans,800,150,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher5.c_str());
    textprintf_ex(buffer,ptsans,1000,150,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher6.c_str());
    draw_sprite(screen,buffer,0,0);
}







void setup(){
    buffer=create_bitmap(1200,768);


    // Load fonts
    f1 = load_font("ptsans.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    ptsans = merge_fonts(f4, f5 = merge_fonts(f2, f3));

    f1 = load_font("ptsans_big.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    ptsans_big = merge_fonts(f4, f5 = merge_fonts(f2, f3));


    // Destroy temporary fonts
    destroy_font(f1);
    destroy_font(f2);
    destroy_font(f3);
    destroy_font(f4);
    destroy_font(f5);

    srand(time(NULL));

     // Setup for FPS system
    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(ticker);
    install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));

    LOCK_VARIABLE(game_time);
    LOCK_FUNCTION(game_time_ticker);
    install_int_ex(game_time_ticker, BPS_TO_TIMER(10));

    // Close button
    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);

   // if (!(bmp = load_bitmap("bmp.png", NULL)))
   //   abort_on_error("Cannot find image bmp.png\nPlease check your files and try again");
}






int main(){

  allegro_init();
  alpng_init();
  install_timer();
  install_keyboard();
  install_mouse();
  set_color_depth(32);


  set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,768, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");



  set_window_title("Dale's Game 2015");
  setup();


      while(!key[KEY_ESC] && !close_button_pressed){
        while(ticks == 0){
            rest(1);
        }
    while(ticks > 0){
        int old_ticks = ticks;

        update();

        ticks--;
        if(old_ticks <= ticks){
            break;
        }
    }
        if(game_time - old_time >= 10){
            fps = frames_done;
            frames_done = 0;
            old_time = game_time;
        }
        draw();
    }


	return 0;
}
END_OF_MAIN()
