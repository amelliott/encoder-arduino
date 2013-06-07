
#include "Encoder.h"

#define ENCA 4
#define ENCB 5

//volatile Encoder * setEncoder = new Encoder(ENCA, ENCB);
//volatile Encoder * setButton = new Encoder(0, 1);
//int address = 0;

void OnLeft()
{
  Serial.println("Left");
}
void OnRight()
{
  Serial.println("Right");
}

void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  EncoderManager::registerEncoder(ENCA, ENCB, OnLeft, OnRight);
}

void loop()
{
}




