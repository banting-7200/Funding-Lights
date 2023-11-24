#include "U8glib.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 11           // Define the pin for your LED matrix
#define NUM_LEDS 50 /*248*/  // Define the number of LEDs in your matrix

// Declairing the NeoPixel Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Money Variables
int fundingGoal = 24000;                                         // The total ammount of money we wish to raise
int sponsorMoney = 10000, studentMoney = 9000, miscMoney = 5000; /* the amount of money currently contributed by sponsors, students and other sources. 
                                                       Change the coressponding variable to change the ammount displayed on the light strip.*/
int dollarsPerLED = fundingGoal / NUM_LEDS;                      // Calculate the ammount of money each LED represents

int animSpeed = 100;  // A variable to easily change the speed of the animation

// Button variables
int buttonPin = 13;  // The pin for the button which updates the lights
bool buttonpressed = false;
bool buttonready = true;

// potentiometer variables
int potPin = A0;
int potVal = 0;
int incPin = 2;  //increment button pin

// Timer and state change variables
int state = 0;

unsigned long currentMillis = 0;
unsigned long startMillis = 0;
const unsigned long period = 3000;  // the amount of time the button needs to be held down

int increment_values[] = { 100, 50, 25 };
int count = 0;  //element in increment values array
bool buttonPress1 = false;
bool runTimer = false;


U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);
int progress = 0;
// '7200Bitmap', 128x64px
// '7200 Lighting Panel', 128x64px
const unsigned char epd_bitmap_7200_Lighting_Panel[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
  0x40, 0x00, 0x0f, 0x8e, 0x1c, 0x38, 0x03, 0xc3, 0x8f, 0x00, 0x78, 0x00, 0x00, 0x04, 0x00, 0x04,
  0x70, 0x00, 0x00, 0x91, 0x22, 0x44, 0x02, 0x24, 0x48, 0x80, 0x44, 0x00, 0x00, 0x04, 0x00, 0x0c,
  0x00, 0x00, 0x01, 0x01, 0x22, 0x44, 0x02, 0x24, 0x08, 0x80, 0x44, 0xf1, 0xe1, 0xc4, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x0e, 0x22, 0x44, 0x03, 0xc4, 0xcf, 0x00, 0x78, 0x09, 0x12, 0x24, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x10, 0x22, 0x44, 0x02, 0x84, 0x48, 0x80, 0x40, 0x79, 0x13, 0xc4, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x10, 0x22, 0x44, 0x02, 0x44, 0x48, 0x80, 0x40, 0x89, 0x12, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x1f, 0x1c, 0x38, 0x02, 0x23, 0xcf, 0x00, 0x40, 0x71, 0x11, 0xe4, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x41, 0x00, 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x18,
  0x00, 0x00, 0x63, 0x00, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x55, 0x1c, 0x3c, 0x70, 0x00, 0x01, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x49, 0x22, 0x44, 0x88, 0x00, 0x01, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x49, 0x22, 0x44, 0xf0, 0x00, 0x01, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x49, 0x22, 0x44, 0x80, 0x00, 0x01, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x49, 0x1c, 0x3c, 0x78, 0x00, 0x01, 0x44, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x4b, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x48, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x44, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x27, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x27, 0x90, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x13, 0x20, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x09, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0e, 0x40, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x09, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0e, 0x40, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x72, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x64, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x72, 0x02, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1040)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {
  epd_bitmap_7200_Lighting_Panel
};



int xmax = 128;
int ymax = 62;
int xcenter = xmax / 2;
int ycenter = ymax / 2 + 10;

void setup() {
  Serial.begin(9600);
  u8g.setColorIndex(1);
  strip.begin();  // Start the strip
  strip.show();   // Initialize all pixels to 'off'


  pinMode(buttonPin, INPUT_PULLUP);  //setup the button pin
  pinMode(potPin, INPUT);
  pinMode(incPin, INPUT);
}

void loop() {
  u8g.firstPage();
  do {


    currentMillis = millis();
    buttonpressed = digitalRead(buttonPin);  //read the state of the button *reads as 0 and 1, 1 = NOT pressed, 0 = pressed*
    potVal = analogRead(potPin);

    //potVal = map(potVal, 1023, 0, fundingGoal, 0);
    //Serial.println(potVal);
    //Serial.println(state);

    if (digitalRead(incPin) == true && buttonPress1 == false) {  //read 2 pin button, if clicked change increment value element (changes val (100, 50, 25))
      buttonPress1 = true;
      count++;
      if (count >= sizeof(increment_values) / sizeof(increment_values[0])) {
        count = 0;
      }
    }
    if (digitalRead(incPin) == false) {
      buttonPress1 = false;
    }

    int mapped_val = (map(potVal, 0, 1023, fundingGoal, 0) / increment_values[count]) * increment_values[count];  //div initial number by x then * x for inc value

    u8g.drawBitmapP(0, 0, 128 / 8, 64, epd_bitmap_7200_Lighting_Panel);
    u8g.drawLine(61, 13, 61, 14);
    u8g.setPrintPos(80, 30);
    u8g.setFont(u8g_font_profont12);
    u8g.println(mapped_val);
    u8g.setPrintPos(80, 50);
    u8g.setFont(u8g_font_profont12);
    u8g.println(increment_values[count]);

    if (buttonpressed == 0 && buttonready == true) {  //checks if the button is pressed and if it is ready to be pressed
      //Serial.println("ButtonPressed");
      switch (state) {
        case 0:
          sponsorMoney = mapped_val;  //changed potval to mapped
          Serial.println(sponsorMoney);
          u8g.setPrintPos(10, 30);
          u8g.println("sponsorMoney");
          state++;
          break;

        case 1:
          studentMoney = mapped_val;  //changed potval to mapped
          Serial.println(studentMoney);
          u8g.setPrintPos(10, 30);
          u8g.println("studentMoney");

          state++;
          break;

        case 2:
          miscMoney = mapped_val;  //changed potval to mapped
          Serial.println(miscMoney);
          u8g.setPrintPos(10, 30);
          u8g.println("miscMoney");

          state++;
          break;

        case 4:  // case 4 above case 3 because if it was below the array delcaritor would freak out and die.
          runTimer = true;
          startMillis = currentMillis;
          break;

        case 3:
          /*
    This array will be fed into the animation function.
    It is poulated with the ammount of LEDs to turn on for each segement
    which is calculated by dividing the ammount of money raised for that 
    segment by how much money a single LED represents.
    */
          int funds[] = { round(sponsorMoney / dollarsPerLED), round(studentMoney / dollarsPerLED), round(miscMoney / dollarsPerLED) };

          LightandAnim(funds, animSpeed);  // Play the animation
          state++;
          break;
      }
      buttonready = false;  //changes the button ready boolean to false to stop it from thinking the button is being pressed multiple times
    }
    if (buttonpressed == 1) {  //if the button is not pressed
      buttonready = true;      //make the button ready to be pressed again
                               //Serial.println("Button NOT pressed");
      runTimer = false;
      if (state == 4)
        startMillis = currentMillis;
    }

    if (runTimer == true) {
      Serial.println(currentMillis - startMillis);
      if (currentMillis - startMillis >= period) {
        state = 0;
        strip.clear();
        strip.show();

        runTimer = false;
      }
    }
  } while (u8g.nextPage());
}



void LightandAnim(int funds[], int animSpeed) {
  /* 
  This is the rgb colour values for each of the
  meter segements. 
  Each variable contains the respective
  value for r, g, and b for each pass through the loop
  */
  int r[] = { 50, 0, 0 };
  int g[] = { 0, 50, 0 };
  int b[] = { 0, 0, 50 };
  // this value stores the offset that will be applied for each
  // segement so the newest segment does not overwrite the last.
  int offset = 0;
  for (int i = 0; i < 3; i++)  // This loop goes through all three entries in the funds array so each coressponding segment has its own little animation
  {
    for (int t = 5; t >= 0; t--)  // this loop contols how far the animation travels. t is passed into a pow function which raises 2 to the power of t and that is added to the psoition the light needs to be at. So as the loop decreases the light gets closer to its intened position.
    {
      for (int j = -1; j < funds[i] - 1; j++)  // j starts at -1 to account for the fact that 1 will always be added to j through the pow function. Might change it later but too lazy to rn tbh.
      {
        strip.setPixelColor(j + offset + pow(2, t), strip.Color(r[i], g[i], b[i]));  // display the light
      }
      strip.show();                            // Display the lights that were just set.
      delay(animSpeed);                        // This is the delay time between "frames" of the animation. Change it to change the animations speed. might make into a variable later for easy acsess
      for (int j = -1; j < funds[i] - 1; j++)  // sets the position
      {
        if (j + pow(2, t) != j + 1)  // Deactivates the lights that were just turned on so they don't stick around in the next frame of the animation, but only if they are not the lights final position.
          strip.setPixelColor(j + offset + pow(2, t), strip.Color(0, 0, 0));
      }
    }
    offset += funds[i];  // add the ammount of lights that were just animated to the offset so they are not overwritten when the next segment is animated.
  }
  Serial.println("DONE!");  // Debug stuff to see when animation has finished
}

// Just displays the leds with no animation. probly won't be used now
void DisplayLEDs(int funds[]) {
  int r = 50, g = 0, b = 0;
  for (int j = 0; j < funds[0] + funds[1] + funds[2]; j++) {
    if (j == funds[0]) {
      r = 0;
      g = 50;
      b = 0;
    } else if (j == funds[0] + funds[1]) {
      r = 0;
      g = 0;
      b = 50;
    }
    strip.setPixelColor(j, strip.Color(r, g, b));  // display the light
    strip.show();
  }
}