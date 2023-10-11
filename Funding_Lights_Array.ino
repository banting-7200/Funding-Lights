#include <Adafruit_NeoPixel.h>

#define LED_PIN 6    // Define the pin for your LED matrix
#define NUM_LEDS 48/*248*/  // Define the number of LEDs in your matrix

int fundingGoal = 24000; // The total ammount of money we wish to raise
int sponsorMoney = 1000, studentMoney = 1000, msicMoney = 1000; /* the amount of money currently contributed by sponsors, students and other sources. 
                                                       Change the coressponding variable to change the ammount displayed on the light strip.*/
  int dollarsPerLED = fundingGoal / NUM_LEDS;// Calculate the ammount of money each LED represents


int buttonPin = 1; // The pin for the button which updates the lights

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int DOT_COUNT = 50;  // Number of dots

int dotPosition[50][2];  // Array to store dot positions
float dotSpeed = 5;

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'

  for (int i = 0; i < DOT_COUNT; i++) {
    //dotPosition[i][0] = NUM_LEDS - 1;  // Start each dot on the right
    //dotPosition[i][1] = ;
  }
  
  int funds[] = {round(sponsorMoney / dollarsPerLED), round(studentMoney / dollarsPerLED), round(msicMoney / dollarsPerLED)};

  DisplayLEDs(funds);
}

void loop() {
  /* Clear the entire strip
  strip.clear();

  for (int i = 0; i < DOT_COUNT; i++) {
    // Update dot position
    dotPosition[i] -= dotSpeed[i];

    // Ensure the dot stays within the bounds
 

    // Draw the dot at its position
    strip.setPixelColor(int(dotPosition[i]), strip.Color(255, 0, 0));  // Red dot
    Serial.println(dotSpeed[i]);
  }

  strip.show();
  delay(50);  // Adjust the speed by changing the delay time*/
}

void DisplayLEDs(int funds[])
{
        int r = 50, g = 0, b = 0;
        for(int j = 0; j < funds[0] + funds[1] + funds[2]; j++)
        {
          if(j == funds[0])
          {
             r = 0; g = 50; b = 0;
          }
          else if(j == funds[0] + funds[1])
          {
             r = 0; g = 0; b = 50;
          }
           strip.setPixelColor(j, strip.Color(r, g, b));  // display the light
           strip.show();
        }      
}
