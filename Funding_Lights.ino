
  #include <Adafruit_NeoPixel.h>

#define LED_PIN 6    // Define the pin for your LED matrix
#define NUM_LEDS 48/*248*/  // Define the number of LEDs in your matrix

// Declairing the NeoPixel Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Money Variables
int fundingGoal = 24000; // The total ammount of money we wish to raise
int sponsorMoney = 10000, studentMoney = 12000, msicMoney = 4000; /* the amount of money currently contributed by sponsors, students and other sources. 
                                                       Change the coressponding variable to change the ammount displayed on the light strip.*/
int dollarsPerLED = fundingGoal / NUM_LEDS;// Calculate the ammount of money each LED represents

int animSpeed = 100; // A variable to easily change the speed of the animation

// Button variables
int buttonPin = 13; // The pin for the button which updates the lights
bool buttonpressed = false;
bool buttonready = true;

// potentiometer variables
int potPin = A0;
int potVal = 0;

// Timer and state change variables
int state = 0;

unsigned long currentMillis = 0;
unsigned long startMillis = 0;
const unsigned long period = 3000;// the amount of time the button needs to be held down

void setup() {
  Serial.begin(9600);
  strip.begin();// Start the strip
  strip.show();  // Initialize all pixels to 'off'
  
  pinMode(buttonPin, INPUT_PULLUP);//setup the button pin
  pinMode(potPin, INPUT);
}

void loop() 
{
   currentMillis = millis();
   buttonpressed = digitalRead(buttonPin);//read the state of the button *reads as 0 and 1, 1 = NOT pressed, 0 = pressed*
   potVal = analogRead(potPin);

   int mapped_val = (map(potVal, 0, 1023, fundingGoal, 0) / 100) * 100; // switch potVal to values of 100 
   //potVal = map(potVal, 1023, 0, fundingGoal, 0);
   //Serial.println(potVal);
   //Serial.println(state);
  
  if (buttonpressed == 0 && buttonready == true) {//checks if the button is pressed and if it is ready to be pressed
    //Serial.println("ButtonPressed");
    switch(state){
      case 0:
      sponsorMoney = mapped_val; //changed potval to mapped 
      //Serial.println(sponsorMoney);
      state++;
      break;
      
       case 1:
       studentMoney = mapped_val;//changed potval to mapped 
     // Serial.println(studentMoney);
       state++;
      break;
     
       case 2:
       msicMoney = mapped_val;//changed potval to mapped 
      //Serial.println(msicMoney);
       state++;
      break;

      case 4:// case 4 above case 3 because if it was below the array delcaritor would freak out and die.
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
    int funds[] = {round(sponsorMoney / dollarsPerLED), round(studentMoney / dollarsPerLED), round(msicMoney / dollarsPerLED)};

    LightandAnim(funds, animSpeed);// Play the animation
    state++;
      break;  
    }
    buttonready = false;//changes the button ready boolean to false to stop it from thinking the button is being pressed multiple times
  }
  if(buttonpressed == 1){//if the button is not pressed
    buttonready = true;//make the button ready to be pressed again
    //Serial.println("Button NOT pressed");
     runTimer = false;
    if(state == 4)
      startMillis = currentMillis;
    
  }
  
  if(runTimer){
     Serial.println(currentMillis - startMillis);
      if(currentMillis - startMillis >= period)
      {
        state = 0;
        strip.clear();
        strip.show();
        
        resetTimer = 0;
        runTimer = false;
      }
  }
}

void LightandAnim(int funds[], int animSpeed)
{
  /* 
  This is the rgb colour values for each of the
  meter segements. 
  Each variable contains the respective
  value for r, g, and b for each pass through the loop
  */
  int r[] = {50, 0, 0};
  int g[] = {0, 50, 0};
  int b[] = {0, 0, 50};
  // this value stores the offset that will be applied for each
  // segement so the newest segment does not overwrite the last.
  int offset = 0;
  for(int i = 0; i < 3; i++)// This loop goes through all three entries in the funds array so each coressponding segment has its own little animation
  {
    for(int t = 5; t >= 0; t--)// this loop contols how far the animation travels. t is passed into a pow function which raises 2 to the power of t and that is added to the psoition the light needs to be at. So as the loop decreases the light gets closer to its intened position.
    {
      for(int j = -1; j < funds[i] - 1; j++)// j starts at -1 to account for the fact that 1 will always be added to j through the pow function. Might change it later but too lazy to rn tbh.
      {
        strip.setPixelColor(j  + offset + pow(2, t), strip.Color(r[i], g[i], b[i]));  // display the light            
      }
      strip.show();// Display the lights that were just set.
      delay(animSpeed);// This is the delay time between "frames" of the animation. Change it to change the animations speed. might make into a variable later for easy acsess
      for(int j = -1; j < funds[i] - 1; j++)// sets the position 
      {        
        if(j + pow(2, t) != j + 1)// Deactivates the lights that were just turned on so they don't stick around in the next frame of the animation, but only if they are not the lights final position.
        strip.setPixelColor(j + offset + pow(2, t), strip.Color(0, 0, 0));
      }
    }
    offset += funds[i];// add the ammount of lights that were just animated to the offset so they are not overwritten when the next segment is animated.
  }
  Serial.println("DONE!");// Debug stuff to see when animation has finished
}

// Just displays the leds with no animation. probly won't be used now
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
