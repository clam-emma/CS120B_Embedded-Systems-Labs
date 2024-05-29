const int B[] = {2, 3, 4, 5};
int a = 0x00;
int a0, a1, a2, a3;

void setup()
{
  pinMode(B[0], OUTPUT);
  pinMode(B[1], OUTPUT);
  pinMode(B[2], OUTPUT);
  pinMode(B[3], OUTPUT);
  Serial.begin(9600);
}

void resetB()
{
  digitalWrite(B[3],LOW);
  digitalWrite(B[2],LOW);
  digitalWrite(B[1],LOW);
  digitalWrite(B[0],LOW);
}

void writeToB(unsigned char temp)
{
 
  if ((temp>>3) & 0x01){digitalWrite(B[3],HIGH);}
  if ((temp>>2) & 0x01){digitalWrite(B[2],HIGH);}
  if ((temp>>1) & 0x01){digitalWrite(B[1],HIGH);}
  if (temp & 0x01){digitalWrite(B[0],HIGH);}
}


void loop()
{
  int val = analogRead(A1);
  
  
  int mapped = map(val, 0, 1023, 4, 0);
  
  
  if (mapped == 0) { resetB(); }
  else if (mapped <= 1) { resetB(); writeToB(0x01); }
  else if (mapped <= 2) { resetB(); writeToB(0x03); }
  else if (mapped <= 3) { resetB(); writeToB(0x07); }
  else if (mapped <= 4) { resetB(); writeToB(0x0F); }
  else { digitalWrite(B[0],1); delay(200); resetB(); }
  
  
  delay(200);
}