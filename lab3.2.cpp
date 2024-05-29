//Lab 3 Part 2
// C++ code
//

enum STATE {INIT, R_WR, R_WP, G_WR, G_WP, Y_WR, Y_WP} gState = INIT;
char buttonPressed = 0;

void tick(void) {
  
  // transitions
  switch (gState) {
    case INIT:
    gState = R_WR;
    break;
    
    case R_WR:
    if (buttonPressed == HIGH) {
      gState = R_WR;
    }
    else if (buttonPressed == LOW) {
      gState = R_WP;
    }
    break;

    case R_WP:
    if (buttonPressed == LOW) {
      gState = R_WP;
    }
    else if (buttonPressed == HIGH) {
      gState = G_WR;
    }
    break;

    case G_WR: 
    if (buttonPressed == HIGH) {
      gState = G_WR;
    }
    else  if (buttonPressed == LOW) {
      gState = G_WP;
    }
    break;

    case G_WP:
    if (buttonPressed == LOW) {
      gState = G_WP;
    }
    else if (buttonPressed == HIGH) {
      gState = Y_WR;
    }
    break;

    case Y_WR:
    if (buttonPressed == HIGH) {
      gState = Y_WR;
    }
    else if (buttonPressed == LOW) {
      gState = Y_WP;
    }
    break;

    case Y_WP:
    if (buttonPressed == LOW) {
      gState = Y_WP;
    }
    else if (buttonPressed == HIGH) {
      gState = R_WR;
    }
    break;

    default:
    gState = INIT;

  }
  
  // actions
  switch (gState) {
    case INIT:
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    break;

    case R_WR:
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    break;

    case R_WP:
    break;

    case G_WR:
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
    break;

    case G_WP:
    break;

    case Y_WR:
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
    break;

    case Y_WP:
    break;

    default:
    break;
  }
}

void setup() {
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop()
{
  buttonPressed = digitalRead(13);
  tick();
  delay(100);
}

