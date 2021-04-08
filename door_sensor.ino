#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int DOOR_SENSOR_PIN_7 = 7;
const int DOOR_SENSOR_PIN_8 = 8;

int counter = 0;
int doorState7 = LOW;
int doorState8 = LOW;
int prevDoorState7 = LOW;
int prevDoorState8 = LOW;


void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.println(F("SSD1306 allocation failed"));
    exit(0);
  }
  display.display();
  delay(2000);

  Serial.begin(9600);
  pinMode(DOOR_SENSOR_PIN_7, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_8, INPUT_PULLUP);
  doorState7 = digitalRead(DOOR_SENSOR_PIN_7);
  doorState8 = digitalRead(DOOR_SENSOR_PIN_8);
  
}

void loop() {
//  doorState7 = digitalRead(DOOR_SENSOR_PIN_7);
//  doorState8 = digitalRead(DOOR_SENSOR_PIN_8);
  doorOpened(prevDoorState7, doorState7, DOOR_SENSOR_PIN_7, 7);
  doorOpened(prevDoorState8, doorState8, DOOR_SENSOR_PIN_8, 8);

  display.clearDisplay();               // Clear buffer
//  delay(2000);                          // Delay by ms where 1000 ms = 1 second
  delay(1);
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0,0);               // Start at top-left corner
  display.cp437(true);                  // Use full 256 char 'Code Page 437' font
  display.println(F("Door Opened Count"));    // Text to be shown and added to display buffer
  
  display.println("Count: " + String(counter));

  display.display();
  delay(1);
//  delay(1000);
  
}

void doorOpened(int &prevDoorState, int &currentDoorState, int doorSensorPin, int pin) {
  prevDoorState = currentDoorState;
  currentDoorState = digitalRead(doorSensorPin);
  if (prevDoorState == LOW && currentDoorState == HIGH) {
    Serial.println("Door is opened: " + String(pin));
    counter += 1;
  }
}
