#include "Timer.h"

enum STATE { OFF, CHECK_DARK, ON } gState = OFF;

int PR_val = 0;
int i = 0;
int threshold = 130;

void tick(void) {

  //transitions
  switch (gState) {
    case OFF:
      if (PR_val < threshold) {
        gState = CHECK_DARK;
      }
      else {
        gState = OFF;
      }
    break;

    case CHECK_DARK:
      if (!(PR_val < threshold)) {
        gState = OFF;
      }
      else if (i < 5 && PR_val < threshold) {
        gState = CHECK_DARK;
      }
      else if (!(i < 5) && PR_val < threshold) {
        gState = ON;
      }
    break;

    case ON:
      if (PR_val > threshold) {
        gState = OFF;
      }
      else {
        gState = ON;
      }
    break;

    default:
    gState = OFF;
    break;
  }

    //actions
    switch (gState) {
      case OFF:
        i = 0;
        digitalWrite(9, LOW);
      break;

      case CHECK_DARK:
        i = i + 1;
      break;

      case ON:
        digitalWrite(9, HIGH);
      break;
    }
}

void setup() {
  TimerSet(1000); //this value (500) is the period in ms
  TimerOn();
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  PR_val = analogRead(A0);
  Serial.println(PR_val);

  tick();

  while(!TimerFlag){}
  TimerFlag = 0;  
}