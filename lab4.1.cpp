#include "Timer.h"

enum STATE {OFF, WR1, SB1, SB0, WR2, FB1, FB0, WR3} gState = OFF;

char button = 0;
int period = 500;

void tick(void) {
  
  // transitions
  switch (gState) {
    case OFF:
      if (button) {
        gState = WR1;
      }
      else {
        gState = OFF;
      }
    break;
    
    case WR1:
      if (!button) {
        gState = SB1;
      }
      else {
        gState = WR1;
      }
    break;

    case SB1:
      if (!button) {
        gState = SB0;
      }
      else {
        gState = WR2;
      }
    break;

    case SB0:
      if (!button) {
        gState = SB1;
      }
      else {
        gState = WR2;
      }
    break;

    case WR2:
      if (!button) {
        gState = FB1;
      }
      else {
        gState = WR2;
      }
    break;

    case FB1:
      if (!button) {
        gState = FB0;
      }
      else {
        gState = WR3;
      }
    break;

    case FB0:
      if (!button) {
        gState = FB1;
      }
      else {
        gState = WR3;
      }
    break;

    case WR3:
      if (!button) {
        gState = OFF;
      }
      else {
        gState = WR3;
      }
    break;

    default:
      gState = OFF;
    break;
  }
  
  // actions
  switch (gState) {
    case OFF:
      digitalWrite(2, LOW);
    break;

    case WR1:
    period = 500;
    setup();
    break;

    case SB1:
      digitalWrite(2, HIGH);
    break;
    case SB0:
      digitalWrite(2, LOW);
    break;

    case WR2:
    period = 200;
    setup();
    break;

    case FB1:
      digitalWrite(2, HIGH);
    break;
    case FB0:
      digitalWrite(2,LOW);
    break;

    case WR3:
    break;
  }
}

void setup() {
  TimerSet(period); //this value (500) is the period in ms
  TimerOn();
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  button = digitalRead(13);
  tick();
  while(!TimerFlag){}
  TimerFlag = 0;  
}