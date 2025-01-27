#define EEPROM_I2C_ADDRESS 0x53
#include <Wire.h>

// blank data for K, C, M & Y chip. 128 array of data. I got it from data dump of a replacement chip. 
byte KChipData[]={
0x32, 0x00, 0x01, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x13, 0x08, 0x4d, 0x43, 0x06, 0x00, 0x38, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

void setup() {
  // Select correct data for chip then copy to WriteData array
  byte WriteData[128];
  memcpy(WriteData,KChipData,128*sizeof(byte));

    

  
  // Start Wire and Serial bus
  Wire.begin();
  Serial.begin(115200);
  delay(100);

  Serial.println("Start");
  Serial.println(" ");

  // Start Read chip
  Serial.println(" ");
  Serial.print("Read 128 bytes :");
  int j=0;
  for(byte i=0;i<128;i++){
      byte readVale = i2cread(i);
      Serial.print(i);
      Serial.print(":");
      Serial.print(readVale,HEX);
      Serial.print(" ");
      j++;
      if (j>15) 
      {
        Serial.println();
        j=0;
      }
  } 
  // Start Write Chip with blank data
  Serial.println();
  Serial.print("Write 128 bytes:");
  byte wordaddress;

  for(byte i=0;i<128;i++){
        wordaddress = i;
        i2cwrite((byte)wordaddress,(byte)WriteData[i]);
        Serial.print(wordaddress);
        Serial.print(":");
        Serial.print(WriteData[i],HEX);
        Serial.print(" ");
  }

  // Start Read chip
  Serial.println(" ");
  Serial.print("Read 128 bytes :");
  for(byte i=0;i<128;i++){
      byte readVale = i2cread(i);
      Serial.print(i);
      Serial.print(":");
      Serial.print(readVale,HEX);
      Serial.print(" ");
  } 
  
  
  Serial.println(" ");  
  Serial.println("End");

}

void loop() {

}

void i2cwrite(byte address, byte data) {
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((byte)address);
  Wire.write((byte)data);
  Wire.endTransmission();
  delay(20);
}

byte i2cread(byte address) {
  byte rData = 0;
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((byte)address);
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_I2C_ADDRESS,1);
  while (Wire.available()){
    rData = Wire.read();
    return rData;
  }
}

void WhatI2CAddress() {
    for(int i=0;i<128;i++){
      Wire.requestFrom(i,1);  //request first data byte
      Serial.print(i);
      Serial.print(":");
      while(Wire.available()){
        byte c = Wire.read();
        Serial.print(c);      //if data exist, print it out. That way you can identify which address.
      }
      Serial.println(" ");
      delay(5);
  }
}
