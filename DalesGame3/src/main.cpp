#include<allegro.h>
#include<alpng.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

#include"globals.h"
#include"cell.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

BITMAP* buffer;

int step;

int batter_number=1;

colour green(0,0,255);

// Fonts
FONT* f1;
FONT* f2;
FONT* f3;
FONT* f4;
FONT* f5;
FONT* ptsans;
FONT* ptsans_big;
FONT* ptsans_108;
FONT* ptsans_48;

bool close_button_pressed;

// FPS System
volatile int ticks = 0;
const int updates_per_second = 60;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

int screen_color=1;

int random_number;
int random_number_steals_throws;
int other_random_numbers[6];

std::string pitcher1;
std::string pitcher2;
std::string pitcher3;
std::string pitcher4;
std::string pitcher5;
std::string pitcher6;

std::string pitcher_ss[6];
std::string pitcher_gs[6];
std::string pitcher_as[6];
std::string pitcher_fs[6];

std::string xml_file;

std::vector<cell> game_cells;

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

    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> * root_node;
    // Read the xml file into a vector
    if(batter_number==1)xml_file="1b.xml";
    if(batter_number==2)xml_file="2b.xml";
    if(batter_number==3)xml_file="3b.xml";
    if(batter_number==4)xml_file="4b.xml";
    if(batter_number==5)xml_file="5b.xml";
    if(batter_number==6)xml_file="6b.xml";

    std::ifstream theFile (xml_file.c_str());
    std::vector<char> xml_buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
    xml_buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&xml_buffer[0]);
    // Find our root node
    root_node = doc.first_node("data");
    // Iterate over the brewerys

    for (rapidxml::xml_node<> * brewery_node = root_node->first_node("GeneratedNumber"); brewery_node; brewery_node = brewery_node->next_sibling())
    {

            // Interate over the beers
      int generatedNumberResult = atoi(brewery_node->first_attribute("number")->value());
      if(generatedNumberResult==random_number){

        for(rapidxml::xml_node<> * beer_node = brewery_node->first_node("batResult"); beer_node; beer_node = beer_node->next_sibling())
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
void load_slugging_xml(std::string new_xml_file){

    if(random_number>84 && random_number<101){

    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> * root_node;
    // Read the xml file into a vector


    std::ifstream theFile (new_xml_file.c_str());
    std::vector<char> xml_buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
    xml_buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&xml_buffer[0]);
    // Find our root node
    root_node = doc.first_node("data");
    // Iterate over the brewerys


    for (rapidxml::xml_node<> * brewery_node = root_node->first_node("GeneratedNumber"); brewery_node; brewery_node = brewery_node->next_sibling())
    {

            // Interate over the beers
      int generatedNumberResult = atoi(brewery_node->first_attribute("number")->value());


      if(generatedNumberResult==random_number){

        for(rapidxml::xml_node<> * beer_node = brewery_node->first_node("batResult"); beer_node; beer_node = beer_node->next_sibling())
        {
          if(new_xml_file=="ss.xml"){
          pitcher_ss[0] = beer_node->first_attribute("pitcher1")->value();
          pitcher_ss[1] = beer_node->first_attribute("pitcher2")->value();
          pitcher_ss[2] = beer_node->first_attribute("pitcher3")->value();
          pitcher_ss[3] = beer_node->first_attribute("pitcher4")->value();
          pitcher_ss[4] = beer_node->first_attribute("pitcher5")->value();
          pitcher_ss[5] = beer_node->first_attribute("pitcher6")->value();
          }
          if(new_xml_file=="gs.xml"){
          pitcher_gs[0] = beer_node->first_attribute("pitcher1")->value();
          pitcher_gs[1] = beer_node->first_attribute("pitcher2")->value();
          pitcher_gs[2] = beer_node->first_attribute("pitcher3")->value();
          pitcher_gs[3] = beer_node->first_attribute("pitcher4")->value();
          pitcher_gs[4] = beer_node->first_attribute("pitcher5")->value();
          pitcher_gs[5] = beer_node->first_attribute("pitcher6")->value();
          }
          if(new_xml_file=="as.xml"){
          pitcher_as[0] = beer_node->first_attribute("pitcher1")->value();
          pitcher_as[1] = beer_node->first_attribute("pitcher2")->value();
          pitcher_as[2] = beer_node->first_attribute("pitcher3")->value();
          pitcher_as[3] = beer_node->first_attribute("pitcher4")->value();
          pitcher_as[4] = beer_node->first_attribute("pitcher5")->value();
          pitcher_as[5] = beer_node->first_attribute("pitcher6")->value();
          }
          if(new_xml_file=="fs.xml"){
          pitcher_fs[0] = beer_node->first_attribute("pitcher1")->value();
          pitcher_fs[1] = beer_node->first_attribute("pitcher2")->value();
          pitcher_fs[2] = beer_node->first_attribute("pitcher3")->value();
          pitcher_fs[3] = beer_node->first_attribute("pitcher4")->value();
          pitcher_fs[4] = beer_node->first_attribute("pitcher5")->value();
          pitcher_fs[5] = beer_node->first_attribute("pitcher6")->value();
          }


        }

      }

      }
    }

}

void update(){

    if(key[KEY_F1])set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,399, 0, 0);
    if(key[KEY_F2])set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,800, 0, 0);


    if((key[KEY_ENTER] || key[KEY_ENTER_PAD] || key[KEY_DEL] || key[KEY_SPACE] ||key[KEY_DEL_PAD] ) && step>9){

        screen_color++;
        if(screen_color==4)screen_color=1;

        for(int i; i<6; i++){
          pitcher_ss[i]="";
          pitcher_gs[i]="";
          pitcher_as[i]="";
          pitcher_fs[i]="";
        }
        for(int i; i<5; i++){
          other_random_numbers[i]=random(1,100);
        }

        random_number=random(1,122);
        random_number_steals_throws=random(1,122);
        load_xml();
        load_slugging_xml("ss.xml");
        load_slugging_xml("gs.xml");
        load_slugging_xml("as.xml");
        load_slugging_xml("fs.xml");
        step=0;
    }
    if(key[KEY_1] || key[KEY_1_PAD])batter_number=1;
    if(key[KEY_2] || key[KEY_2_PAD])batter_number=2;
    if(key[KEY_3] || key[KEY_3_PAD])batter_number=3;
    if(key[KEY_4] || key[KEY_4_PAD])batter_number=4;
    if(key[KEY_5] || key[KEY_5_PAD])batter_number=5;
    if(key[KEY_6] || key[KEY_6_PAD])batter_number=6;

    step++;
}

void draw(){
    rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(255,255,255));
    for(int i=0; i<game_cells.size(); i++){
      game_cells[i].draw(buffer);
    }

    draw_sprite(screen,buffer,0,0);
}







void setup(){

    cell newCell(10,10,20,20,green,green,"Hello world!");
    game_cells.push_back(newCell);

    buffer=create_bitmap(SCREEN_W,SCREEN_H);


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

    f1 = load_font("ptsans_108.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    ptsans_108 = merge_fonts(f4, f5 = merge_fonts(f2, f3));

    f1 = load_font("ptsans_48.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    ptsans_48 = merge_fonts(f4, f5 = merge_fonts(f2, f3));


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


  int w, h;
  get_desktop_resolution(&w, &h);

  set_gfx_mode(GFX_AUTODETECT, w,h, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");



  set_window_title("OPBL Official Number Generator 2.0");
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
