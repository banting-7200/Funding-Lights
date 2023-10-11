#include <Adafruit_NeoPixel.h>
#define LED_PIN 6    // Define the pin for your LED matrix
#define NUM_LEDS 48  // Define the number of LEDs in your matrix

int fundingGoal = 20000;                                       // The total ammount of money we wish to raise
int sponsorMoney = 5000, studentMoney = 100, miscMoney = 1000; /* the amount of money currently contributed by sponsors, students and other sources. 
                                                       Change the coressponding variable to change the ammount displayed on the light strip.*/
// The pin the light string is attached to on the arduino

int dollarsPerLED = fundingGoal / NUM_LEDS;

int sponsorMoneyLEDStoDisplay = round(sponsorMoney / dollarsPerLED);
int studentMoneyLEDStoDisplay = round(studentMoney / dollarsPerLED);
int miscMoneyLEDStoDisplay = round(miscMoney / dollarsPerLED);


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define DOT_COUNT 5  // Number of dots

int dotPosition[DOT_COUNT];  // Array to store dot positions
float dotSpeed[DOT_COUNT];   // Array to store dot speeds

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'

  for (int i = 0; i < sponsorMoneyLEDStoDisplay; i++) {
    strip.setPixelColor(i, 50, 0, 0);
    strip.show();
  }
  for (int i = sponsorMoneyLEDStoDisplay; i < (sponsorMoneyLEDStoDisplay + studentMoneyLEDStoDisplay); i++) {
    strip.setPixelColor(i, 0, 50, 0);
    strip.show();
  }
  for (int i = sponsorMoneyLEDStoDisplay + studentMoneyLEDStoDisplay; i < (sponsorMoneyLEDStoDisplay + studentMoneyLEDStoDisplay + miscMoneyLEDStoDisplay); i++) {
    strip.setPixelColor(i, 0, 0, 50);
    strip.show();
  }


}

void loop(){

}
