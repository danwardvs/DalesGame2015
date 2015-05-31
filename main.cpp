#include<allegro.h>
#include<alpng.h>
#include<time.h>
#include<iostream>
#include <fstream>
#include<vector>
#include<string>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

BITMAP* al_buffer;

bool close_button_pressed;

int random_number=0;

int step;
int scrolly;

char* pitcher1="NA";
char* pitcher2="NA";
char* pitcher3="NA";
char* pitcher4="NA";
char* pitcher5="NA";
char* pitcher6="NA";

// FPS System
volatile int ticks = 0;
const int updates_per_second = 60;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

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

/*
//Convert int to string
string convertInt(int number){
   stringstream ss;
   ss << number;
   return ss.str();
}

//Convert string to int
int convertStringToInt(string newString){
  int result;
  stringstream(newString) >> result;
  return result;
}
*/

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

void update(){
  if(step>-1){
    random_number++;
    if(random_number==68)random_number=1;
    step=0;




  }
  step++;



}



void draw(){



    rectfill(al_buffer,0,0,SCREEN_W,SCREEN_H,makecol(255,255,255));
    textprintf_ex(al_buffer,font,10,10,makecol(0,0,0),makecol(0,0,-1),"%i",random_number);
    //load_xml();

    textprintf_ex(al_buffer,font,10,50,makecol(0,0,0),makecol(0,0,-1),"1P:%s", pitcher1);
     textprintf_ex(al_buffer,font,10,60,makecol(0,0,0),makecol(0,0,-1),"2P:%s", pitcher2);
     textprintf_ex(al_buffer,font,10,70,makecol(0,0,0),makecol(0,0,-1),"3P:%s",pitcher3);
     textprintf_ex(al_buffer,font,10,80,makecol(0,0,0),makecol(0,0,-1),"4P:%s",pitcher4);
     textprintf_ex(al_buffer,font,10,90,makecol(0,0,0),makecol(0,0,-1),"5P:%s", pitcher5);
     textprintf_ex(al_buffer,font,10,100,makecol(0,0,0),makecol(0,0,-1),"6P:%s",pitcher6);

    draw_sprite(screen,al_buffer,0,0);
}







void setup(){
    al_buffer=create_bitmap(1024,768);


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


  set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600, 0, 0);
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
