#include "NewEncoder.h"
#include "Arduino.h"

int Encoder::mNumEncoders = 0;
int Encoder::mPinA[NUM_ENCODERS];
int Encoder::mPinB[NUM_ENCODERS];
volatile int Encoder::mPrevPinAVal[NUM_ENCODERS];
volatile int Encoder::mPrevPinBVal[NUM_ENCODERS];


void Encoder::registerEncoder(int pinA, int pinB)
{
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    attachInterrupt(pinA, onInterrupt, CHANGE);
    attachInterrupt(pinB, onInterrupt, CHANGE);

    mPinA[mNumEncoders] = pinA;
    mPinB[mNumEncoders] = pinB;
    mPrevPinAVal[mNumEncoders] = 0;
    mPrevPinBVal[mNumEncoders] = 0;
    ++mNumEncoders;
}

void Encoder::deregisterEncoder(volatile Encoder* encoder)
{
}

void Encoder::onInterrupt()
{
    Serial.println("onInterrupt");
    for (int i = 0; i < mNumEncoders; ++i)
    {

    }
}
