int buttonpin = 13;//pin 13 on the arduino

bool buttonpressed = false;
bool buttonready = true;

void setup() {
  Serial.begin(9600);//initalize Serial Monitor 
  pinMode(buttonpin, INPUT_PULLUP);//setup the button pin
}

void loop() {
  buttonpressed = digitalRead(buttonpin);//read the state of the button *reads as 0 and 1, 1 = NOT pressed, 0 = pressed*

  if (buttonpressed == 0 && buttonready == true) {//checks if the button is pressed and if it is ready to be pressed
    Serial.println("ButtonPressed");
    buttonready = false;//changes the button ready boolean to false to stop it from thinking the button is being pressed multiple times
  }
  if(buttonpressed == 1){//if the button is not pressed
    buttonready = true;//make the button ready to be pressed again
    Serial.println("Button NOT pressed");
  }
}
