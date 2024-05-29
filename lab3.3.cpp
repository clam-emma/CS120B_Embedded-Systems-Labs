//Lab 3 Part 2
// C++ code
//

enum STATE {INIT, X_WR1, X_WP1, Y_WR1, Y_WP1, Z_WR1, Z_WP1, X_WR2, X_WP2, Y_WR2, Y_WP2, Z_WR2} gState = INIT;
char button1 = 0;
char button2 = 0;
char button3 = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case INIT:
    if (button1 == HIGH) {
      gState = X_WR1;
      break;
    }
    gState = INIT;
    break;
    
    case X_WR1:
    if (button1 == HIGH) {
      gState = X_WR1;
    }
    else if (button1 == LOW) {
      gState = X_WP1;
    }
    break;

    case X_WP1:
    if (button1 == LOW) {
      gState = X_WP1;
    }
    else if (button1 == HIGH) {
      gState = X_WR1;
    }
    else if (button3 == HIGH) {
      gState = INIT;
    }
    else if (button2 == HIGH) {
      gState = Y_WR1;
    }
    break;

    case Y_WR1: 
    if (button2 == HIGH) {
      gState = Y_WR1;
    }
    else  if (button2 == LOW) {
      gState = Y_WP1;
    }
    break;

    case Y_WP1:
    if (button2 == LOW) {
      gState = Y_WP1;
    }
    else if (button2 == HIGH) {
      gState = INIT;
    }
    else if (button1 == HIGH) {
      gState = X_WR1;
    }
    else if (button3 == HIGH) {
      gState = Z_WR1;
    }
    break;

    case Z_WR1:
    if (button3 == HIGH) {
      gState = Z_WR1;
    }
    else if (button3 == LOW) {
      gState = Z_WP1;
    }
    break;

    case Z_WP1:
    if (!button3 || button2 || button3) {
      gState = Z_WP1;
    }
    else if (button1 == HIGH) {
      gState = X_WR2;
    }
    break;
/////////////////////////////////////////////////////
    case X_WR2:
    if (button1 == HIGH) {
      gState = X_WR2;
    }
    else if (button1 == LOW) {
      gState = X_WP2;
    }
    break;

    case X_WP2:
    if (button1 == LOW) {
      gState = X_WP2;
    }
    else if (button1 == HIGH) {
      gState = X_WR2;
    }
    else if (button3 == HIGH) {
      gState = Z_WP1;
    }
    else if (button2 == HIGH) {
      gState = Y_WR2;
    }
    break;

    case Y_WR2: 
    if (button2 == HIGH) {
      gState = Y_WR2;
    }
    else  if (button2 == LOW) {
      gState = Y_WP2;
    }
    break;

    case Y_WP2:
    if (button2 == LOW) {
      gState = Y_WP2;
    }
    else if (button2 == HIGH) {
      gState = Z_WP1;
    }
    else if (button1 == HIGH) {
      gState = X_WR2;
    }
    else if (button3 == HIGH) {
      gState = Z_WR2;
    }
    break;

    case Z_WR2:
    if (button3 == HIGH) {
      gState = Z_WR2;
    }
    else if (button3 == LOW) {
      gState = INIT;
    }
    break;

    default:
    gState = INIT;

  }
  
  // actions
  switch (gState) {
    case INIT:
    digitalWrite(2, LOW);
    break;

    case X_WR1:
    break;

    case X_WP1:
    break;

    case Y_WR1:
    break;

    case Y_WP1:
    break;

    case Z_WR1:
    break;

    case Z_WP1:
    digitalWrite(2,HIGH);
    break;
////////////////////////////////////
    case X_WR2:
    break;

    case X_WP2:
    break;

    case Y_WR2:
    break;

    case Y_WP2:
    break;

    case Z_WR2:
    break;

    default:
    break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(~11, INPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  button1 = digitalRead(13);
  button2 = digitalRead(12);
  button3 = digitalRead(~11);
  tick();
  delay(100);
}