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
  if(key[KEY_ENTER] && step>9){
    random_number=random(1,122);
    step=0;

    xml_document<> doc;
    xml_node<> * root_node;
    // Read the xml file into a vector
    ifstream theFile ("1b.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);
    // Find our root node
    root_node = doc.first_node("data");
    // Iterate over the brewerys
    for (xml_node<> * brewery_node = root_node->first_node("GeneratedNumber"); brewery_node; brewery_node = brewery_node->next_sibling())
    {

      int asdf = atoi(brewery_node->first_attribute("number")->value());
      if(asdf==random_number){

            // Interate over the beers
	    for(xml_node<> * beer_node = brewery_node->first_node("batResult"); beer_node; beer_node = beer_node->next_sibling())
	    {

        pitcher1 = beer_node->first_attribute("pitcher1")->value();
        pitcher2 = beer_node->first_attribute("pitcher2")->value();
        pitcher3 = beer_node->first_attribute("pitcher3")->value();
        pitcher4 = beer_node->first_attribute("pitcher4")->value();
        pitcher5 = beer_node->first_attribute("pitcher5")->value();
        pitcher6 = beer_node->first_attribute("pitcher6")->value();



      //textprintf_ex(al_buffer,font,10,40+y,makecol(0,0,0),makecol(0,0,-1),"I gave it the following review: %s", beer_node->value());
	    }
	    }

	}


  }

  if(key[KEY_UP])scrolly+=10;
  if(key[KEY_DOWN])scrolly-=10;
  step++;



}
void load_xml(){

	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile ("1b.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("data");
	// Iterate over the brewerys
	int y=-60;
	for (xml_node<> * brewery_node = root_node->first_node("GeneratedNumber"); brewery_node; brewery_node = brewery_node->next_sibling())
	{
    y+=80;
    //if(brewery_node->first_attribute("number")->value()=)
      textprintf_ex(al_buffer,font,10,40+y+scrolly,makecol(0,0,0),makecol(0,0,-1),"Generated number is %s",
        brewery_node->first_attribute("number")->value()
      );
            // Interate over the beers
	    for(xml_node<> * beer_node = brewery_node->first_node("batResult"); beer_node; beer_node = beer_node->next_sibling())
	    {

	    	textprintf_ex(al_buffer,font,10,50+y+scrolly,makecol(0,0,0),makecol(0,0,-1),"1P:%s", beer_node->first_attribute("pitcher1")->value());
        textprintf_ex(al_buffer,font,10,60+y+scrolly,makecol(0,0,0),makecol(0,0,-1),"2P:%s", beer_node->first_attribute("pitcher2")->value());
        textprintf_ex(al_buffer,font,10,70+y+scrolly,makecol(0,0,0),makecol(0,0,-1),"3P:%s", beer_node->first_attribute("pitcher3")->value());
        textprintf_ex(al_buffer,font,10,80+y+scrolly,makecol(0,0,0),makecol(0,0,-1),"4P:%s", beer_node->first_attribute("pitcher4")->value());
        textprintf_ex(al_buffer,font,10,90+y+scrolly,makecol(0,0,0),makecol(0,0,-1),"5P:%s", beer_node->first_attribute("pitcher5")->value());
        textprintf_ex(al_buffer,font,10,100+y+scrolly,makecol(0,0,0),makecol(0,0,-1),"6P:%s", beer_node->first_attribute("pitcher6")->value());




      //textprintf_ex(al_buffer,font,10,40+y,makecol(0,0,0),makecol(0,0,-1),"I gave it the following review: %s", beer_node->value());

	    }

	}

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


  set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768, 0, 0);
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
