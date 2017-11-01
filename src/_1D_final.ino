#include <Arduino.h>
#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 5
#define WIDTH_OF_SCREEN 5
#define HEIGHT_OF_SCREEN 1
#define DATA_PIN 3
#define CLOCK_PIN 5
#define NUM_INPUTS 5
CRGB leds[NUM_LEDS];


#include <Wire.h>
#include "Adafruit_MPR121.h"


int wiresXY [WIDTH_OF_SCREEN][HEIGHT_OF_SCREEN];

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup(){
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  // cap stuff ------------------------------
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  // LED STUF -----------------------------
  // FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);

  //  horizonal
  for (int i = 0 ; i < WIDTH_OF_SCREEN ; i++) {
    for (int j = 0 ; j < HEIGHT_OF_SCREEN ; j++) {
      wiresXY[i][j] = 0;
    }
  }
}



void loop() {
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  the1DPart();
  // the2DPart();
  paint_current_wire(wiresXY);
  delay(100);
}



int highestValue[NUM_INPUTS];
int lowestValue[NUM_INPUTS];
void the1DPart(){
  for(uint8_t i = 0 ; i < NUM_INPUTS; i++){

    if (highestValue[i] < cap.filteredData(i)) {
      highestValue[i] = cap.filteredData(i);
    }

    float mappedData = map(cap.filteredData(i), highestValue[i], 0, 0, 1000);
    mappedData = max(mappedData, 0);
    mappedData = min(mappedData, 255);

    for (int x = 0; x <WIDTH_OF_SCREEN ; x++){
      wiresXY[x][i] = mappedData;
    }//for
  }//for
}//the1DPart



int highestValue0;
int highestValue1;
int highestValue2;
int highestValue3;

int highestValue4;
int highestValue5;
int highestValue6;
int highestValue7;

void the2DPart(){

  float level;
  float lum;

  // ---------
  if(highestValue0 < cap.filteredData(0)){
    highestValue0 = cap.filteredData(0);
  }
  if(highestValue1 < cap.filteredData(1)){
    highestValue1 = cap.filteredData(1);
  }
  if(highestValue2 < cap.filteredData(2)){
    highestValue2 = cap.filteredData(2);
  }
  if(highestValue3 < cap.filteredData(3)){
    highestValue3 = cap.filteredData(3);
  }

  //---------------------
  if(highestValue4 < cap.filteredData(4)){
    highestValue4 = cap.filteredData(4);
  }
  if(highestValue5 < cap.filteredData(5)){
    highestValue5 = cap.filteredData(5);
  }
  if(highestValue6 < cap.filteredData(6)){
    highestValue6 = cap.filteredData(6);
  }
  if(highestValue7 < cap.filteredData(7)){
    highestValue7 = cap.filteredData(7);
  }
  //--------------------


  float mappedData0 = map(cap.filteredData(0), highestValue0, 0, 0, 1000);
  mappedData0 = max(mappedData0, 0);
  mappedData0 = min(mappedData0, 255);

  float mappedData1 = map(cap.filteredData(1), highestValue1, 0, 0, 1000);
  mappedData1 = max(mappedData1, 0);
  mappedData1 = min(mappedData1, 255);

  float mappedData2 = map(cap.filteredData(2), highestValue2, 0, 0, 1000);
  mappedData2 = max(mappedData2, 0);
  mappedData2 = min(mappedData2, 255);

  float mappedData3 = map(cap.filteredData(3), highestValue3, 0, 0, 1000);
  mappedData3 = max(mappedData3, 0);
  mappedData3 = min(mappedData3, 255);

  //-------------------------------


  float mappedData4 = map(cap.filteredData(4), highestValue4, 0, 0, 1000);
  mappedData4 = max(mappedData4, 0);
  mappedData4 = min(mappedData4, 255);

  float mappedData5 = map(cap.filteredData(5), highestValue5, 0, 0, 1000);
  mappedData5 = max(mappedData5, 0);
  mappedData5 = min(mappedData5, 255);

  float mappedData6 = map(cap.filteredData(6), highestValue6, 0, 0, 1000);
  mappedData6 = max(mappedData6, 0);
  mappedData6 = min(mappedData6, 255);

  float mappedData7 = map(cap.filteredData(7), highestValue7, 0, 0, 1000);
  mappedData7 = max(mappedData7, 0);
  mappedData7 = min(mappedData7, 255);

  //----------------------------------


  // 0,4
  level = mappedData0 + mappedData4;
  wiresXY[4-4][0] = level;
  // 0,5
  level = mappedData0 + mappedData5;
  wiresXY[5-4][0] = level;
  // 0,6
  level = mappedData0 + mappedData6;
  wiresXY[6-4][0] = level;
  // 0,7
  level = mappedData0 + mappedData7;
  wiresXY[7-4][0] = level;



  // 1,4
  level = mappedData1 + mappedData4;
  wiresXY[4-4][1] = level;
  // 1,5
  level = mappedData1 + mappedData5;
  wiresXY[5-4][1] = level;
  // 1,6
  level = mappedData1 + mappedData6;
  wiresXY[6-4][1] = level;
  // 1,7
  level = mappedData1 + mappedData7;
  wiresXY[7-4][1] = level;


  // 2,4
  level = mappedData2 + mappedData4;
  wiresXY[4-4][2] = level;
  // 2,5
  level = mappedData2 + mappedData5;
  wiresXY[5-4][2] = level;
  // 2,6
  level = mappedData2 + mappedData6;
  wiresXY[6-4][2] = level;
  // 2,7
  level = mappedData2 + mappedData7;
  wiresXY[7-4][2] = level;


  // 3,4
  level = mappedData3 + mappedData4;
  wiresXY[4-4][3] = level;
  // 3,5
  level = mappedData3 + mappedData5;
  wiresXY[5-4][3] = level;
  // 3,6
  level = mappedData3 + mappedData6;
  wiresXY[6-4][3] = level;
  // 3,7
  level = mappedData3 + mappedData7;
  wiresXY[7-4][3] = level;

}//the2DPart





void paint_one_color(CRGB col) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = col;
  }
  FastLED.show();
}


void paint_testpattern() {
  for(int i =0 ; i < 1; i++){
    paint_one_color(CRGB::Red);
    FastLED.show();
    delay(100);
    paint_one_color(CRGB::Green);
    FastLED.show();
    delay(100);
    paint_one_color(CRGB::Blue);
    FastLED.show();
    delay(100);
    paint_one_color(CRGB::White);
    FastLED.show();
    delay(100);
    paint_one_color(CRGB::Black);
    FastLED.show();
  }
}



int calcSeqNumber(int _x, int _y) {
  int ans = 0;
  if (_y % 2 == 0) {
    ans = (WIDTH_OF_SCREEN * _y) + _x;
  } else if (_y % 2 != 0) {
    ans = (WIDTH_OF_SCREEN - 1 - _x) + _y * WIDTH_OF_SCREEN;
  }
  return ans;
}


void paint_current_wire(int wiresXY[WIDTH_OF_SCREEN][HEIGHT_OF_SCREEN]) {

  float level;
  int lum;
  for ( int x = 0 ; x < WIDTH_OF_SCREEN ; x++) {
    for (int y = 0; y < HEIGHT_OF_SCREEN; y++) {
      level = wiresXY[x][y];


      if(level > 40){
        leds[calcSeqNumber(x, y)] = CRGB(level, level, level);
      }else{
        leds[calcSeqNumber(x, y)] = CRGB(0, 0, 0);
      }
    }
  }

  FastLED.show();

}
