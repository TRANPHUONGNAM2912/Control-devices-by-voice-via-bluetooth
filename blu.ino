#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // Chân D4 là TX, chân D5 là RX

LiquidCrystal_I2C lcd(0x27, 16, 2);
String voice;
int count = 0;
int ledPin1 = 12;
int ledPin2 = 11;
int fanPin = 10;
int pumPin = 7;
bool led1Status = false;
bool led2Status = false;
bool fanStatus = false;
bool pumStatus = false;

void setup() {
Serial.begin(9600);  // Bật cổng Serial mặc định cho mục đích debug
  mySerial.begin(38400); // Bật cổng Serial mới trên chân D4 và D5
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(pumPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  updateLCD(); 
}

void updateLCD() {
  lcd.setCursor(0,0); 
  lcd.print("LED1:");
  lcd.setCursor(5, 0); 
  lcd.print(led1Status ? "ON " : "OFF");
  lcd.setCursor(8,0); 
  lcd.print("LED2:");
  lcd.setCursor(13, 0); 
  lcd.print(led2Status ? "ON " : "OFF");
  lcd.setCursor(0,1); 
  lcd.print("QUAT:");
  lcd.setCursor(5, 1); 
  lcd.print(fanStatus ? "ON " : "OFF");
  lcd.setCursor(9,1); 
  lcd.print("BOM:");
  lcd.setCursor(13, 1); 
  lcd.print(pumStatus ? "ON " : "OFF");
}

void loop() {
  if (mySerial.available() > 0) {
    voice = mySerial.readString();
    voice.toLowerCase();
    Serial.println(voice);

    if (voice.indexOf("bật đèn 1") != -1||voice.indexOf("bật đèn một") != -1) {
      digitalWrite(ledPin1, HIGH);
      led1Status = true;
    } if (voice.indexOf("tắt Đèn 1") != -1||voice.indexOf("tắt Đèn một") != -1) {
      digitalWrite(ledPin1, LOW);
      led1Status = false;
    } if (voice.indexOf("bật đèn 2") != -1||voice.indexOf("bật đèn hai") != -1) {
      digitalWrite(ledPin2, HIGH);
      led2Status = true;
    } if (voice.indexOf("tắt đèn 2") != -1||voice.indexOf("tắt đèn hai") != -1) {
      digitalWrite(ledPin2, LOW);
      led2Status = false;
    } if (voice.indexOf("bật quạt") != -1) {
      digitalWrite(fanPin, HIGH);
      fanStatus = true;
    } if (voice.indexOf("tắt quạt") != -1) {
      digitalWrite(fanPin, LOW);
      fanStatus = false;
    } if (voice.indexOf("bật bơm") != -1) {
      digitalWrite(pumPin, HIGH);
      pumStatus = true;
    } if (voice.indexOf("tắt bơm") != -1) {
      digitalWrite(pumPin, LOW);
      pumStatus = false;
    }
    updateLCD();
  }
}
