#include <EEPROM.h> // bringing in eeprom library
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

//const unsigned long day = 10000; // 10 second test, 86400000 when ready
//unsigned long mytime = millis();// getting time for day condition below
const int ADDRESS_EEPROM = 1;
int value;
const int DOOR_SENSOR_PIN_2 = 2;
const int DOOR_SENSOR_PIN_3 = 3;
const int DOOR_SENSOR_PIN_4 = 4;
const int DOOR_SENSOR_PIN_5 = 5;
const int DOOR_SENSOR_PIN_6 = 6;
const int DOOR_SENSOR_PIN_7 = 7;
const int DOOR_SENSOR_PIN_8 = 8;
const int DOOR_SENSOR_PIN_9 = 9;
const int DOOR_SENSOR_PIN_10 = 10;
const int DOOR_SENSOR_PIN_11 = 11;

int counter = 0;
int doorState2 = LOW;
int doorState3 = LOW;
int doorState4 = LOW;
int doorState5 = LOW;
int doorState6 = LOW;
int doorState7 = LOW;
int doorState8 = LOW;
int doorState9 = LOW;
int doorState10 = LOW;
int doorState11 = LOW;
int prevDoorState2 = LOW;
int prevDoorState3 = LOW;
int prevDoorState4 = LOW;
int prevDoorState5 = LOW;
int prevDoorState6 = LOW;
int prevDoorState7 = LOW;
int prevDoorState8 = LOW;
int prevDoorState9 = LOW;
int prevDoorState10 = LOW;
int prevDoorState11 = LOW;


void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    exit(0);
  }
  display.display();
  delay(2000);

  Serial.begin(9600);
  pinMode(DOOR_SENSOR_PIN_2, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_3, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_4, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_5, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_6, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_7, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_8, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_9, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_10, INPUT_PULLUP);
  pinMode(DOOR_SENSOR_PIN_11, INPUT_PULLUP);
  doorState2 = digitalRead(DOOR_SENSOR_PIN_2);
  doorState3 = digitalRead(DOOR_SENSOR_PIN_3);
  doorState4 = digitalRead(DOOR_SENSOR_PIN_4);
  doorState5 = digitalRead(DOOR_SENSOR_PIN_5);
  doorState6 = digitalRead(DOOR_SENSOR_PIN_6);
  doorState7 = digitalRead(DOOR_SENSOR_PIN_7);
  doorState8 = digitalRead(DOOR_SENSOR_PIN_8);
  doorState9 = digitalRead(DOOR_SENSOR_PIN_9);
  doorState10 = digitalRead(DOOR_SENSOR_PIN_10);
  doorState11 = digitalRead(DOOR_SENSOR_PIN_11);

  counter = EEPROM.read(ADDRESS_EEPROM);  
}

void loop() {
  //  doorState7 = digitalRead(DOOR_SENSOR_PIN_7);
  //  doorState8 = digitalRead(DOOR_SENSOR_PIN_8);
  doorOpened(prevDoorState2, doorState2, DOOR_SENSOR_PIN_2, 2);
  doorOpened(prevDoorState3, doorState3, DOOR_SENSOR_PIN_3, 3);
  doorOpened(prevDoorState4, doorState4, DOOR_SENSOR_PIN_4, 4);
  doorOpened(prevDoorState5, doorState5, DOOR_SENSOR_PIN_5, 5);
  doorOpened(prevDoorState6, doorState6, DOOR_SENSOR_PIN_6, 6);
  doorOpened(prevDoorState7, doorState7, DOOR_SENSOR_PIN_7, 7);
  doorOpened(prevDoorState8, doorState8, DOOR_SENSOR_PIN_8, 8);
  doorOpened(prevDoorState9, doorState9, DOOR_SENSOR_PIN_9, 9);
  doorOpened(prevDoorState10, doorState10, DOOR_SENSOR_PIN_10, 10);
  doorOpened(prevDoorState11, doorState11, DOOR_SENSOR_PIN_11, 11);

  display.clearDisplay();               // Clear buffer
  //  delay(2000);                          // Delay by ms where 1000 ms = 1 second
  delay(1);
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.cp437(true);                  // Use full 256 char 'Code Page 437' font
  display.println(F("Door Opened Count"));    // Text to be shown and added to display buffer

  display.println("Count: " + String(counter));

  display.display();
  delay(1);
  //  delay(1000);

  

}
// 86400000 is a day
void doorOpened(int &prevDoorState, int &currentDoorState, int doorSensorPin, int pin) {
  prevDoorState = currentDoorState;
  currentDoorState = digitalRead(doorSensorPin);
  if (prevDoorState == LOW && currentDoorState == HIGH) {
    Serial.println("Door is opened: " + String(pin));
    counter += 1;
    EEPROM.write(ADDRESS_EEPROM, counter);
    value = EEPROM.read(ADDRESS_EEPROM);
    Serial.print(ADDRESS_EEPROM);
    Serial.print("\t");
    Serial.print(value);
    Serial.println();
    //if (mytime % day == 0) { //testing with 10 seconds - ideally counter value gets recorded every 10 seconds
      //for (int i = 0 ; i < 3; i++) { //i++ instead of i + 1, i < 90 for less than 90 days?
  }
}
