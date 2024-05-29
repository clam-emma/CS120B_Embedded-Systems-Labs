#include "Timer.h"

enum STATE {RED, WR, GREEN, YELLOW} gState = RED;

char button = 0;
int i = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case RED:
      if (button) {
        gState = WR;
      }
      else {
        gState = RED;
      }
    break;
    
    case WR:
      if (!button) {
        gState = GREEN;
        i = 0;
      }
      else {
        gState = WR;
      }
    break;

    case GREEN:
      if (i < 10) {
        gState = GREEN;
      }
      else if (!(i < 10)) {
        gState = YELLOW;
        i = 0;
      }
    break;

    case YELLOW:
      if (i < 5) {
        gState = YELLOW;
      }
      else if (!(i < 5)) {
        gState = RED;
        i = 0;
      }
    break;

    default:
    gState = RED;
    break;
  }
  
  // actions
  switch (gState) {
    case RED:
      digitalWrite(6, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(2, LOW);
      i = 0;
    break;

    case WR:
    break;

    case GREEN:
      digitalWrite(6, LOW);
      digitalWrite(4, LOW);
      digitalWrite(2, HIGH);
      i = i + 1;
    break;

    case YELLOW:
      digitalWrite(6, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(2, LOW);
      i = i + 1;
    break;
  }
}

void setup() {
  TimerSet(1000); //this value (500) is the period in ms
  TimerOn();
  pinMode(13, INPUT);
  pinMode(6, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  button = digitalRead(13);
  tick();
  while(!TimerFlag){}
  TimerFlag = 0;  
}