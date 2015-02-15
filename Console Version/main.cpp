#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

// Random number generator. Use int random(highest,lowest);
int random(int newLowest, int newHighest)
{
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest+int(range*rand()/(RAND_MAX + 1.0));
  return randomNumber;
}

int main(void)
{
  while(2>1){

    int random_number=random(1,122);
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
    system("cls");

    for (xml_node<> * brewery_node = root_node->first_node("GeneratedNumber"); brewery_node; brewery_node = brewery_node->next_sibling())
    {

            // Interate over the beers
      int generatedNumberResult = atoi(brewery_node->first_attribute("number")->value());
      if(generatedNumberResult==random_number){

          printf("Generated Number:%s\n\n",brewery_node->first_attribute("number")->value());
        for(xml_node<> * beer_node = brewery_node->first_node("batResult"); beer_node; beer_node = beer_node->next_sibling())
        {
          printf("1P:%s\n",beer_node->first_attribute("pitcher1")->value());
          printf("1P:%s\n",beer_node->first_attribute("pitcher2")->value());
          printf("1P:%s\n",beer_node->first_attribute("pitcher3")->value());
          printf("1P:%s\n",beer_node->first_attribute("pitcher4")->value());
          printf("1P:%s\n",beer_node->first_attribute("pitcher5")->value());
          printf("1P:%s\n",beer_node->first_attribute("pitcher6")->value());
        }
        system("pause");
        cout << endl;
      }
    }

  }
}
