char myData[20];
byte myHex[2];

int B[8] = {2,3,4,5,6,7,8,9};

void setup() {
 for(int i = 0; i < 8 ; i++){
   pinMode(B[i],OUTPUT);
  }
  Serial.begin(9600);
}

int getHex()
{
 for (int i = 0; i < 2; i++)
 {
   byte y = myData[i];
   if (y <= 0x39)
   {
     myHex[i] = y - 0x30;
   }
   else
   {
     myHex[i] = y - 0x37;
   }
 }
 return ((unsigned int)(myHex[0] << 4) | (unsigned int)(myHex[1]));
}

int bitNum(unsigned int reading, int x) {	//returns the bit at a certain index
  int num;
  if (x==0) {num = reading&0x01; }
  else if (x==1) {num = reading&0x02; }
  else if (x==2) {num = reading&0x04; }
  else if (x==3) {num = reading&0x08; }
  else if (x==4) {num = reading&0x10; }
  else if (x==5) {num = reading&0x20; }
  else if (x==6) {num = reading&0x40; }
  else if (x==7) {num = reading&0x80; }
  return num;
}

void outIncr(unsigned int reading, int x){	//outputs starting from x
  for(int i = x; i >= 0; i--) {
    int num = bitNum(reading,i);
	digitalWrite(B[i],num);
  	delay(1000);
  	digitalWrite(B[i],0);
  }
}

void outOnce(unsigned int reading, int x) {	//outputs the whole 8bits
  for(int i = 0; i < 8; i++) {
    int num = bitNum(reading,i);
    digitalWrite(B[i],num);
  }
  delay(1000);
  for(int i = 0; i < 8; i++) {			//leave ON the starting increment bit
    if (i != x) {
    	digitalWrite(B[i],0);
    }
  }
}

void loop() {
 Serial.print("What is the input A?\n");
   while(Serial.available() == 0){}
 byte m = Serial.readBytesUntil('\n', myData, 20);
 myData[m] = '\0';
 unsigned int reading = getHex();
 Serial.println(reading,HEX);
 Serial.println(reading,BIN);
  Serial.println(reading);
  
  Serial.print("Which bit of A would you like to access?\n(enter a value 0-7)\n"); 
  
  while(Serial.available()==0) {}
  	int x = Serial.parseInt();
    Serial.println(x);
    
  Serial.print("masking...\n");
  
  outOnce(reading,x);
  
  outIncr(reading,x);

}
