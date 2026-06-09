#include "sp02.hpp"

/*
    Measuring Blood oxygen concentration 
*/

MAX30105 ParticleSensor;

#define MAX_BRIGHTNESS 255 

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__);
// Arduino Uno doesn't have enough SRAM to store 100 samples of IR led data and red led data in 32-bit format
// To solve this problem, 16-bit MSB of the sampled data will be truncated. Samples become 16-bit data.
uint16_t irbuffer[100]; // IR buffer data
uint16_t Redbuffer[100]; // Red buffer data
#else 
uint32_t irbuffer[100]; // IR buffer data
uint32_t Redbuffer[100]; // Red buffer data
#endif

int32_t BufferLength;  // Buffer length
int32_t Sp02; // SP02 value 
int8_t ValidSp02; // Valid Sp02
int32_t HeartRate; // Heart Rate Value 
int8_t ValidHeartRate; // Valid Heart Rate Value


byte pulseLED = 11; 
byte ReadLED = 13; 

void Sp02_Setup(){
    pinMode(pulseLED, OUTPUT);
    pinMode(ReadLED, OUTPUT);


    byte LedBrightness = 60; //Options: 0=Off to 255=50mA
    byte sampleAverage = 3; //Options: 1, 2, 4, 8, 16, 32
    byte LedMode = 2;  //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 411; //Options: 69, 118, 215, 411
    int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

    ParticleSensor.setup(LedBrightness, sampleAverage, LedMode, sampleRate, pulseWidth, adcRange);

}


void RunSp02(){

    BufferLength = 100;

    for(uint i = 0; i < BufferLength; i++){
        // check for signal 
        while(ParticleSensor.available() == false){ // checking for new data 
            ParticleSensor.check(); // do we have new data? 
        }

        Redbuffer[i] = ParticleSensor.getRed();
        irbuffer[i] = ParticleSensor.getIR();

        ParticleSensor.nextSample();


        Serial.print(F("RED = "));
        Serial.print(Redbuffer[i], DEC);
        Serial.print(F("IR = "));
        Serial.print(irbuffer[i], DEC);


    }
}

