//Lab 3 Part 1
// C++ code
//

enum STATE {INIT, ON, WAIT1, OFF, WAIT2} gState = INIT;
char buttonPressed = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case INIT:
    if (buttonPressed == HIGH) {
      gState = ON;
    }
    else if (buttonPressed == LOW) {
      gState = INIT;
    }
    break;
    
    case ON:
    if (buttonPressed == HIGH) {
      gState = ON;
    }
    else if (buttonPressed == LOW) {
      gState = WAIT1;
    }
    break;

    case WAIT1:
    if (buttonPressed == LOW) {
      gState = WAIT1;
    }
    else if (buttonPressed == HIGH) {
      gState = OFF;
    }
    break;

    case OFF: 
    if (buttonPressed == HIGH) {
      gState = OFF;
    }
    else  if (buttonPressed == LOW) {
      gState = WAIT2;
    }
    break;

    case WAIT2:
    if (buttonPressed == LOW) {
      gState = WAIT2;
    }
    else if (buttonPressed == HIGH) {
      gState = ON;
    }

    default:
    gState = INIT;
  }
  
  // actions
  switch (gState) {
    case INIT:
    break;

    case ON:
    digitalWrite(2, HIGH);

    case WAIT1:
    break;

    case OFF:
    digitalWrite(2,LOW);

    case WAIT2:
    break;

    default:
    break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick();
  delay(100);
}
