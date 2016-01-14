
//This file contains an array of structures,
//where each structure has a different variable available for printing on the OLED

#ifndef OLED_PRINTING_H
#define OLED_PRINTING_H

#include <Wire.h>
#include <oled_Adafruit_GFX.h>
#include <oled_Adafruit_SSD1306.h>

struct HPSVals
{
    const char* name_of_variable; //name of variable to display
    const char* unit;             //units, 2 char max
    void* variable;         //pointer to variable
    int decimal_places;     //0 for integer, otherwise assume the datatype is double
};

class PrintHPS
{
    private:
        Adafruit_SSD1306 *oled;
        HPSVals* data;
        int index;
        int size;

    public:
        PrintHPS();
        PrintHPS(int size);
        void setSize(int size);      //set the size manually
        const char* add(HPSVals newEntry); //adds an entry to the array
        void resetIndex();           //resets the index to 0
        void setIndex(int index);    //sets the index to a specific number, starts at 0
        int getNext();               //returns the next index in the array (implements a circular array)
        int getPrev();               //returns the previous index in the array (implements a circular array)
        void printHeaders();         //prints the current struct to the OLED
        void initialize_oled(byte addr = 0x3C);      //sets up the interface and displays the splash screen
        void refresh();              //displays the most recent numbers

        void printsomething();
};

#endif
