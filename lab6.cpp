#include "Timer.h"
int butt = 0;
char gSegPins[] = {2,3,4,5,6,7,8};
int D1 = A0;
int D2 = A1;
int num = 0;
int cnt = 0;
int tens = 0;

unsigned char encodeInt[10] = {
  // 0     1     2     3     4     5     6     7     8     9
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67,
};

void displayNumTo7Seg(unsigned int targetNum, int digitPin) {

  digitalWrite(digitPin, HIGH);

  for (int k = 0; k < 7; ++k) {
    digitalWrite(gSegPins[k], encodeInt[targetNum] & (1 << k));
  }

  digitalWrite(digitPin, LOW);

}

void turnON() {
  if (num == 1) {
    digitalWrite(A3, HIGH);
    digitalWrite(A2, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else if (num == 2) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else if (num == 3) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else if (num == 4) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else if (num == 5) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else if (num == 6) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  else if (num == 7) {
    digitalWrite(A3, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  }
}
enum State { OFFR, ONR, BPR, OFFL, ONL, BPL } gState = OFFR;

void LightTick() 
{
  switch (gState) 
  {
    case OFFR:
      gState = ONR;
      num++;
      break;
    case ONR:
      if (butt) {
        gState = BPR;
      }
      else if (num == 7) {
        gState = ONL;
      }
      else {
        gState = OFFR;
      }
      break;
    case BPR:
      if (!butt) {
        gState = ONR;
      }
      break;
    case OFFL:
      gState = ONL;
      break;
    case ONL:
      if (butt) {
        gState = BPL;
      }
      else if (num == 0) {
        gState = ONR;
      }
      else {
        gState = OFFL;
        num--;
      }
      break;
    case BPL:
      if (!butt) {
        gState = ONL;
      }
    default:
    break;
  }

  switch (gState)
  {
    case OFFR:
    break;
    case ONR:
      turnON();
    break;
    case BPR:
      turnON();
    break;
    case OFFL:
    break;
    case ONL:
      turnON();
    break;
    case BPL:
      turnON();
    break;
  }
}

enum state { reset, digit2, digit1, BP_WR, BR } state = reset;

void Count() 
{
  switch (state)
  {
    case reset:
      state = digit2;
      break;
    case digit2:
      if (butt && num == 4) {
        state = BP_WR;
      }
      else if (butt && num != 4) {
        state = reset;
      }
      else {
        state = digit1;
      }
      break;
    case digit1:
      state = digit2;
      break;
    case BP_WR:
      if (butt) {
        state = BP_WR;
      }
      else if (!butt) {
        state = BR;
      }
      break;
    case BR:
      state = digit2;
    default:
    break;
  }
  switch (state) 
  {
    case reset:
      cnt = 0;
      tens = 0;
    break;
    case digit2:
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      displayNumTo7Seg(tens, D2);
    break;
    case digit1:
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      displayNumTo7Seg(cnt, D1);
    break;
    case BP_WR:
    break;
    case BR:
      if (cnt >= 9) {
        tens++;
        cnt = 0;
      }
      else if (cnt < 9) {
        cnt++;
      }
    break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // LED
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  // BUTTON
  pinMode(A5, INPUT);
  // 7 SEG
  pinMode(gSegPins[0], OUTPUT);
  pinMode(gSegPins[1], OUTPUT);
  pinMode(gSegPins[2], OUTPUT);
  pinMode(gSegPins[3], OUTPUT);
  pinMode(gSegPins[4], OUTPUT);
  pinMode(gSegPins[5], OUTPUT);
  pinMode(gSegPins[6], OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  TimerSet(100);  // increased period for demo
  TimerOn();

}

void loop() {
  // put your main code here, to run repeatedly:
  butt = digitalRead(A5);
  Serial.print("Button: ");
  Serial.println(butt);

  // digitalWrite(A2, HIGH);
  // digitalWrite(A3, HIGH);
  // digitalWrite(9, HIGH);
  // digitalWrite(10, HIGH);
  // digitalWrite(11, HIGH);
  // digitalWrite(12, HIGH);
  // digitalWrite(13, HIGH);

  // digitalWrite(D1, HIGH);
  // digitalWrite(D2, LOW);
  // digitalWrite(2, HIGH);
  // digitalWrite(3, HIGH);
  // digitalWrite(4, HIGH);
  // digitalWrite(5, HIGH);
  // digitalWrite(6, HIGH);
  // digitalWrite(7, HIGH);
  // digitalWrite(8, HIGH);

  // digitalWrite(A1, LOW);
  // digitalWrite(A0, HIGH);
  // displayNumTo7Seg(0, A1);
  // displayNumTo7Seg(5, A1);

  LightTick();
  Count();


  while (!TimerFlag) {}
  TimerFlag = 0;

}