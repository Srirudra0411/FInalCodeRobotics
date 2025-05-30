#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int micPin = A0; // KY-038 analog output to A0
const int piezoPin = 9; // Piezo buzzer to D9
const int threshold = 36;
const unsigned long buzzerOnDuration = 1000; // 1 second in milliseconds
LiquidCrystal_I2C lcd(0x3F, 16, 2); // LCD address 0x3F, 16 columns, 2 rows
unsigned long buzzerTriggeredAt = 0;
bool buzzerActive = false;
void setup() {
pinMode(micPin, INPUT);
pinMode(piezoPin, OUTPUT);
Serial.begin(9600);
lcd.init();
lcd.backlight();
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Mic Value:");
}
void loop() {
int micValue = analogRead(micPin);
// Serial.println(micValue); // This line is now commented out
// Display the mic value on the LCD (ensure previous value is fully erased)
lcd.setCursor(0, 1);
lcd.print(" "); // Clear the entire second line (16 spaces)
lcd.setCursor(0, 1);
lcd.print(micValue);
// Spike detection and buzzer logic
unsigned long now = millis();
if (!buzzerActive && micValue > threshold) {
// Spike detected, turn on buzzer
digitalWrite(piezoPin, HIGH);
buzzerActive = true;
buzzerTriggeredAt = now;
}
// Keep buzzer on for 1 second after spike
if (buzzerActive && (now - buzzerTriggeredAt >= buzzerOnDuration)) {
digitalWrite(piezoPin, LOW);
buzzerActive = false;
}
delay(50);
}
