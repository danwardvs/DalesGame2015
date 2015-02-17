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

int batter_number=1;

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

int random_number;
int random_number_steals_throws;
int other_random_numbers[6];

string pitcher1;
string pitcher2;
string pitcher3;
string pitcher4;
string pitcher5;
string pitcher6;

string pitcher_ss[6];
string pitcher_gs[6];
string pitcher_as[6];
string pitcher_fs[6];

string xml_file;

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

    xml_document<> doc;
    xml_node<> * root_node;
    // Read the xml file into a vector
    if(batter_number==1)xml_file="1b.xml";
    if(batter_number==2)xml_file="2b.xml";
    if(batter_number==3)xml_file="3b.xml";
    if(batter_number==4)xml_file="4b.xml";
    if(batter_number==5)xml_file="5b.xml";
    if(batter_number==6)xml_file="6b.xml";

    ifstream theFile (xml_file.c_str());
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
void load_slugging_xml(string new_xml_file){

    if(random_number>84 && random_number<101){

    xml_document<> doc;
    xml_node<> * root_node;
    // Read the xml file into a vector


    ifstream theFile (new_xml_file.c_str());
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


    if((key[KEY_ENTER] || key[KEY_ENTER_PAD] || key[KEY_DEL] || key[KEY_SPACE] ||key[KEY_DEL_PAD] ) && step>9){

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

    rectfill(buffer,205,10,390,135,makecol(0,0,0));
    textprintf_ex(buffer,ptsans_108,210,-25,makecol(255,0,0),makecol(0,0,-1),"%i",random_number);
    textprintf_ex(buffer,ptsans_big,25,13,makecol(0,0,0),makecol(0,0,-1),"%i",batter_number);
    textprintf_ex(buffer,ptsans,10,10,makecol(0,0,0),makecol(0,0,-1),"Batter Number");



    rectfill(buffer,391,10,640,77,makecol(255,255,0));
    rect(buffer,391,10,515,77,makecol(0,0,0));
    rect(buffer,391,77,515,135,makecol(0,0,0));

    rectfill(buffer,516,77,640,135,makecol(0,255,0));
    rect(buffer,515,10,640,77,makecol(0,0,0));
    rect(buffer,515,77,640,135,makecol(0,0,0));

    rectfill(buffer,641,10,765,135,makecol(51,51,153));
    rect(buffer,640,10,765,135,makecol(0,0,0));
    rect(buffer,640,77,765,135,makecol(0,0,0));


    textprintf_ex(buffer,ptsans_48,420,4,makecol(0,0,0),makecol(0,0,-1),"%i",other_random_numbers[0]);
    textprintf_ex(buffer,ptsans_48,544,4,makecol(0,0,0),makecol(0,0,-1),"%i",other_random_numbers[1]);
    textprintf_ex(buffer,ptsans_48,668,65,makecol(255,255,255),makecol(0,0,-1),"%i",other_random_numbers[2]);
    textprintf_ex(buffer,ptsans_48,668,4,makecol(255,255,255),makecol(0,0,-1),"%i",other_random_numbers[3]);

    textprintf_ex(buffer,ptsans_48,544,65,makecol(0,0,0),makecol(0,0,-1),"%i",random_number_steals_throws);

    textprintf_ex(buffer,ptsans,398,100,makecol(0,0,0),makecol(0,0,-1),"Steals and throws>");


    rectfill(buffer,0,148,1199,168,makecol(0,0,200));
    rectfill(buffer,0,188,1199,208,makecol(51,204,204));
    rectfill(buffer,0,228,1199,248,makecol(0,255,0));
    rectfill(buffer,0,268,1199,288,makecol(255,204,0));
    rectfill(buffer,0,308,1199,328,makecol(255,102,0));

    rect(buffer,0,188,1199,208,makecol(0,0,0));
    rect(buffer,0,228,1199,248,makecol(0,0,0));
    rect(buffer,0,268,1199,288,makecol(0,0,0));
    rect(buffer,0,308,1199,328,makecol(0,0,0));



    rect(buffer,0,148,1199,168,makecol(0,0,0));

    rect(buffer,0,148,1199,348,makecol(0,0,0));

    rect(buffer,190,148,390,348,makecol(0,0,0));
    rect(buffer,590,148,790,348,makecol(0,0,0));
    rect(buffer,990,148,1199,348,makecol(0,0,0));


    textprintf_ex(buffer,ptsans,10,170,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher1.c_str());
    textprintf_ex(buffer,ptsans,200,170,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher2.c_str());
    textprintf_ex(buffer,ptsans,400,170,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher3.c_str());
    textprintf_ex(buffer,ptsans,600,170,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher4.c_str());
    textprintf_ex(buffer,ptsans,800,170,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher5.c_str());
    textprintf_ex(buffer,ptsans,1000,170,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher6.c_str());

    textprintf_ex(buffer,ptsans,10,210,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_fs[0].c_str());
    textprintf_ex(buffer,ptsans,200,210,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_fs[1].c_str());
    textprintf_ex(buffer,ptsans,400,210,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_fs[2].c_str());
    textprintf_ex(buffer,ptsans,600,210,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_fs[3].c_str());
    textprintf_ex(buffer,ptsans,800,210,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_fs[4].c_str());
    textprintf_ex(buffer,ptsans,1000,210,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_fs[5].c_str());

    textprintf_ex(buffer,ptsans,10,250,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_as[0].c_str());
    textprintf_ex(buffer,ptsans,200,250,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_as[1].c_str());
    textprintf_ex(buffer,ptsans,400,250,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_as[2].c_str());
    textprintf_ex(buffer,ptsans,600,250,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_as[3].c_str());
    textprintf_ex(buffer,ptsans,800,250,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_as[4].c_str());
    textprintf_ex(buffer,ptsans,1000,250,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_as[5].c_str());

    textprintf_ex(buffer,ptsans,10,290,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_gs[0].c_str());
    textprintf_ex(buffer,ptsans,200,290,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_gs[1].c_str());
    textprintf_ex(buffer,ptsans,400,290,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_gs[2].c_str());
    textprintf_ex(buffer,ptsans,600,290,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_gs[3].c_str());
    textprintf_ex(buffer,ptsans,800,290,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_gs[4].c_str());
    textprintf_ex(buffer,ptsans,1000,290,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_gs[5].c_str());

    textprintf_ex(buffer,ptsans,10,330,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_ss[0].c_str());
    textprintf_ex(buffer,ptsans,200,330,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_ss[1].c_str());
    textprintf_ex(buffer,ptsans,400,330,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_ss[2].c_str());
    textprintf_ex(buffer,ptsans,600,330,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_ss[3].c_str());
    textprintf_ex(buffer,ptsans,800,330,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_ss[4].c_str());
    textprintf_ex(buffer,ptsans,1000,330,makecol(0,0,0),makecol(0,0,-1),"%s", pitcher_ss[5].c_str());


    textprintf_ex(buffer,ptsans,10,150,makecol(255,255,255),makecol(0,0,-1),"Pitcher #1");
    textprintf_ex(buffer,ptsans,200,150,makecol(255,255,255),makecol(0,0,-1),"Pitcher #2");
    textprintf_ex(buffer,ptsans,400,150,makecol(255,255,255),makecol(0,0,-1),"Pitcher #3");
    textprintf_ex(buffer,ptsans,600,150,makecol(255,255,255),makecol(0,0,-1),"Pitcher #4");
    textprintf_ex(buffer,ptsans,800,150,makecol(255,255,255),makecol(0,0,-1),"Pitcher #5");
    textprintf_ex(buffer,ptsans,1000,150,makecol(255,255,255),makecol(0,0,-1),"Pitcher #6");

    textprintf_ex(buffer,ptsans,10,188,makecol(0,0,0),makecol(0,0,-1),"Fair Slugger");
    textprintf_ex(buffer,ptsans,200,188,makecol(0,0,0),makecol(0,0,-1),"Fair Slugger");
    textprintf_ex(buffer,ptsans,400,188,makecol(0,0,0),makecol(0,0,-1),"Fair Slugger");
    textprintf_ex(buffer,ptsans,600,188,makecol(0,0,0),makecol(0,0,-1),"Fair Slugger");
    textprintf_ex(buffer,ptsans,800,188,makecol(0,0,0),makecol(0,0,-1),"Fair Slugger");
    textprintf_ex(buffer,ptsans,1000,188,makecol(0,0,0),makecol(0,0,-1),"Fair Slugger");

    textprintf_ex(buffer,ptsans,10,228,makecol(0,0,0),makecol(0,0,-1),"Average Slugger");
    textprintf_ex(buffer,ptsans,200,228,makecol(0,0,0),makecol(0,0,-1),"Average Slugger");
    textprintf_ex(buffer,ptsans,400,228,makecol(0,0,0),makecol(0,0,-1),"Average Slugger");
    textprintf_ex(buffer,ptsans,600,228,makecol(0,0,0),makecol(0,0,-1),"Average Slugger");
    textprintf_ex(buffer,ptsans,800,228,makecol(0,0,0),makecol(0,0,-1),"Average Slugger");
    textprintf_ex(buffer,ptsans,1000,228,makecol(0,0,0),makecol(0,0,-1),"Average Slugger");

    textprintf_ex(buffer,ptsans,10,268,makecol(0,0,0),makecol(0,0,-1),"Good Slugger");
    textprintf_ex(buffer,ptsans,200,268,makecol(0,0,0),makecol(0,0,-1),"Good Slugger");
    textprintf_ex(buffer,ptsans,400,268,makecol(0,0,0),makecol(0,0,-1),"Good Slugger");
    textprintf_ex(buffer,ptsans,600,268,makecol(0,0,0),makecol(0,0,-1),"Good Slugger");
    textprintf_ex(buffer,ptsans,800,268,makecol(0,0,0),makecol(0,0,-1),"Good Slugger");
    textprintf_ex(buffer,ptsans,1000,268,makecol(0,0,0),makecol(0,0,-1),"Good Slugger");

    textprintf_ex(buffer,ptsans,10,308,makecol(0,0,0),makecol(0,0,-1),"Super Slugger");
    textprintf_ex(buffer,ptsans,200,308,makecol(0,0,0),makecol(0,0,-1),"Super Slugger");
    textprintf_ex(buffer,ptsans,400,308,makecol(0,0,0),makecol(0,0,-1),"Super Slugger");
    textprintf_ex(buffer,ptsans,600,308,makecol(0,0,0),makecol(0,0,-1),"Super Slugger");
    textprintf_ex(buffer,ptsans,800,308,makecol(0,0,0),makecol(0,0,-1),"Super Slugger");
    textprintf_ex(buffer,ptsans,1000,308,makecol(0,0,0),makecol(0,0,-1),"Super Slugger");

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


  set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,768, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");



  set_window_title("SPBL Official Number Generator 1.0");
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
