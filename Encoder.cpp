#include "Encoder.h"
#include "Arduino.h"

int EncoderManager::mNumEncoders = 0;
Encoder EncoderManager::mEncoders[NUM_ENCODERS];

// TODO: When onLeft or onRight NULL, skip registration
Encoder * EncoderManager::registerEncoder(int pinA, int pinB, void(*onLeft)(), void (*onRight)())
{
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    attachInterrupt(pinA, onInterrupt, CHANGE);
    attachInterrupt(pinB, onInterrupt, CHANGE);
    
    Encoder * newEncoder = &mEncoders[mNumEncoders];
    newEncoder->pinA = pinA;
    newEncoder->pinB = pinB;
    newEncoder->onLeft = onLeft;
    newEncoder->onRight = onRight;
    ++mNumEncoders;
    return newEncoder;
}

// pos, turn, oldVal
void EncoderManager::onInterrupt()
{
    //Serial.println("onInterrupt");
    for (int i = 0; i < mNumEncoders; ++i)
    {
        Encoder * encoder = &mEncoders[i];
        int val1 = digitalRead(encoder->pinA);
        int val2 = digitalRead(encoder->pinB);
#ifdef ENC_DEBUG
        Serial.print("Pin1 (");
        Serial.print(encoder->pinA);
        Serial.print(encoder->oldPos);
        Serial.print("): ");
        Serial.println(val1);
        Serial.print("Pin2: (");
        Serial.print(encoder->pinB);
        Serial.print("): ");
        Serial.println(val2);
#endif
        int pos;
        // for each pair there's a position out of four
        if (val1 == 1 && val2 == 1) // stationary position
            pos = 0;
        else if (val1 == 0 && val2 == 1)
            pos = 1;
        else if (val1 == 0 && val2 == 0)
            pos = 2;
        else if (val1 == 1 && val2 == 0)
            pos = 3;
        
        int turn = pos - encoder->oldPos;
        
        if (abs(turn) != 2)  // impossible to understand where it's turning otherwise.
            if (turn == -1 || turn == 3)
                ++encoder->turnCount;
            else if (turn == 1 || turn == -3)
                --encoder->turnCount;
        
        if (pos == 0){ // only assume a complete step on stationary position
            if (encoder->turnCount > 0) {
                if (encoder->onLeft != NULL)
                    encoder->onLeft();
            }
            else if (encoder->turnCount < 0) {
                if (encoder->onRight != NULL)
                    encoder->onRight();
            }
            encoder->turnCount = 0;
        }
        
        encoder->oldPos  = pos;
        encoder->oldTurn = turn;
    }
}
