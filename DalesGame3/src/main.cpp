#include <allegro.h>
#include <alpng.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "globals.h"
#include "cell.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

#define left false
#define centre true

BITMAP* buffer;
BITMAP* cursor;

int step;

scalable_font calibri_bold("fonts/calibri_bold");
scalable_font calibri("fonts/calibri");

void generate_cells();
int batter_number = 1;

// Color defs
colour red( 255, 0, 0);
colour green( 0, 255, 0);
colour blue( 0, 0, 200);
colour teal( 0, 225,225);
colour purple( 255, 0, 255);
colour orange( 255, 100, 0);
colour yellow( 255, 255, 0);
colour white( 255, 255, 255);
colour black( 0, 0, 0);

FONT* load_font();

bool close_button_pressed;

// FPS System
volatile int ticks = 0;
const int updates_per_second = 60;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

int screen_colour = 1;

// Yo Allan set this guy to true for a nice surprise!
bool nicefont=false;

int random_number;
int random_number_steals_throws;
int other_random_numbers[9];

std::string base_result_pitcher[6];


std::string pitcher_ss[6];
std::string pitcher_gs[6];
std::string pitcher_as[6];
std::string pitcher_fs[6];

std::string xml_file;

std::vector<cell> game_cells;


template <class newType>

std::string to_string(newType newValue){
    std::stringstream newStringStream;
    newStringStream << newValue;
    std::string newResult = newStringStream.str();
    return newResult;

}
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
int random(int newLowest, int newHighest){
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
void create_cell(int newX, int newY, int newWidth, int newHeight, colour newBackgroundColour, colour newTextColour, scalable_font newFont,int newTextSize, bool newPosition, std::string newText){
  cell newCell( newX, newY, newWidth, newHeight, newBackgroundColour, newTextColour,newFont, newTextSize, newPosition, newText);
  game_cells.push_back( newCell);
}


void load_xml(){

  rapidxml::xml_document<> doc;
  rapidxml::xml_node<> * root_node;

  // Read the xml file into a vector
  if( batter_number == 1)
    xml_file = "data/1b.xml";
  if( batter_number == 2)
    xml_file = "data/2b.xml";
  if( batter_number == 3)
    xml_file = "data/3b.xml";
  if( batter_number == 4)
    xml_file="data/4b.xml";
  if( batter_number == 5)
    xml_file = "data/5b.xml";
  if( batter_number == 6)
    xml_file = "data/6b.xml";

  // Make an xml object
  std::ifstream theFile (xml_file.c_str());
  std::vector<char> xml_buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
  xml_buffer.push_back('\0');

  // Parse the buffer using the xml file parsing library into doc
  doc.parse<0>(&xml_buffer[0]);

  // Find our root node
  root_node = doc.first_node("data");

  // Iterate over the brewerys
  for (rapidxml::xml_node<> * generated_node = root_node -> first_node("GeneratedNumber"); generated_node; generated_node = generated_node -> next_sibling()){
    // Interate over the beers
    int generatedNumberResult = atoi( generated_node -> first_attribute("number") -> value());
    if( generatedNumberResult == random_number){
      for(rapidxml::xml_node<> * batter_node = generated_node -> first_node("batResult"); batter_node; batter_node = batter_node -> next_sibling()){
        base_result_pitcher[0] = batter_node -> first_attribute("pitcher1" )-> value();
        base_result_pitcher[1] = batter_node -> first_attribute("pitcher2") -> value();
        base_result_pitcher[2] = batter_node -> first_attribute("pitcher3") -> value();
        base_result_pitcher[3] = batter_node -> first_attribute("pitcher4") -> value();
        base_result_pitcher[4] = batter_node -> first_attribute("pitcher5") -> value();
        base_result_pitcher[5] = batter_node -> first_attribute("pitcher6") -> value();
      }
    }
  }
}

void load_slugging_xml(std::string new_xml_file){
  if( random_number > 84 && random_number < 101){
    // Create an xml doc
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> * root_node;

    // Read the xml file into a vector
    std::ifstream theFile (new_xml_file.c_str());
    std::vector<char> xml_buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
    xml_buffer.push_back('\0');

    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>( &xml_buffer[0]);

    // Find our root node
    root_node = doc.first_node("data");

    // Iterate over the brewerys
    for ( rapidxml::xml_node<> * generated_node = root_node -> first_node("GeneratedNumber"); generated_node; generated_node = generated_node -> next_sibling()){
      // Interate over the beers
      int generatedNumberResult = atoi(generated_node -> first_attribute("number") -> value());

      if( generatedNumberResult == random_number){
        for( rapidxml::xml_node<> * pitcher_node = generated_node -> first_node("batResult"); pitcher_node; pitcher_node = pitcher_node -> next_sibling()){
          // Super sluggers
          if( new_xml_file == "data/ss.xml"){
            pitcher_ss[0] = pitcher_node -> first_attribute("pitcher1") -> value();
            pitcher_ss[1] = pitcher_node -> first_attribute("pitcher2") -> value();
            pitcher_ss[2] = pitcher_node -> first_attribute("pitcher3") -> value();
            pitcher_ss[3] = pitcher_node -> first_attribute("pitcher4") -> value();
            pitcher_ss[4] = pitcher_node -> first_attribute("pitcher5") -> value();
            pitcher_ss[5] = pitcher_node -> first_attribute("pitcher6") -> value();
          }
          // Great sluggers
          if( new_xml_file == "data/gs.xml"){
            pitcher_gs[0] = pitcher_node -> first_attribute("pitcher1") -> value();
            pitcher_gs[1] = pitcher_node -> first_attribute("pitcher2") -> value();
            pitcher_gs[2] = pitcher_node -> first_attribute("pitcher3") -> value();
            pitcher_gs[3] = pitcher_node -> first_attribute("pitcher4") -> value();
            pitcher_gs[4] = pitcher_node -> first_attribute("pitcher5") -> value();
            pitcher_gs[5] = pitcher_node -> first_attribute("pitcher6") -> value();
          }
          // Average sluggers
          if( new_xml_file == "data/as.xml"){
            pitcher_as[0] = pitcher_node -> first_attribute("pitcher1") -> value();
            pitcher_as[1] = pitcher_node -> first_attribute("pitcher2") -> value();
            pitcher_as[2] = pitcher_node -> first_attribute("pitcher3") -> value();
            pitcher_as[3] = pitcher_node -> first_attribute("pitcher4") -> value();
            pitcher_as[4] = pitcher_node -> first_attribute("pitcher5") -> value();
            pitcher_as[5] = pitcher_node -> first_attribute("pitcher6") -> value();
          }
          // Failure of a career sluggers (jk fair sluggers)
          // Aha u got me
          if( new_xml_file == "data/fs.xml"){
            pitcher_fs[0] = pitcher_node -> first_attribute("pitcher1") -> value();
            pitcher_fs[1] = pitcher_node -> first_attribute("pitcher2") -> value();
            pitcher_fs[2] = pitcher_node -> first_attribute("pitcher3") -> value();
            pitcher_fs[3] = pitcher_node -> first_attribute("pitcher4") -> value();
            pitcher_fs[4] = pitcher_node -> first_attribute("pitcher5") -> value();
            pitcher_fs[5] = pitcher_node -> first_attribute("pitcher6") -> value();
          }
        }
      }
    }
  }
}

// Update game logic
void update(){

  if(nicefont)game_cells[15].set_width(mouse_x-10);
  if(nicefont)game_cells[15].set_height(mouse_y-200);

  // Change graphics mode while running
  if( key[KEY_F1]){
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024,768, 0, 0);
    game_cells.clear();
    generate_cells();
  }
  if( key[KEY_F2])
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,800, 0, 0);

  // Turn
  if(( key[KEY_ENTER] || key[KEY_ENTER_PAD] || key[KEY_DEL] || key[KEY_SPACE] || key[KEY_DEL_PAD]) && step > 9){
    // Cycle screen colors
    screen_colour++;
    if( screen_colour == 4)
      screen_colour = 1;

    // Reset pitcher values
    for( int i = 0; i < 6; i++){
      pitcher_ss[i] = "";
      pitcher_gs[i] = "";
      pitcher_as[i] = "";
      pitcher_fs[i] = "";
    }

    // Make a list of 9 random numbers
    for( int i = 0; i < 10; i++){
      other_random_numbers[i] = random(1,100);
    }

    // Init all other values
    random_number = random(1,122);
    random_number_steals_throws = random(1,122);
    load_xml();
    load_slugging_xml( "data/ss.xml");
    load_slugging_xml( "data/gs.xml");
    load_slugging_xml( "data/as.xml");
    load_slugging_xml( "data/fs.xml");
    step = 0;
  }

  // Change batters
  if( key[KEY_1] || key[KEY_1_PAD])
    batter_number = 1;
  if( key[KEY_2] || key[KEY_2_PAD])
    batter_number = 2;
  if( key[KEY_3] || key[KEY_3_PAD])
    batter_number = 3;
  if( key[KEY_4] || key[KEY_4_PAD])
    batter_number = 4;
  if( key[KEY_5] || key[KEY_5_PAD])
    batter_number = 5;
  if( key[KEY_6] || key[KEY_6_PAD])
    batter_number = 6;

  //Display colours
  int display_cell = 8;
  if(screen_colour==1)
    game_cells[display_cell].set_background_colour(red);
  if(screen_colour==2)
    game_cells[display_cell].set_background_colour(green);
  if(screen_colour==3)
    game_cells[display_cell].set_background_colour(blue);
  if(screen_colour==4)
    game_cells[display_cell].set_background_colour(yellow);

  // Random numbers
  game_cells[1].set_text(to_string(random_number));
  game_cells[2].set_text(to_string(other_random_numbers[0]));
  game_cells[4].set_text(to_string(other_random_numbers[1]));
  game_cells[5].set_text(to_string(random_number_steals_throws));
  game_cells[6].set_text(to_string(other_random_numbers[2]));
  game_cells[7].set_text(to_string(other_random_numbers[3]));

  game_cells[69].set_text(to_string(other_random_numbers[4]));
  game_cells[70].set_text(to_string(other_random_numbers[5]));
  game_cells[71].set_text(to_string(other_random_numbers[6]));
  game_cells[72].set_text(to_string(other_random_numbers[7]));
  game_cells[73].set_text(to_string(other_random_numbers[8]));
  game_cells[74].set_text(to_string(other_random_numbers[9]));

  // Batter number
  game_cells[0].set_text(to_string(batter_number));

  //Pitcher base results
  for(int i=0; i<6; i++){
    game_cells[i+15].set_text(base_result_pitcher[i]);
  }

  //Fair slugger charts
  for(int i=0; i<6; i++){
    game_cells[i+27].set_text(pitcher_fs[i]);
  }

  //Average slugger charts
  for(int i=0; i<6; i++){
    game_cells[i+39].set_text(pitcher_as[i]);
  }

   //Good slugger charts
  for(int i=0; i<6; i++){
    game_cells[i+51].set_text(pitcher_gs[i]);
  }

  //Good slugger charts
  for(int i=0; i<6; i++){
    game_cells[i+63].set_text(pitcher_ss[i]);
  }

  if(nicefont)
    game_cells[15].set_text("NiCe TeXt! 4allanz");




  // Incriment the step counter
  // You tried
  step++;
}

// Draw all the required graphics to screen
void draw(){

  rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(255,255,255));

  // Draw our nice lil rectangle
  for(unsigned int i = 0; i < game_cells.size(); i++){
    game_cells[i].draw(buffer);
  }

  //textprintf_ex(buffer,calibri_bold.size(28),50,550,makecol(0,0,0),makecol(0,0,-1),"Scalable fonts OP!");
  textprintf_ex(buffer,calibri.size(16),15,12,makecol(0,0,0),makecol(0,0,-1),"Batter Number");

  if(nicefont)game_cells[15].draw(buffer);

  draw_sprite(buffer,cursor,mouse_x,mouse_y);

  // Draw the buffer to the screen
  draw_sprite( screen, buffer, 0, 0);
}


void generate_cells(){


  int spacing_6 = SCREEN_W/6;
  int newTextSize = 18;

  // Batter number entry
  create_cell(10,10,spacing_6-10,180,white,black,calibri_bold,0,centre,"");
  // Main random number display
  create_cell(10+spacing_6,10,200,180,black,red,calibri_bold,100,centre,"");

  // Random number 2 and "Steals and throws" label
  create_cell(10+spacing_6+200,10,200,90,yellow,black,calibri_bold,48,centre,"");
  create_cell(10+spacing_6+200,100,200,90,white,black,calibri,0,centre,"Steals and throws -->");

  // Random number 3 and steals and throws random number
  create_cell(10+spacing_6+200+200,10,200,90,yellow,black,calibri_bold,48,centre,"");
  create_cell(10+spacing_6+200+200,100,200,90,green,black,calibri_bold,48,centre,"");

  // Random number 4 and 5
  create_cell(10+spacing_6+200+200+200,10,200,90,blue,white,calibri_bold,48,centre,"");
  create_cell(10+spacing_6+200+200+200,100,200,90,blue,white,calibri_bold,48,centre,"");

  // Colour changing display
  if(SCREEN_H>768)
    create_cell(0,SCREEN_H-100,SCREEN_W-1,99,white,black,calibri_bold,8,left,"");
  else
    create_cell(0,SCREEN_H-50,SCREEN_W-1,49,white,black,calibri_bold,8,left,"");

  create_cell(0,200,spacing_6,50,blue,white,calibri,newTextSize,left,"Pitcher #1");
  create_cell(spacing_6,200,spacing_6,50,blue,white,calibri,newTextSize,left,"Pitcher #2");
  create_cell(spacing_6*2,200,spacing_6,50,blue,white,calibri,newTextSize,left,"Pitcher #3");
  create_cell(spacing_6*3,200,spacing_6,50,blue,white,calibri,newTextSize,left,"Pitcher #4");
  create_cell(spacing_6*4,200,spacing_6,50,blue,white,calibri,newTextSize,left,"Pitcher #5");
  create_cell(spacing_6*5,200,spacing_6,50,blue,white,calibri,newTextSize,left,"Pitcher #6");

  create_cell(0,250,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6,250,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*2,250,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*3,250,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*4,250,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*5,250,spacing_6,50,white,black,calibri_bold,0,left,"");

  create_cell(0,300,spacing_6,50,teal,black,calibri,newTextSize,left,"Fair Slugger");
  create_cell(spacing_6,300,spacing_6,50,teal,black,calibri,newTextSize,left,"Fair Slugger");
  create_cell(spacing_6*2,300,spacing_6,50,teal,black,calibri,newTextSize,left,"Fair Slugger");
  create_cell(spacing_6*3,300,spacing_6,50,teal,black,calibri,newTextSize,left,"Fair Slugger");
  create_cell(spacing_6*4,300,spacing_6,50,teal,black,calibri,newTextSize,left,"Fair Slugger");
  create_cell(spacing_6*5,300,spacing_6,50,teal,black,calibri,newTextSize,left,"Fair Slugger");

  create_cell(0,350,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6,350,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*2,350,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*3,350,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*4,350,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*5,350,spacing_6,50,white,black,calibri_bold,0,left,"");

  create_cell(0,400,spacing_6,50,green,black,calibri,newTextSize,left,"Average Slugger");
  create_cell(spacing_6,400,spacing_6,50,green,black,calibri,newTextSize,left,"Average Slugger");
  create_cell(spacing_6*2,400,spacing_6,50,green,black,calibri,newTextSize,left,"Average Slugger");
  create_cell(spacing_6*3,400,spacing_6,50,green,black,calibri,newTextSize,left,"Average Slugger");
  create_cell(spacing_6*4,400,spacing_6,50,green,black,calibri,newTextSize,left,"Average Slugger");
  create_cell(spacing_6*5,400,spacing_6,50,green,black,calibri,newTextSize,left,"Average Slugger");

  create_cell(0,450,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6,450,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*2,450,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*3,450,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*4,450,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*5,450,spacing_6,50,white,black,calibri_bold,0,left,"");

  create_cell(0,500,spacing_6,50,yellow,black,calibri,newTextSize,left,"Good Slugger");
  create_cell(spacing_6,500,spacing_6,50,yellow,black,calibri,newTextSize,left,"Good Slugger");
  create_cell(spacing_6*2,500,spacing_6,50,yellow,black,calibri,newTextSize,left,"Good Slugger");
  create_cell(spacing_6*3,500,spacing_6,50,yellow,black,calibri,newTextSize,left,"Good Slugger");
  create_cell(spacing_6*4,500,spacing_6,50,yellow,black,calibri,newTextSize,left,"Good Slugger");
  create_cell(spacing_6*5,500,spacing_6,50,yellow,black,calibri,newTextSize,left,"Good Slugger");

  create_cell(0,550,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6,550,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*2,550,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*3,550,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*4,550,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*5,550,spacing_6,50,white,black,calibri_bold,0,left,"");

  create_cell(0,600,spacing_6,50,orange,black,calibri,newTextSize,left,"Super Slugger");
  create_cell(spacing_6,600,spacing_6,50,orange,black,calibri,newTextSize,left,"Super Slugger");
  create_cell(spacing_6*2,600,spacing_6,50,orange,black,calibri,newTextSize,left,"Super Slugger");
  create_cell(spacing_6*3,600,spacing_6,50,orange,black,calibri,newTextSize,left,"Super Slugger");
  create_cell(spacing_6*4,600,spacing_6,50,orange,black,calibri,newTextSize,left,"Super Slugger");
  create_cell(spacing_6*5,600,spacing_6,50,orange,black,calibri,newTextSize,left,"Super Slugger");

  create_cell(0,650,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6,650,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*2,650,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*3,650,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*4,650,spacing_6,50,white,black,calibri_bold,0,left,"");
  create_cell(spacing_6*5,650,spacing_6,50,white,black,calibri_bold,0,left,"");

  create_cell(0,710,spacing_6,50,yellow,black,calibri_bold,0,centre,"");
  create_cell(spacing_6,710,spacing_6,50,yellow,black,calibri_bold,0,centre,"");
  create_cell(spacing_6*2,710,spacing_6,50,yellow,black,calibri_bold,0,centre,"");
  create_cell(spacing_6*3,710,spacing_6,50,yellow,black,calibri_bold,0,centre,"");
  create_cell(spacing_6*4,710,spacing_6,50,yellow,black,calibri_bold,0,centre,"");
  create_cell(spacing_6*5,710,spacing_6,50,yellow,black,calibri_bold,0,centre,"");





}



void setup(){
  // Init allegro
  allegro_init();
  alpng_init();
  install_timer();
  install_keyboard();
  install_mouse();
  set_color_depth(32);

  // Set window dimensions
  int w, h;
  get_desktop_resolution(&w, &h);
  //set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024,768, 0, 0);
  set_gfx_mode(GFX_AUTODETECT, w,h, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");

  // Title (its a bit more than a number generator)
  set_window_title("OPBL Official Number Generator 2.0");



  // Buffer the size of the screen
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Init randomizer and run once to start
  srand(time(NULL));
  for(int i=0; i<1000; i++){
    random(0,i);
  }

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

  if (!(cursor = load_bitmap("images/cursor.png", NULL)))
    abort_on_error("Cannot find image images/cursor.png\nPlease check your files and try again");

  calibri_bold.load_all_fonts();
  calibri.load_all_fonts();
   // Lil cell


  generate_cells();


  //cell newCell( 300, 10, 1000, 100, green, black,calibri_bold, 0, "Hello world!");
  //game_cells.push_back( newCell);



}

// Main, program starts here
int main(){
  // Setup game
  setup();

  // Run until escap button pressed
  while(!key[KEY_ESC] && !close_button_pressed){
    while(ticks == 0){
      rest(1);
    }
    while(ticks > 0){
      int old_ticks = ticks;

      // Game logic
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
    // Game painting
    draw();
  }

  // Return success
	return 0;
}
END_OF_MAIN()
