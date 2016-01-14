
#include "oled_printing.h"

PrintHPS::PrintHPS()
{
    oled = new Adafruit_SSD1306(4);
    size = 0;
    index = 0;
    data = new HPSVals[size];
}

PrintHPS::PrintHPS(int size)
{
    oled = new Adafruit_SSD1306(4);
    this->size = size;
    index = 0;
    data = new HPSVals[size];
}

void PrintHPS::setSize(int size)
{
    this->size = size;
    delete data;
    data = new HPSVals[size];
}

const char* PrintHPS::add(HPSVals newEntry)
{
    if (index < size)
    {
        data[index] = newEntry;
        index++;
        return "Entry added.";
    }
    return "Addition failed - No more room in the array.";
}

void PrintHPS::resetIndex()
{
    index = 0;
}

void PrintHPS::setIndex(int index)
{
    this->index = index;
}

int PrintHPS::getNext()
{
    int output = index;
    output++;
    if (output == size) output = 0; //wrap back to the beginning if we advance too far
    return output;
}

int PrintHPS::getPrev()
{
    int output = index;
    output--;
    if (output < 0) output = size-1; //go to the last element if we go back too far
    return output;
}

//does not print the value of the varible, only sets up the screen with the title and prev/next indicators
void PrintHPS::printHeaders()
{
    oled->clearDisplay();
    oled->setTextColor(WHITE, BLACK);
    oled->setCursor(0,0);
    oled->setTextSize(2);
    oled->println(data[index].name_of_variable);
    oled->setCursor(0,56);
    oled->setTextSize(1);
    oled->print("< ");
    oled->print(data[getPrev()].name_of_variable);
    oled->print("   ");
    oled->print(data[getNext()].name_of_variable);
    oled->print(" >");
    oled->display();
}

void PrintHPS::initialize_oled(byte addr)
{
    //Adafruit splash screen is in the buffer by default
    oled->begin(SSD1306_SWITCHCAPVCC, addr);
    oled->display();
}

void PrintHPS::printsomething(){
    oled->clearDisplay();
    uint8_t color = WHITE;
    for (int16_t i=0; i<oled->height()/2-2; i+=2)
    {
        oled->fillRoundRect(i, i, oled->width()-2*i, oled->height()-2*i, oled->height()/4, color);
        if (color == WHITE) color = BLACK;
        else color = WHITE;
        oled->display();
    }
}

void PrintHPS::refresh()
{
    oled->setCursor(0,16);
    oled->setTextSize(3);

    if (data[index].decimal_places == 0) oled->print(*(int*)data[index].variable);
    else oled->print(*(double*)data[index].variable, data[index].decimal_places);

    oled->setTextSize(1);
    oled->println(data[index].unit);
    oled->display();
}






