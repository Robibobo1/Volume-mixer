#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define PIXEL_PIN    12
#define PIXEL_COUNT  5

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);


int brightnessValue[5];
const int analogInputs[5] = {A0, A1, A2, A3, A4};
const int digitalInputs[5] = {3, 4, 5, 6, 7};
int analogSliderValues[5];
bool digitalValue[5] = {1,1,1,1,1};
bool digitalState[5];

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin


void setup() {
  strip.begin();
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(analogInputs[i], INPUT);
    pinMode(digitalInputs[i], INPUT_PULLUP);
  }
}

void loop() {


  for (int i = 0; i < 5; i++)
  {
    if (digitalValue[i] == 1)
    {
      analogSliderValues[i] = analogRead(analogInputs[i]);
      brightnessValue[i] = analogSliderValues[i] / 4.7  ;
    }
    if (digitalValue[i] == 0)
    {
      analogSliderValues[i] = 1024;
      brightnessValue[i] = 255  ;
    }
  }

  strip.setPixelColor(0, 0, 255 - brightnessValue[0], 0);
  strip.setPixelColor(1, 255 - brightnessValue[1], 100 - (brightnessValue[1] / 2.55), 0);
  strip.setPixelColor(2 , 0, 0, 255 - brightnessValue[2]);
  strip.setPixelColor(3 , 100 - (brightnessValue[3] / 2.55), 0, 255 - brightnessValue[3]);
  strip.setPixelColor(4 , 255 - brightnessValue[4], 0, 0);
  strip.show();

  sendSliderValues();
  delay(10);
  
  for (int i = 0; i < 5; i++)
  {
    strip.show();
    digitalState[i] = digitalRead(digitalInputs[i]);
    if(digitalState[i] == 0)
    {
      delay(50);
      strip.show();
      if(digitalRead(digitalInputs[i]) == 0)
      {
        digitalValue[i] =! digitalValue[i];
        while(digitalRead(digitalInputs[i]) == 0)
        {
          sendSliderValues();
          strip.show();
          delay(10);
        }
      }
    }
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < 5; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < 5 - 1) {
      builtString += String("|");
    }
  }

  Serial.println(builtString);
}
