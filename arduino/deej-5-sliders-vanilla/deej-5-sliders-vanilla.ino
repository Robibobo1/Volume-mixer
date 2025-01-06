#include <Adafruit_NeoPixel.h>

#define LED_PIN    12
#define LED_COUNT 5

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#define NUM_SLIDERS 5
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4};
const uint32_t sliderColors[NUM_SLIDERS] = 
{
  strip.Color(0x10, 0xF0, 0x20),
  strip.Color(0xFC, 0x14, 0x12),
  strip.Color(0x7F, 0x00, 0xFF),
  strip.Color(0x00, 0x00, 0xFF),
  strip.Color(0xFF, 0xBF, 0x00)
};


int analogSliderValues[NUM_SLIDERS];

void setup() { 
  strip.begin();
  strip.setBrightness(255);
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
    strip.setPixelColor(i,sliderColors[i]);
  }
  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  strip.show();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}