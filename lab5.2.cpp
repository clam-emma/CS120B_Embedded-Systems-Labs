#include "Timer.h"

int xValue = 0;
int yValue = 0;
int buttonState = 0;
int pinON = 13;
int mapp = 0;

void turnON () 
{
  if (pinON == 13) {
    if (digitalRead(13) == HIGH) {
      digitalWrite(13, LOW);
    }
    else if (digitalRead(13) == LOW) {
      digitalWrite(13, HIGH);
    }
  }
  else if (pinON == 12) {
    if (digitalRead(12) == HIGH) {
      digitalWrite(12, LOW);
    }
    else if (digitalRead(12) == LOW) {
      digitalWrite(12, HIGH);
    }
  }
  else if (pinON == 11) {
    if (digitalRead(11) == HIGH) {
      digitalWrite(11, LOW);
    }
    else if (digitalRead(11) == LOW) {
      digitalWrite(11, HIGH);
    }
  }
  else if (pinON == 10) {
    if (digitalRead(10) == HIGH) {
      digitalWrite(10, LOW);
    }
    else if (digitalRead(10) == LOW) {
      digitalWrite(10, HIGH);
    }
  }
  else if (pinON == 9) {
    if (digitalRead(9) == HIGH) {
      digitalWrite(9, LOW);
    }
    else if (digitalRead(9) == LOW) {
      digitalWrite(9, HIGH);
    }
  }
}

enum States {m3, m2, m1, m4, m5, ON_wr, ON} gState = m2;

void tick(void)
{
  switch (gState) {
    case m3:
      if (mapp == 3 && !buttonState) {
        gState = m3;
      }
      else if (mapp == 3 && buttonState) {
        gState = ON_wr;
      }
      else if (mapp > 3) {
        gState = m4;
      }
      else if (mapp < 3) {
        gState = m2;
      }
    break;

    case m4:
      if (mapp == 4 && !buttonState) {
        gState = m4;
      }
      else if (mapp == 4 && buttonState) {
        gState = ON_wr;
      }
      else if (mapp > 4) {
        gState = m5;
      }
      else if (mapp < 4) {
        gState = m3;
      }
    break;

    case m5:
      if (mapp > 4 && !buttonState) {
        gState = m5;
      }
      else if (mapp > 4 && buttonState) {
        gState = ON_wr;
      }
      else if (mapp <= 4) {
        gState = m4;
      }
    break;

    case m2:
      if (mapp >= 1 && !buttonState) {
        gState = m2;
      }
      else if (mapp >= 1 && buttonState) {
        gState = ON_wr;
      }
      else if (mapp > 2) {
        gState = m3;
      }
      else if (mapp < 2) {
        gState = m1;
      }
    break;

    case m1:
      if (mapp <= 1 && !buttonState) {
        gState = m1;
      }
      else if (mapp <= 1 && buttonState) {
        gState = ON_wr;
      }
      else if (mapp == 2) {
        gState = m2;
      }
    break;

    case ON_wr:
      if (buttonState) {
        gState = ON_wr;
      }
      else if (!buttonState) {
        gState = ON;
      }
    break;

    case ON:
      if (mapp <= 1 && !buttonState) {
        gState = m1;
      }
      else if (mapp == 2 && !buttonState) {
        gState = m2;
      }
      else if (mapp == 3 && !buttonState) {
        gState = m3;
      }
      else if (mapp == 4 && !buttonState) {
        gState = m4;
      }
      else if (mapp == 5 && !buttonState) {
        gState = m5;
      }
    break;

    default:
    break;
  }
  switch (gState) {
    case m3:
      pinON = 11;
    break;
    case m4:
      pinON = 10;
    break;
    case m5:
      pinON = 9;
    break;
    case m2:
      pinON = 12;
    break;
    case m1:
      pinON = 13;
    break;
    case ON_wr:
    break;
    case ON:
      turnON();
    break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  TimerSet(300);
  TimerOn();

}

void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(A0);
  yValue = analogRead(A1);
  buttonState = digitalRead(2);


  Serial.print("xval: ");
  Serial.println(xValue);
  Serial.print("mapval: ");
  Serial.println(mapp);
  // Serial.print("yval: ");
  // Serial.println(yValue);
  Serial.print("button: ");
  Serial.println(buttonState);
  Serial.print("pin: ");
  Serial.println(pinON);

  mapp = map(xValue, 0, 1010, 5, 0);

  tick();

  while (!TimerFlag) {}
  TimerFlag = 0;
}