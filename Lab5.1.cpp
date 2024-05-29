#include "Timer.h"
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String data = "";

enum States {reset, input1, output1, input2, output2} gState = reset;

void tick(void) {
  switch(gState) {
    case reset:
      gState = input1;
      Serial.println("Enter 1st Line: ");
    break;

    case input1:
      if (data == "") {
        gState = input1;
      }
      else {
        gState = output1;
      }
      break;

    case output1:
      gState = input2;
      Serial.println("Enter 2nd Line: ");
    break;

    case input2:
      if (data == "") {
        gState = input2;
      }
      else {
        gState = output2;
      }
    break;

    case output2:
      gState = reset;
    break;

    default: 
      gState = reset;
    break;
  }

    switch(gState) {
      case reset: 
        lcd.setCursor(0, 0);
        lcd.clear();
        data = "";
      break;
      case input1:
        data = Serial.readString();
      break;
      case output1:
        data.trim();
        lcd.print(data);
        lcd.setCursor(0, 1);
        data = "";
      break;
      case input2:
        data = Serial.readString();
      break;
      case output2:
        data.trim();
        lcd.print(data);
      break;
    }
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(9600);
  lcd.setCursor(0,0);
  TimerSet(1000);
  TimerOn();
}

void loop() {
  // Serial.println("Start");
  tick();

  while(!TimerFlag) {}
  TimerFlag = 0;  
